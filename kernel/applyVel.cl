__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity,
							double posX, double posY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		start = gid * 3;
	float3	particle;

	float3 vel = particlesVelocity[gid].xyz;
	particle.x = particles[start];
	particle.y = particles[start + 1];
	particle.z = particles[start + 2];
	float	width = 900.f;
	float	height = 600.f;
	float3 center = float3(posX * width - width / 2.0f, posY * height - height / 2.0f, -5000.f);

	//printf("Center: pos(%f, %f)  %f, %f, %f\n", posX, posY, center.x, center.y, center.z);
	double3 tmp = convert_double3(center - particle);
	double dist = distance(center, particle);
	//printf("g: %e\n", g);
	double fGravity = (G_CONST * MASS_POINT * MASS_PARTICLES) / (dist * dist);
	//printf("fGravity: %e\n", fGravity);
	tmp *= fGravity;
	//printf("fgravity: (%e * %e * %e / %e) = %e\n", G_CONST, MASS_POINT, MASS_PARTICLES, dist * dist, fGravity);
	vel += convert_float3(tmp);
	particlesVelocity[gid].xyz = vel;
	//printf("tmp: %f, %f, %f   vel: %f %f %f particle: %f, %f, %f\n", tmp.x, tmp.y, tmp.z, vel.x, vel.y, vel.z, particle.x, particle.y, particle.z);
	particle += vel;
	//particle = min(particle, float3(300, 300, -300.0f));
	//particle = max(particle, float3(-300, -300, -900.0f));
/*
	if (particle.x > 300.f)
		particle.x = 300.f;
	if (particle.x > 300.f)
		particle.x = 300.f;
*/
	//printf("Particle2: %f, %f, %f src: %f, %f, %f\n", particle.x, particle.y, particle.z, t.x, t.y, t.z);
	particles[start] = particle.x;
	particles[start + 1] = particle.y;
	particles[start + 2] = particle.z;
}
