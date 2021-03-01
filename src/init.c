/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <lshellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		init_mlx(t_wolf3d *wlf)
{
	if (!(wlf->mlx_ptr = mlx_init()))
		return (ERR);
	if (!(wlf->win_ptr = mlx_new_window(wlf->mlx_ptr, W, H, "Wolf3D")))
		return (ERR);
	if (!(wlf->img = (t_img *)ft_memalloc(sizeof(t_img))))
		return (ERR);
	if (!(wlf->img->img_ptr = mlx_new_image(wlf->mlx_ptr, W, H)))
		return (ERR);
	if (!(wlf->img->data = (int *)mlx_get_data_addr(wlf->img->img_ptr,
			&wlf->img->bpp, &wlf->img->size_line, &wlf->img->endian)))
		return (ERR);
	return (NO_ERR);
}

int		init_wlf(t_wolf3d *wlf)
{
	wlf->pos = wlf->map.pos;
	wlf->dir = wlf->map.dir;
	norm_vect2d(&wlf->dir);
	wlf->plane = cross_vect3d(&wlf->dir);
	norm_vect2d(&wlf->plane);
	norm_vect2d(&wlf->dir);
	norm_vect2d(&wlf->dir);
	return (NO_ERR);
}

int		init_one_text(t_wolf3d *wlf, t_texture *text, char *file)
{
	if (!(text->tex_ptr = mlx_xpm_file_to_image(
			wlf->mlx_ptr,
			file,
			&text->width,
			&text->height)))
		return (ERR);
	if (!(text->buf = (int *)mlx_get_data_addr(
			text->tex_ptr,
			&text->bpp,
			&text->size_line,
			&text->endian)))
		return (ERR);
	return (NO_ERR);
}

int		init_textures(t_wolf3d *wlf)
{
	if (!(wlf->text = ft_memalloc(sizeof(t_texture) * TEX_NUM)))
		return (ERR);
	if (ERR == init_one_text(wlf, wlf->text, TEXT1))
		return (ERR);
	if (ERR == init_one_text(wlf, wlf->text + 1, TEXT2))
		return (ERR);
	if (ERR == init_one_text(wlf, wlf->text + 2, TEXT3))
		return (ERR);
	if (ERR == init_one_text(wlf, wlf->text + 3, TEXT4))
		return (ERR);
	if (ERR == init_one_text(wlf, wlf->text + 4, TEXT5))
		return (ERR);
	return (NO_ERR);
}

void	init(t_wolf3d *wlf)
{
	if (ERR == init_wlf(wlf))
		exit(0);
	if (ERR == init_mlx(wlf))
		exit(0);
	if (ERR == init_textures(wlf))
		exit(0);
}
