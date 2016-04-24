__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity,
							double posX, double posY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		start = gid * 3;
	float3	particle;

	float3 center = float3(posX * SIZE_X, posY * SIZE_Y, -100.0f);
	float3 vel = particlesVelocity[gid].xyz;
	particle.x = particles[start];
	particle.y = particles[start + 1];
	particle.z = particles[start + 2];

	double3 tmp = convert_double3(center - particle);
	double dist = distance(center, particle);
	//printf("g: %e\n", g);
	double fGravity = (G * MASS_POINT * MASS_PARTICLES) / (dist * dist);
	//printf("fGravity: %e\n", fGravity);
	tmp *= fGravity * 0.1;
	//printf("fgravity: (%e * %e * %e / %e) = %e\n", G, MASS_POINT, MASS_PARTICLES, dist * dist, fGravity);
	vel += convert_float3(tmp);
	particlesVelocity[gid].xyz = vel;
	//printf("tmp: %f, %f, %f   vel: %f %f %f particle: %f, %f, %f\n", tmp.x, tmp.y, tmp.z, vel.x, vel.y, vel.z, particle.x, particle.y, particle.z);
	particle += vel;
	particle = min(particle, float3(SIZE_X, SIZE_Y, SIZE_Z));
	particle = max(particle, float3(-SIZE_X, -SIZE_Y, -SIZE_Z));
	particles[start] = particle.x;
	particles[start + 1] = particle.y;
	particles[start + 2] = particle.z;
}
