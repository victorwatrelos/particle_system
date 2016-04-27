__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity,
							float posX, float posY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	gid *= NB_PARTICLES_PER_WORK_ITEM;
	int		i;
	int		start;
	float	width, height;
	float3	center;
	double	dist;
	double3	tmp;
	double	fGravity;
	float3	particle;

	i = 0;
	while (i < NB_PARTICLES_PER_WORK_ITEM && gid < NB_PARTICLES)
	{
		i++;
		start = gid * 3;

		float3 vel = particlesVelocity[gid].xyz;

		particle.x = particles[start];
		particle.y = particles[start + 1];
		particle.z = particles[start + 2];

		(void)(vel);
		width = 1350.f;
		height = width * 1.f;
		center = (float3)(posX * width - width / 2.0f, posY * height - height / 2.0f, 0.f);
		dist = distance(center, particle);
		if (dist < 1.0)
		{
			gid++;
			continue ;
		}

		(void)tmp;
		tmp = convert_double3(center - particle);
		fGravity = (G_CONST * MASS_POINT * MASS_PARTICLES) / (dist * dist);

		tmp *= fGravity;
		vel += convert_float3(tmp);
		particlesVelocity[gid].xyz = vel;
		particle += vel;

		particles[start] = particle.x;
		particles[start + 1] = particle.y;
		particles[start + 2] = particle.z;
		gid++;
	}
}
