__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		start = gid * 3;
	//int	startVel = gid * 4;
	float3	particle;
	float3 center = float3(-50.f, 10.f, -300.f);
	float3 vel = particlesVelocity[gid].xyz;
	particle.x = particles[start];
	particle.y = particles[start + 1];
	particle.z = particles[start + 2];
	float3 tmp = center - particle;
	vel += (center - particle) * 0.001f;
	//vel.z = 0.0f;
	particlesVelocity[gid].xyz = vel;
	//printf("tmp: %f, %f, %f   vel: %f %f %f particle: %f, %f, %f\n", tmp.x, tmp.y, tmp.z, vel.x, vel.y, vel.z, particle.x, particle.y, particle.z);
	particle += vel;
	particles[start] = particle.x;
	particles[start + 1] = particle.y;
	particles[start + 2] = particle.z;
}
