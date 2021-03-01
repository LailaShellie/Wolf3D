/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

//void		render1(t_wolf3d *wlf)
//{
//	double		cam_x;
//	int 		x = -1;
//	double		side_x = 0;
//	double		side_y = 0;
//
//	ft_bzero(wlf->img->data, W * H * 4);
//	while (++x < W)
//	{
//		wlf->ray.map_x = (int)wlf->pos.x;
//		wlf->ray.map_y = (int)wlf->pos.y;
//
//		cam_x = 2.0 * x / W - 1.0;
//		wlf->ray.dir.x = wlf->dir.x + wlf->plane.x * cam_x;
//		wlf->ray.dir.y = wlf->dir.y + wlf->plane.y * cam_x;
//
//		wlf->ray.delta_x = fabs(1 / wlf->ray.dir.x);
//		wlf->ray.delta_y = fabs(1 / wlf->ray.dir.y);
//
//		if (wlf->ray.dir.x < 0)
//		{
//			wlf->ray.step_x = -1;
//			side_x = (wlf->pos.x - wlf->ray.map_x) * wlf->ray.delta_x;
//		}
//		else
//		{
//			wlf->ray.step_x = 1;
//			side_x = (wlf->ray.map_x + 1.0 - wlf->pos.x) * wlf->ray.delta_x;
//		}
//
//		if (wlf->ray.dir.y < 0)
//		{
//			wlf->ray.step_y = -1;
//			side_y = (wlf->pos.y - wlf->ray.map_y) * wlf->ray.delta_y;
//		}
//		else
//		{
//			wlf->ray.step_y = 1;
//			side_y = (wlf->ray.map_y + 1.0 - wlf->pos.y) * wlf->ray.delta_y;
//		}
//		int         hit = 0;
//		int         side = -1;
//		while (hit == 0 && wlf->ray.map_x < 23 && wlf->ray.map_y < 23 && wlf->ray.map_x > 0 && wlf->ray.map_y > 0)
//		{
//			if (side_x < side_y)
//			{
//				side_x += wlf->ray.delta_x;
//				wlf->ray.map_x += wlf->ray.step_x;
//				side = 0;
//			}
//			else
//			{
//				side_y += wlf->ray.delta_y;
//				wlf->ray.map_y += wlf->ray.step_y;
//				side = 1;
//			}
//			hit = worldMap[wlf->ray.map_y][wlf->ray.map_x];
//		}
//		if (hit == 0)
//			continue;
//		hit = (hit + 1) % TEX_NUM;
//		if (side == 0)
//			wlf->ray.dist = (wlf->ray.map_x - wlf->pos.x + (1.0 - wlf->ray.step_x) / 2.0) / wlf->ray.dir.x;
//		else
//			wlf->ray.dist = (wlf->ray.map_y - wlf->pos.y + (1.0 - wlf->ray.step_y) / 2.0) / wlf->ray.dir.y;
//		wlf->ray.line = (int)(H / wlf->ray.dist);
//
//		int start, end;
//
//		start = -wlf->ray.line / 2 + H / 2;
//		end = wlf->ray.line / 2 + H / 2;
//		if (start < 0)
//			start = 0;
//		if (end >= H)
//			end = H - 1;
//		double wallx = 0;
//		if (side == 0)
//			wallx = wlf->pos.y + wlf->ray.dist * wlf->ray.dir.y;
//		else
//			wallx = wlf->pos.x + wlf->ray.dist * wlf->ray.dir.x;
//		wallx -= floor(wallx);
//		printf("%lf\n", wallx);
//		int texx = (int)(wallx * (double)wlf->text[hit].width);
//		if(side == 0 && wlf->ray.dir.x > 0)
//			texx = wlf->text[hit].width - texx - 1;
//		if(side == 1 && wlf->ray.dir.y < 0)
//			texx = wlf->text[hit].width - texx - 1;
//		printf("%d\n",texx);
//		int texy;
//		double step = 1.0 * wlf->text[hit].height / wlf->ray.line;
//		double texPos = (start - H / 2.0 + wlf->ray.line / 2.0) * step;
//
//		while (start <= end)
//		{
//			if ((int)texPos >= wlf->text[hit].height)
//				texy = (int)texPos % wlf->text[hit].height - 1;
//			else
//				texy = (int)texPos;
//			wlf->img->data[x + start * wlf->img->size_line / 4] = wlf->text[hit].buf[texx + texy * wlf->text[hit].height];
//			texPos += step;
//			++start;
//		}
//	}
//	mlx_put_image_to_window(wlf->mlx_ptr, wlf->win_ptr, wlf->img->img_ptr, 0, 0);
//}

#define MAP_ERROR "Not valid map\n"
#define ARG_ERROR "usage:\n./wolf3d map_file\n"

int		ft_exit(t_wolf3d *wlf, char *msg_error)
{
	if (msg_error)
		ft_putstr_fd(msg_error, 2);
	(void)wlf;
	exit(0);
}

int main(int argc, char **argv)
{
	t_wolf3d wlf;

	if (argc != 2)
		return (ft_exit(&wlf, ARG_ERROR));
	ft_bzero(&wlf, sizeof(t_wolf3d));
	if (!(file_to_map(argv[1], &wlf.map)))
		return (ft_exit(&wlf, MAP_ERROR));
	init(&wlf);
	render(&wlf);
	hooks(&wlf);
	return (0);
}
