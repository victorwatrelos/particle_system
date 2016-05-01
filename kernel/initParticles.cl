# define R_SPHERE 1000.f
# define STEP_SPHERE 2.f
# define STEP_CIRCLE (0.01f * M_PI)
# define NB_POINT_PER_LINE 15

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
	int		is_cube = 1;
	float	x, y, z, n, r, oa, teta;
	int		oa_index, teta_index, n_index;
	int		tot_oa, tot_teta;
	int		i = gid;

	if (is_cube) {
		x = (((float)(gid % ((int)SIZE_X))) - SIZE_X / 2.0f) * COEFF_START + centerX;
		y = ((((gid % (int)(SIZE_X * SIZE_Y))  / (int)SIZE_X)) - (int)SIZE_Y / 2.0f) * COEFF_START + centerY;
		z = ((gid / (int)(SIZE_X * SIZE_Y)) - SIZE_X / 2.0f) * COEFF_START;
	} else {
		tot_oa = (int)((float)((R_SPHERE / STEP_SPHERE) * 2.f));
		tot_teta = ((2.f * M_PI) / STEP_CIRCLE);

		oa_index = i / (tot_teta * NB_POINT_PER_LINE);
		teta_index = (i - (oa_index * tot_teta * NB_POINT_PER_LINE)) / NB_POINT_PER_LINE;
		n_index = (i - (oa_index * tot_teta * NB_POINT_PER_LINE + teta_index * NB_POINT_PER_LINE));

		oa = R_SPHERE - ((float)(oa_index) * STEP_SPHERE);
		teta = teta_index * STEP_CIRCLE;
		n = (float)(n_index) / (float)(NB_POINT_PER_LINE);
		r = sqrt((R_SPHERE * R_SPHERE) - oa * oa);
		x = cos(teta) * r;
		y = sin(teta) * r;
		z = R_SPHERE - ((float)(oa_index) * STEP_SPHERE);
	}

	particles[gid].xyz = (float3)(x, y, z);
/*
	particles[startPart] = x;
	particles[startPart + 1] = y;
	particles[startPart + 2] = z;
*/
	particlesVelocity[gid].xyz = (float3)(0.f, 0.f, 0.f);
	particlesColor[gid] = 1.0f;
}
