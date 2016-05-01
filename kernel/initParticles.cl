__kernel void	initParticles(__global float3	*particles,
							__global float3	*particlesVelocity,
							__global float *particlesColor,
							float centerX, float centerY)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	//int		startPart = gid * 4;
	//int		startVel = gid * 4;
	float	x, y, z;
	x = (((float)(gid % ((int)SIZE_X))) - SIZE_X / 2.0f) * COEFF_START + centerX;
	y = ((((gid % (int)(SIZE_X * SIZE_Y))  / (int)SIZE_X)) - (int)SIZE_Y / 2.0f) * COEFF_START + centerY;
	z = ((gid / (int)(SIZE_X * SIZE_Y)) - SIZE_X / 2.0f) * COEFF_START;
	particles[gid].xyz = (float3)(x, y, z);
/*
	particles[startPart] = x;
	particles[startPart + 1] = y;
	particles[startPart + 2] = z;
*/
	particlesVelocity[gid].xyz = (float3)(0.f, 0.f, 0.f);
	particlesColor[gid] = 1.0f;
}
