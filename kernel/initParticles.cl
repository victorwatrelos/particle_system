__kernel void	initParticles(__global float3	*particles,
							__global float3	*particlesVelocity,
							__global float *particlesColor,
							float centerX, float centerY, int is_cube)
{
	int		gid = get_global_id(0);
	if (gid > MAX_GID)
		return ;
	float	x, y, z, n, r, oa, teta;
	int		oa_index, teta_index, n_index;
	int		i = gid;

	if (is_cube) {
		x = (((float)(gid % ((int)SIZE_X))) - SIZE_X / 2.0f);
		y = ((((gid % (int)(SIZE_X * SIZE_Y))  / (int)SIZE_X)) - (int)SIZE_Y / 2.0f);
		z = ((gid / (int)(SIZE_X * SIZE_Y)) - SIZE_X / 2.0f);
	} else {
		oa_index = i / (TOT_TETA * NB_POINT_PER_LINE);
		teta_index = (i - (oa_index * TOT_TETA * NB_POINT_PER_LINE)) / NB_POINT_PER_LINE;
		n_index = (i - (oa_index * TOT_TETA * NB_POINT_PER_LINE + teta_index * NB_POINT_PER_LINE));

		oa = (float)(R_SPHERE) - ((float)(oa_index) * (float)(STEP_SPHERE));
		teta = (float)(teta_index) * (float)(STEP_CIRCLE);
		n = (float)(n_index) / (float)(NB_POINT_PER_LINE);
		r = sqrt(((float)(R_SPHERE * R_SPHERE)) - oa * oa);
		x = (cos(teta) * r) * n;
		y = (sin(teta) * r) * n;
		z = ((float)(R_SPHERE) - ((float)(oa_index) * (float)STEP_SPHERE));
		//printf("(gid: %d) coord %f, %f, %f, teta: %f, oa: %f, r: %f, n: %f\n", gid, x, y, z, teta, oa, r, n);
	}

	particles[gid].xyz = (float3)(x * COEFF_START + centerX, y * COEFF_START + centerY, z * COEFF_START);
	particlesVelocity[gid].xyz = (float3)(0.f, 0.f, 0.f);
	particlesColor[gid] = 1.0f;
}
