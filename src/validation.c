/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <ssoraka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:28:14 by ssoraka           #+#    #+#             */
/*   Updated: 2019/04/16 18:47:16 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define EMPTY 0
#define OUT -1

int		valid_position(t_map *map, int y, int x)
{
	int pos;

	pos = map->map[y][x];
	if (pos >= -1 && pos <= TEX_NUM)
		return (NO_ERR);
	pos += '0';
	if (ft_strchr("NSWE", pos) && !map->has_person)
	{
		if (pos == 'S')
			map->dir.y = 1;
		if (pos == 'N')
			map->dir.y = -1;
		if (pos == 'E')
			map->dir.x = 1;
		if (pos == 'W')
			map->dir.x = -1;
		map->pos.x = x;
		map->pos.y = y;
		map->map[y][x] = EMPTY;
		map->has_person = 1;
		return (NO_ERR);
	}
	return (ERR);
}

int		validate_map(t_map *map)
{
	int y;
	int x;
	int **ptr;

	ptr = map->map;
	y = -1;
	while (++y < map->heigth)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!valid_position(map, y, x))
				return (ERR);
			if (ptr != EMPTY)
				continue;
			if (x == 0 || x == map->width - 1 || y == 0 || y == map->heigth - 1)
				return (ERR);
			if (ptr[y][x + 1] == OUT || ptr[y][x - 1] == OUT
				|| ptr[y + 1][x] == OUT || ptr[y - 1][x] == OUT
				|| ptr[y + 1][x + 1] == OUT || ptr[y + 1][x - 1] == OUT
				|| ptr[y - 1][x + 1] == OUT || ptr[y - 1][x - 1] == OUT)
				return (ERR);
		}
	}
	return (NO_ERR);
}
