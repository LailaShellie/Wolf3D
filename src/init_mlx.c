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

# include "wolf3d.h"

int			ft_close(t_wolf3d *wlf)
{
	(void)wlf;
	exit(0);
}

void		hooks(t_wolf3d *wlf)
{
	mlx_hook(wlf->win_ptr, 17, 0, ft_close, wlf);
	mlx_loop(wlf->mlx_ptr);
}

int			init_mlx(t_wolf3d *wlf)
{
	if (!(wlf->mlx_ptr = mlx_init()))
		return (ERR);
	if (!(wlf->win_ptr = mlx_new_window(wlf->mlx_ptr, W, H, "Wolf3D")))
		return (ERR);
	if (!(wlf->img = ft_memalloc(sizeof(t_img))))
		return (ERR);
	if (!(wlf->img->img_ptr = mlx_new_image(wlf->mlx_ptr, W, H)))
		return (ERR);
	if (!(wlf->img->data = (int *)mlx_get_data_addr(wlf->img->img_ptr,
			&wlf->img->bpp, &wlf->img->size_line, &wlf->img->endian)))
		return (ERR);
	return (1);
}
