/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <lshellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 15:50:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define MAP_ERROR "Not valid map\n"
#define ARG_ERROR "usage:\n./wolf3d map_file\n"

int		ft_exit(t_wolf3d *wlf, char *msg_error)
{
	if (msg_error)
		ft_putstr_fd(msg_error, 2);
	(void)wlf;
	exit(0);
}

int		main(int argc, char **argv)
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
