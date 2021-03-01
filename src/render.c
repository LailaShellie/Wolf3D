/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by odrinkwa         ###   ########.fr       */
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

void	cast_ray(t_wolf3d *wlf, t_ray *ray)
{
	double	side_x;
	double	side_y;

	side_x = ray->dir.x >= 0 ? (1.0 - wlf->pos.x + ray->map_x)
			* ray->delta_x : (wlf->pos.x - ray->map_x) * ray->delta_x;
	side_y = ray->dir.y >= 0 ? (1.0 - wlf->pos.y + ray->map_y)
			* ray->delta_y : (wlf->pos.y - ray->map_y) * ray->delta_y;
	ray->step_x = ray->dir.x >= 0 ? 1 : -1;
	ray->step_y = ray->dir.y >= 0 ? 1 : -1;
	while (ray->hit == 0 && ray->map_x > 0 && ray->map_x < wlf->map.width - 1 && ray->map_y > 0 && ray->map_y < wlf->map.heigth - 1)
	{
		if (side_x < side_y)
		{
			side_x += ray->delta_x;
			ray->side = X_SIDE;
			ray->map_x += ray->step_x;
		}
		else
		{
			side_y += ray->delta_y;
			ray->side = Y_SIDE;
			ray->map_y += ray->step_y;
		}
		ray->hit = wlf->map.map[ray->map_y][ray->map_x];
	}
	if (ray->hit == 0)
		return ;
	ray->hit = (ray->hit - 1) % (TEX_NUM); //
	draw_line(wlf, ray);
}

void	render_floor(t_wolf3d *wlf)
{
	t_vect2d floor;
	t_vect2d floor_step;
	t_vect2d ray_dir0;
	float row_dist;

	for(int y = 0; y < H / 2 ; y++) {
		ray_dir0.x = wlf->dir.x + wlf->dir.y;
		ray_dir0.y = wlf->dir.y - wlf->dir.x;
		row_dist = (0.5 * H) / (H / 2 - y);
		floor_step.x = row_dist * (wlf->dir.x - wlf->dir.y - ray_dir0.x) / W;
		floor_step.y = row_dist * (wlf->dir.y + wlf->dir.x - ray_dir0.y) / W;
		floor.x = wlf->pos.x + row_dist * ray_dir0.x;
		floor.y = wlf->pos.y + row_dist * ray_dir0.y;



		int x;
		int tx;
		int ty;
		int cell_x;
		int cell_y;

		x = -1;
		while (++x < W)
		{
			cell_x = (int)(floor.x);
			cell_y = (int)(floor.y);

			tx = (int)(wlf->text[4].width * (floor.x - cell_x)) & (wlf->text[4].width - 1);
			ty = (int)(wlf->text[4].height * (floor.y - cell_y)) & (wlf->text[4].height - 1);
			wlf->img->data[y * W + x] = wlf->text[4].buf[wlf->text[4].width * ty + tx];

			tx = (int)(wlf->text[2].width * (floor.x - cell_x)) & (wlf->text[2].width - 1);
			ty = (int)(wlf->text[2].height * (floor.y - cell_y)) & (wlf->text[2].height - 1);
			wlf->img->data[(H - y - 1) * W + x] = wlf->text[2].buf[wlf->text[2].width * ty + tx];
			floor.x += floor_step.x;
			floor.y += floor_step.y;
		}
	}
}


void	render(t_wolf3d *wlf)
{
	t_ray	ray;
	double 	delta;

	wlf->x = -1;
	ft_bzero(wlf->img->data, W * H * 4);
	render_floor(wlf);
	while (++wlf->x < W)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.map_x = (int)wlf->pos.x;
		ray.map_y = (int)wlf->pos.y;
		delta = 2.0 * wlf->x / W - 1.0;
		ray.dir.x = wlf->dir.x - wlf->dir.y * delta;
		ray.dir.y = wlf->dir.y + wlf->dir.x * delta;
		ray.delta_x = fabs(1 / ray.dir.x);
		ray.delta_y = fabs(1 / ray.dir.y);
		cast_ray(wlf , &ray);
	}
	mlx_put_image_to_window(wlf->mlx_ptr, wlf->win_ptr, wlf->img->img_ptr, 0, 0);
}
