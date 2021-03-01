
#ifndef WOLF3D_WOLF3D_H
# define WOLF3D_WOLF3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include "keys.h"
# include <unistd.h>
# include <fcntl.h>

# include "../mlx/mlx.h"

# define ERR 0
# define NO_ERR 1
# define W 1200
# define H 800

# define TEX_NUM 5

# define TEXT1 "textures/bluestone.xpm"
# define TEXT2 "textures/purplestone.xpm"
# define TEXT3 "textures/redbrick.xpm"
# define TEXT4 "textures/wood.xpm"
//# define TEXT5 "pics/bat_enter.xpm"
# define TEXT5 "textures/Ivan.xpm"

# define X_SIDE 0
# define Y_SIDE 1

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

typedef struct			s_texture
{
	void				*tex_ptr;
	int 				*buf;
	int 				height;
	int 				width;
	int					bpp;
	int					size_line;
	int					endian;
}						t_texture;

typedef	struct			s_ray
{
	t_vect2d			dir;
	double				delta_x;
	double 				delta_y;
	int 				step_x;
	int 				step_y;
	int 				side;
	int 				hit;
	int 				map_x;
	int 				map_y;
	double				dist;
	int 				line;
	int 				start;
	int 				end;
}						t_ray;

typedef struct			s_map
{
	int 				**map;
	int 				width;
	int 				heigth;
	int					has_person;
	t_vect2d			pos;
	t_vect2d			dir;
}						t_map;

typedef struct			s_wolf3d
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*img;
	t_texture			*text;
	t_vect2d			pos;
	t_vect2d			dir;
	t_vect2d			plane;
	t_ray				ray;
	int 				x;
	t_map				map;
}						t_wolf3d;

void		norm_vect2d(t_vect2d *a);
double		len_vect2d(t_vect2d *a);
t_vect2d	cross_vect3d(t_vect2d *a);
t_vect2d	rot_vect2d(t_vect2d *a, double angle);
void		scale_vect2d(double scale, t_vect2d *a);

void 		init(t_wolf3d *wlf);
void		hooks(t_wolf3d *wlf);

void		render(t_wolf3d *wlf);

int			file_to_map(char *file, t_map *map);
int			validate_map(t_map *map);

#endif
