/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <lshellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define TRUE 1
#define FALSE 0

#define STEP 0.1
#define FORWARD 1
#define BACKWARD -1

#define EMPTY 0

int			ft_close(t_wolf3d *wlf)
{
	(void)wlf;
	exit(0);
}

int			set_new_pos(t_vect2d *old, t_vect2d *dir, int move, t_map *map)
{
	t_vect2d new_p;

	new_p.x = old->x + dir->x * STEP * move;
	new_p.y = old->y + dir->y * STEP * move;
	if (new_p.x >= 0 && new_p.x < map->width
	&& new_p.y >= 0 && new_p.y < map->heigth
	&& map->map[(int)new_p.y][(int)new_p.x] == EMPTY)
	{
		*old = new_p;
		return (TRUE);
	}
	return (FALSE);
}

int			keyhooks(int key, t_wolf3d *wlf)
{
	if (key == KEY_UP && set_new_pos(&wlf->pos, &wlf->dir, FORWARD, &wlf->map))
		render(wlf);
	if (key == KEY_DOWN
	&& set_new_pos(&wlf->pos, &wlf->dir, BACKWARD, &wlf->map))
		render(wlf);
	if (key == KEY_LEFT)
	{
		wlf->dir = rot_vect2d(&wlf->dir, -0.1);
		render(wlf);
	}
	if (key == KEY_RIGHT)
	{
		wlf->dir = rot_vect2d(&wlf->dir, 0.1);
		render(wlf);
	}
	if (key == KEY_ESC)
		ft_close(wlf);
	return (1);
}

void		hooks(t_wolf3d *wlf)
{
	mlx_hook(wlf->win_ptr, 17, 0, ft_close, wlf);
	mlx_hook(wlf->win_ptr, 2, 0, keyhooks, wlf);
	mlx_loop(wlf->mlx_ptr);
}
