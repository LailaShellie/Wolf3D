/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <lshellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw(t_wolf3d *wlf, t_ray *ray, int x, double step)
{
	int		y;
	double	tex_pos;

	tex_pos = (ray->start - H / 2.0 + ray->line / 2.0) * step;
	while (ray->start <= ray->end)
	{
		if ((int)tex_pos >= wlf->text[ray->hit].height)
			y = (int)tex_pos % wlf->text[ray->hit].height - 1;
		else
			y = (int)tex_pos;
		tex_pos += step;
		wlf->img->data[wlf->x + ray->start * wlf->img->size_line / 4] =
				wlf->text[ray->hit].buf[x + y * wlf->text[ray->hit].height];
		++ray->start;
	}
}

void	manage_texture(t_wolf3d *wlf, t_ray *ray)
{
	double		wallx;
	int			textx;
	double		step;

	if (ray->side == 0)
		wallx = wlf->pos.y + ray->dir.y * ray->dist;
	else
		wallx = wlf->pos.x + ray->dir.x * ray->dist;
	wallx -= floor(wallx);
	textx = (int)(wallx * wlf->text[ray->hit].width);
	if (ray->side == 0 && ray->dir.x > 0)
		textx = wlf->text[ray->hit].width - textx - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		textx = wlf->text[ray->hit].width - textx - 1;
	step = 1.0 * wlf->text[ray->hit].height / ray->line;
	draw(wlf, ray, textx, step);
}

void	draw_line(t_wolf3d *wlf, t_ray *ray)
{
	if (ray->side == X_SIDE)
		ray->dist = (ray->map_x - wlf->pos.x + (1.0 - ray->step_x) / 2.0)
				/ ray->dir.x;
	else
		ray->dist = (ray->map_y - wlf->pos.y + (1.0 - ray->step_y) / 2.0)
				/ ray->dir.y;
	ray->line = (int)(H / ray->dist);
	ray->start = H / 2 - ray->line / 2;
	ray->end = H / 2 + ray->line / 2;
	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= H)
		ray->end = H - 1;
	manage_texture(wlf, ray);
}

void	get_hit(t_wolf3d *wlf, t_ray *ray, t_vect2d side)
{
	while (ray->hit == 0 && ray->map_x > 0 && ray->map_x < wlf->map.width - 1
	&& ray->map_y > 0 && ray->map_y < wlf->map.heigth - 1)
	{
		if (side.x < side.y)
		{
			side.x += ray->delta_x;
			ray->side = X_SIDE;
			ray->map_x += ray->step_x;
		}
		else
		{
			side.y += ray->delta_y;
			ray->side = Y_SIDE;
			ray->map_y += ray->step_y;
		}
		ray->hit = wlf->map.map[ray->map_y][ray->map_x];
	}
}

void	cast_ray(t_wolf3d *wlf, t_ray *ray)
{
	t_vect2d	side;

	side.x = ray->dir.x >= 0 ? (1.0 - wlf->pos.x + ray->map_x)
			* ray->delta_x : (wlf->pos.x - ray->map_x) * ray->delta_x;
	side.y = ray->dir.y >= 0 ? (1.0 - wlf->pos.y + ray->map_y)
			* ray->delta_y : (wlf->pos.y - ray->map_y) * ray->delta_y;
	ray->step_x = ray->dir.x >= 0 ? 1 : -1;
	ray->step_y = ray->dir.y >= 0 ? 1 : -1;
	get_hit(wlf, ray, side);
	if (ray->hit <= 0)
		return ;
	ray->hit = get_texture_id(ray->hit, ray->side, ray->step_x, ray->step_y);
	draw_line(wlf, ray);
}
