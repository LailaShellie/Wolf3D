
#include "../includes/wolf3d.h"

int worldMap[24][24]=
        {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

void        draw_line(t_wolf3d *wlf, int s, int e, int x)
{
    while (s <= e)
    {
        wlf->img->data[x + s * wlf->img->size_line / 4] = 255;
        ++s;
    }
}

int main()
{


	t_wolf3d wlf;

	ft_bzero(&wlf, sizeof(t_wolf3d));
	wlf.map.wx = 24;
	wlf.map.wy = 24;
	wlf.player.pos.x = 1;
    wlf.player.pos.y = 1;
    wlf.player.dir.x = 1;
    wlf.player.dir.y = 0;
	init_mlx(&wlf);
	t_vect2d	ray;
	double		cam_x;
	int 		x = 0;

	int 		map_x;
	int 		map_y;

	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;

	int         step_x;
	int         step_y;
	int         hit = 0;
	int         side = 0;

	double      perpWall;

	int         line;

	while (x < W)
	{
		map_x = (int)wlf.player.pos.x;
		map_y = (int)wlf.player.pos.y;

		delta_x = fabs(1 / wlf.player.dir.x);
		delta_y = fabs(1 / wlf.player.dir.y);

		cam_x = 2.0 * x / (double)W - 1;
		ray.x = wlf.player.dir.x + wlf.player.plane.x * cam_x;
		ray.y = wlf.player.dir.y + wlf.player.plane.y * cam_x;

		if (wlf.player.dir.x < 0)
        {
            step_x = -1;
            side_x = (wlf.player.pos.x - map_x) * delta_x;
        }
		else
        {
		    step_x = 1;
		    side_x = (map_x + 1.0 - wlf.player.pos.x) * delta_x;
        }

        if (wlf.player.dir.y < 0)
        {
            step_y = -1;
            side_y = (wlf.player.pos.y - map_y) * delta_y;
        }
        else
        {
            step_y = 1;
            side_y = (map_x + 1.0 - wlf.player.pos.y) * delta_y;
        }

        while (hit == 0)
        {
            if (side_x < side_y)
            {
                side_x += delta_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_y += delta_y;
                map_y += step_y;
                side = 1;
            }
            if (worldMap[map_x][map_y] > 0)
                hit = 1;
        }
        if (side == 0)
            perpWall = (map_x - wlf.player.pos.x + (1.0 - step_x) / 2) / wlf.player.dir.x;
        else
            perpWall = (map_y - wlf.player.pos.y + (1.0 - step_y) / 2) / wlf.player.dir.y;
        line = (int)(H / perpWall);

        int start, end;

        start = -line / 2 + H / 2;
        end = line / 2 + H / 2;
        if (start < 0)
            start = 0;
        if (end >= H)
            end = H - 1;
        draw_line(&wlf, start, end, x);
        ++x;
	}
	mlx_put_image_to_window(wlf.mlx_ptr, wlf.win_ptr, wlf.img->img_ptr, 0, 0);
	hooks(&wlf);
	return (0);
}
