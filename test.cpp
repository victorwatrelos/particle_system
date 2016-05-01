#include <iostream>
#include <cmath>

# define R_SPHERE 100.f
# define STEP_SPHERE 41.8323f
# define STEP_CIRCLE (0.01f * M_PI)
# define NB_POINT_PER_LINE 15

void	calc_it(int oa_index, int teta_index, int n_index)
{
	float oa, teta, n;
	float	x, y, r, z;

	oa = R_SPHERE - ((float)(oa_index) * STEP_SPHERE);
	teta = teta_index * STEP_CIRCLE;
	n = (float)(n_index) / (float)(NB_POINT_PER_LINE);
	r = sqrt((R_SPHERE * R_SPHERE) - oa * oa);
	x = cos(teta) * r;
	y = sin(teta) * r;
	z = R_SPHERE - ((float)(oa_index) * STEP_SPHERE);
/*	std::cout << "Dir: oa: " << oa
		<< " teta: " << teta
		<< " res: " << n
		<< " x: " << x * n
		<< " y: " << y * n
		//<< " x: " << x
		//<< " y: " << y
		<< " z: " << z
		<< std::endl;*/
}

void	from_i(int i)
{
	int oa_index, teta_index, n_index;
	int	tot_oa, tot_teta;
	int	first_part_n;
	int	second_par_n;

	tot_oa = (int)((float)((R_SPHERE / STEP_SPHERE) * 2.f));
	tot_teta = ((2.f * M_PI) / STEP_CIRCLE);
	oa_index = i / (tot_teta * NB_POINT_PER_LINE);
	teta_index = (i - (oa_index * tot_teta * NB_POINT_PER_LINE)) / NB_POINT_PER_LINE;
	//std::cout << (i - (oa_index * tot_teta * NB_POINT_PER_LINE)) << " btw: 0-" << tot_teta * NB_POINT_PER_LINE
	//	<< std::endl;
	n_index = (i - (oa_index * tot_teta * NB_POINT_PER_LINE + teta_index * NB_POINT_PER_LINE));

	/*std::cout << "tot oa: " << tot_oa << " tot_teta: " << tot_teta 
		<< " oa index: " << oa_index
		<< " teta index: " << teta_index
		<< " n_index: " << n_index
		<< std::endl;*/
	calc_it(oa_index, teta_index, n_index);
}

int main()
{
	float	oa;
	float	R = R_SPHERE;
	float	r;
	float	step_sphere = STEP_SPHERE;
	float	step_circle = STEP_CIRCLE;
	float	teta;
	float	n;
	float	step = 5.f;
	float	ret = 0.0f;
	float	i = 0.0f;
	int		j;
	float	av_r = 77.613;
	int		nb_point_per_line = NB_POINT_PER_LINE;

	float	x, y, z;
	int		nb_ao, nb_teta, nb_n = 0;

	int	nb_entry = 0;
	nb_ao = 0;
	nb_teta = 0;
	for (oa = R; oa > -R; oa -= step_sphere)
	{
		z = oa;
		r = sqrt((R * R) - oa * oa);
		ret += r;
		i += 1.f;
		//std::cout << "r: " << r << std::endl;
		nb_teta = 0;
		for (teta = 0.0f; teta < 2 * M_PI; teta += step_circle)
		{
			x = cos(teta) * r;
			y = sin(teta) * r;
			nb_n = 0;
			for (j = 0; j < nb_point_per_line; j++)
			{

				float	res = (float)(j) / (float)(nb_point_per_line);
		//		std::cout << "Ind teta: " << teta  << " coord: " << x * res << ", " << y * res << ", " << z << std::endl;
			/*	std::cout << "Ind: oa: " << oa
					<< " teta: " << teta
					<< " res: " << res
					<< " x: " << x * res
					<< " y: " << y * res
					//<< " x: " << x
					//<< " y: " << y
					<< " z: " << z
					<< std::endl;*/
				/*std::cout << "Ind: oa: " << oa << " teta: " << teta
				  << " res: " << res << " x: " << x * res << " y: " << y * res
				  << " x: " << x
				  << " y: " << y
				  << std::endl;
				//calc_it(nb_ao, nb_teta, j);
				std::cout << "oa_index: " << nb_ao
				<< " teta_index: " << nb_teta
				<< " n_index: " << j
				<< std::endl;*/
				from_i(nb_entry);

				nb_n++;
				nb_entry++;
			}
			nb_teta++;
		}
		nb_ao++;
	}

	std::cout << "ret: " << ret / i << std::endl;
	float tot = ((R / step_sphere) * 2.f) * (((2 * M_PI) / step_circle) * (nb_point_per_line));
	float tot_2 = ((R_SPHERE / STEP_SPHERE) * 2.f) * (((2 * M_PI) / STEP_CIRCLE) * (NB_POINT_PER_LINE));
	//std::cout << "nb ao: " << nb_ao << " nb teta: " << nb_teta << " nb n : " << nb_n << std::endl;
	/*std::cout << "Calculte: " 
		<< "nb ao: " << ((R / step_sphere) * 2.f)
		<< " nb teta: " << ((2 * M_PI) / step_circle)
		<< " nb n : " << nb_point_per_line << std::endl;
	std::cout << "tot: " << tot  << std::endl;
	std::cout << "nb entry: " << nb_entry << "average n : " << nb_entry / nb_teta << std::endl;
	*/
	float	tmp = (4.f * R_SPHERE * M_PI * NB_POINT_PER_LINE) / (STEP_SPHERE * STEP_CIRCLE);
	float 	o = (4 * R_SPHERE * M_PI * NB_POINT_PER_LINE) / (14343 * STEP_CIRCLE);
	std::cout << "tot: " << tot << " tot2: " << tot_2 << " tmp: " << tmp
		<< " n: " << o << " n step sphere: " << STEP_SPHERE
		<< std::endl;
}
