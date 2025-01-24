#include "../../inc/cub3d.h"

void	find_intersect(t_raycast *ray_data, t_data *data)
{
	int grid[2];


		/*Interseccion H
			Primera interseccion
				1. Finding the coordinate of A.
				If the ray is facing up (between 179-1 ??)
					A.y = rounded_down(Py/64) * (64) - 1;
				If the ray is facing down (between 181-359 ??)
					A.y = rounded_down(Py/64) * (64) + 64;
				A.y=rounded_down(224/64) * (64) - 1 = 191;
				A.y is 191/64 = 2;

				A.x = Px + (Py-A.y)/tan(ALPHA);
				A.x=96 + (224-191)/tan(60) = about 115;
				The grid coordinate of A.x is 115/64 = 1;

				Check if wall in grid

				2.Finding Ya
					If the ray is facing up
						Ya=-64;
					If the ray is facing down
						Ya=64;
				3. Finding Xa
				Xa = 64/tan(ALPHA) = 36;
		*/
}

void	draw_map(t_raycast *ray_data, t_data *data)
{
	int	i;
	
	i = 0;
	/*Raycasting

	Primer angulo pixel 0 (pj angle + 30)
	Bucle all pixels WIDTH
	while(i < WIDTH)
	{
		find_intersect(HORIZONTAL, ray_data, data);
		find_intersect(VERTICAL, ray_data, data);
		i++;
	}
		Buscar pixel (y) donde dibujar muro
			Buscar intersecciones
							Interseccion V
			Calcular distancia
			Calcular distancia real (sin distorsion)
			Printar cielo
			Printar muro
			Printar suelo
		Restar decremento angulo (izq a derecha resta)
	fin bucle */
	
}
