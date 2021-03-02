/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
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
#define MIN_MAP_SIZE 3

void	del(void *content, size_t ivan)
{
	(void)ivan;
	free(content);
}

int		read_file_to_lists(int fd, int *height, int *width, t_list *begin)
{
	char	*str;
	t_list	*tmp;
	t_list	*new;

	begin->next = NULL;
	tmp = begin;
	*height = 0;
	*width = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		{
			free(str);
			return (ERR);
		}
		new->content = str;
		tmp->next = new;
		tmp = new;
		(*width) = (*width > ft_strlen(str)) ? *width : ft_strlen(str);
		(*height)++;
	}
	return (NO_ERR);
}

int		create_map_from_list(t_map *map, t_list *lst)
{
	char	*ptr;
	int		**line;
	int		i;

	if (!(map->map = (int **)ft_memalloc((map->heigth + 1) * sizeof(int *))))
		return (ERR);
	line = map->map;
	while (lst)
	{
		if (!(*line = (int *)malloc(map->width * sizeof(int))))
			return (ERR);
		ft_memset(*line, OUT, map->width * sizeof(int));
		ptr = lst->content;
		i = -1;
		while (ptr[++i])
			(*line)[i] = (ptr[i] == ' ') ? -1 : ptr[i] - '0';
		line++;
		lst = lst->next;
	}
	return (NO_ERR);
}

int		file_to_map(char *file, t_map *map)
{
	int		fd;
	t_list	lst[1];

	if ((fd = open(file, O_RDWR)) < 0)
		return (ERR);
	if (!(read_file_to_lists(fd, &map->heigth, &map->width, lst))
	|| map->heigth < MIN_MAP_SIZE || map->width < MIN_MAP_SIZE
	|| !(create_map_from_list(map, lst->next)))
	{
		close(fd);
		ft_lstdel(&lst->next, &del);
		return (ERR);
	}
	close(fd);
	ft_lstdel(&lst->next, &del);
	if (!(validate_map(map)) || !map->has_person)
		return (ERR);
	return (NO_ERR);
}
