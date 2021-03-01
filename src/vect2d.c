/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vect2d	rot_vect2d(t_vect2d *a, double angle)
{
	t_vect2d v;

	v.x = a->x * cos(angle) - a->y * sin(angle);
	v.y = a->x * sin(angle) + a->y * cos(angle);
	return (v);
}

t_vect2d	cross_vect3d(t_vect2d *a)
{
	t_vect2d v;

	v.x = -a->y;
	v.y = a->x;
	return (v);
}

double		len_vect2d(t_vect2d *a)
{
	double len;

	len = a->x * a->x;
	len += a->y * a->y;
	return (sqrt(len));
}

void		scale_vect2d(double scale, t_vect2d *a)
{
	a->x *= scale;
	a->y *= scale;
}

void		norm_vect2d(t_vect2d *a)
{
	double		len;

	len = len_vect2d(a);
	a->x /= len;
	a->y /= len;
}
