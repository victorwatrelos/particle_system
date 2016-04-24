__kernel void	initParticles(__global float	*particles,
							__global float	*particlesVelocity)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	int		startPart = gid * 3;
	int		startVel = gid * 4;
	particles[startPart] = ((float)(gid % ((int)SIZE_X))) - SIZE_X / 2.0f;
	particles[startPart + 1] = (((gid % (int)(SIZE_X * SIZE_Y))  / (int)SIZE_X)) - (int)SIZE_Y / 2.0f;
	particles[startPart + 2] = (gid / (int)(SIZE_X * SIZE_Y)) - 600.0f - SIZE_X / 2.0f;
	particlesVelocity[startVel] = 0.f;
	particlesVelocity[startVel + 1] = 0.f;
	particlesVelocity[startVel + 2] = 0.f;
}
