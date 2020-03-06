
#ifndef WOLF3D_WOLF3D_H
# define WOLF3D_WOLF3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>

# define ERR 0
# define W 1200
# define H 800

typedef struct			s_vect2d
{
	double 				x;
	double 				y;
}						t_vect2d;

typedef struct			s_img
{
	void				*img_ptr;
    int 				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_img;

typedef struct			s_player
{
	t_vect2d			pos;
	t_vect2d			dir;
	t_vect2d			plane;
}						t_player;

typedef struct			s_map
{
	unsigned int		wx;
	unsigned int		wy;
	int 				**field;
}						t_map;

typedef struct			s_wolf3d
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*img;
	t_map				map;
	t_player			player;
}						t_wolf3d;

int			init_mlx(t_wolf3d *wlf);
void		hooks(t_wolf3d *wlf);

#endif
