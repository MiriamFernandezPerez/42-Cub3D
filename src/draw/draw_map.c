#include "../../inc/cub3d.h"

void	draw_map(t_data *data)
{
	/*Raycasting

	Primer angulo pixel 0 (pj angle + 30)
	Bucle all pixels WIDTH
		Buscar pixel (y) donde dibujar muro
			Buscar intersecciones
				Interseccion H
					Primera interseccion
						1. Finding the coordinate of A.
  						If the ray is facing up (between 179-1 ??)
     						A.y = rounded_down(Py/64) * (64) - 1;
   						If the ray is facing down (between 181-359 ??)
     						A.y = rounded_down(Py/64) * (64) + 64;
				Interseccion V
			Calcular distancia
			Calcular distancia real (sin distorsion)
			Printar cielo
			Printar muro
			Printar suelo
		Restar decremento angulo (izq a derecha resta)
	fin bucle
	*/
}
