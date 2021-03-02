/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <lshellie@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by ssoraka           #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_floor(t_wolf3d *wlf, int y, t_vect2d floor, t_vect2d floor_step)
{
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
		tx = (int)(wlf->text[4].width * (floor.x - cell_x))
			& (wlf->text[4].width - 1);
		ty = (int)(wlf->text[4].height * (floor.y - cell_y))
			& (wlf->text[4].height - 1);
		wlf->img->data[y * W + x] =
				wlf->text[4].buf[wlf->text[4].width * ty + tx];
		wlf->img->data[(H - y - 1) * W + x] =
				wlf->text[2].buf[wlf->text[2].width * ty + tx];
		floor.x += floor_step.x;
		floor.y += floor_step.y;
	}
}

void	render_floor(t_wolf3d *wlf)
{
	t_vect2d	floor;
	t_vect2d	floor_step;
	t_vect2d	ray_dir0;
	float		row_dist;
	int			y;

	y = -1;
	while (++y < H / 2)
	{
		ray_dir0.x = wlf->dir.x + wlf->dir.y;
		ray_dir0.y = wlf->dir.y - wlf->dir.x;
		row_dist = (0.5 * H) / (H / 2 - y);
		floor_step.x = row_dist * (wlf->dir.x - wlf->dir.y - ray_dir0.x) / W;
		floor_step.y = row_dist * (wlf->dir.y + wlf->dir.x - ray_dir0.y) / W;
		floor.x = wlf->pos.x + row_dist * ray_dir0.x;
		floor.y = wlf->pos.y + row_dist * ray_dir0.y;
		draw_floor(wlf, y, floor, floor_step);
	}
}

int		get_texture_id(int hit, int side, int step_x, int step_y)
{
	hit = (hit - 1) % (TEX_NUM);
	if (hit > 1)
		return (hit);
	if (side == X_SIDE)
		hit = (step_x == 1) ? hit : hit + TEX_NUM;
	else if (side == Y_SIDE)
		hit = (step_y == 1) ? hit + TEX_NUM + 2 : hit;
	return (hit);
}

void	render(t_wolf3d *wlf)
{
	t_ray	ray;
	double	delta;

	ft_bzero(wlf->img->data, W * H * 4);
	render_floor(wlf);
	wlf->x = -1;
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
		cast_ray(wlf, &ray);
	}
	mlx_put_image_to_window(
			wlf->mlx_ptr, wlf->win_ptr, wlf->img->img_ptr, 0, 0);
}
