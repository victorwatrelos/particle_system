__kernel void	applyVel(__global float	*particles,
							__global float4	*particlesVelocity,
							float centerX, float centerY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		start;
	float3	center;
	float	dist;
	float3	particle;

	start = gid * 3;
	float3 vel = particlesVelocity[gid].xyz;
	particle.x = particles[start];
	particle.y = particles[start + 1];
	particle.z = particles[start + 2];
	center = (float3)(centerX, centerY, 0.f);
	dist = distance(center, particle);
	if (dist < 1.0)
		return ;
	vel += (center - particle) * (((float)(DIVIDEND)) / (pown(dist, 2)));
	particlesVelocity[gid].xyz = vel;
	particle += vel;
	particles[start] = particle.x;
	particles[start + 1] = particle.y;
	particles[start + 2] = particle.z;
}
