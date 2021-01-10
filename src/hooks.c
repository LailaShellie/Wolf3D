/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int 		keyhooks(int key, t_wolf3d *wlf)
{
	printf("%d - key\n", key);
	if (key == KEY_UP)
	{
		wlf->pos.x += wlf->dir.x * 0.1;
		wlf->pos.y += wlf->dir.y * 0.1;
		render(wlf);
	}
	if (key == KEY_DOWN)
	{
		wlf->pos.x -= wlf->dir.x * 0.1;
		wlf->pos.y -= wlf->dir.y * 0.1;
		render(wlf);
	}
	if (key == KEY_LEFT)
	{
		wlf->dir = rot_vect2d(&wlf->dir, -0.1);
//		wlf->plane = rot_vect2d(&wlf->plane, -0.1);
		render(wlf);
	}
	if (key == KEY_RIGHT)
	{
		wlf->dir = rot_vect2d(&wlf->dir, 0.1);
//		wlf->plane = rot_vect2d(&wlf->plane, 0.1);
		render(wlf);
	}
	if (key == KEY_ESC)
		exit(0);
	return (1);
}

int			ft_close(t_wolf3d *wlf)
{
	(void)wlf;
	exit(0);
}

void		hooks(t_wolf3d *wlf)
{
	mlx_hook(wlf->win_ptr, 17, 0, ft_close, wlf);
	mlx_hook(wlf->win_ptr, 2, 0, keyhooks, wlf);
	mlx_loop(wlf->mlx_ptr);
}
