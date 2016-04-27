__kernel void	applyVel(__global float3 *particles,
							__global float3	*particlesVelocity,
							float centerX, float centerY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	float3	center;
	float	dist;

	float3	vel = particlesVelocity[gid];
	float3	particle = particles[gid];
	center = (float3)(centerX, centerY, 0.f);
	dist = distance(center, particle);
	if (dist < 1.0)
		return ;
	vel += (center - particle) * (((float)(DIVIDEND)) / (pown(dist, 2)));
	particlesVelocity[gid] = vel;
	particle += vel;
	particles[gid] = particle;
}
