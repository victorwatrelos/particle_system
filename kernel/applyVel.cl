__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		start = gid * 3;
	//int	startVel = gid * 4;
	float3	particle;
	float3 center = float3(0.f, 0.f, 0.f);
	float3 vel = particlesVelocity[gid].xyz;
	particle.x = particles[start];
	particle.y = particles[start + 1];
	particle.z = particles[start + 2];
	vel += (center - particle) * 0.01f;
	particlesVelocity[gid].xyz = vel;
	particle += vel;
	particles[start] = particle.x;
	particles[start + 1] = particle.y;
	particles[start + 2] = particle.z;
}
