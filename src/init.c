//
// Created by Ivan on 15/03/2020.
//

#include "wolf3d.h"

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
	return (NO_ERR);
}

int 		init_wlf(t_wolf3d *wlf)
{
	ft_bzero(wlf, sizeof(t_wolf3d));
	wlf->pos.x = 2;
	wlf->pos.y = 2;
	wlf->dir.x = 1;
	wlf->dir.y = 1;
	norm_vect2d(&wlf->dir);
	wlf->plane = cross_vect3d(&wlf->dir);
	norm_vect2d(&wlf->plane);
	norm_vect2d(&wlf->dir);
	init_mlx(wlf);
	norm_vect2d(&wlf->dir);
	return (NO_ERR);
}

int 		init_one_text(t_wolf3d *wlf, int id, char *file)
{
	if (!(wlf->text[id].tex_ptr = mlx_xpm_file_to_image(wlf->mlx_ptr, file, &wlf->text[id].width, &wlf->text[id].height)))
		return (ERR);
	if (!(wlf->text[id].buf = (int *)mlx_get_data_addr(wlf->text[id].tex_ptr,
			&wlf->text[id].bpp, &wlf->text[id].size_line, &wlf->text[id].endian)))
		return (ERR);
	return (NO_ERR);
}

int 		init_textures(t_wolf3d *wlf)
{
	if (!(wlf->text = ft_memalloc(sizeof(t_texture) * TEX_NUM)))
		return (ERR);
	if (ERR == init_one_text(wlf, 0, TEXT1))
		return (ERR);
	if (ERR == init_one_text(wlf, 1, TEXT2))
		return (ERR);
	if (ERR == init_one_text(wlf, 2, TEXT3))
		return (ERR);
	if (ERR == init_one_text(wlf, 3, TEXT4))
		return (ERR);
	return (NO_ERR);
}

void 	init(t_wolf3d *wlf)
{
	if (ERR == init_wlf(wlf))
		exit (0);
	if (ERR == init_mlx(wlf))
		exit (0);
	if (ERR == init_textures(wlf))
		exit (0);
}