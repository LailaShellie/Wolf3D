//
// Created by Suzette Soraka on 1/27/21.
//

#include "../includes/wolf3d.h"

#define EMPTY 0
#define OUT -1

//отладочная функция
void	print_map(t_map *map)
{
	int y;
	int x;

	printf("width = %d, height = %d\n", map->width, map->heigth);
	y = 0;
	while (y < map->heigth)
	{
		x = 0;
		while (x < map->width)
		{
			printf("%d ", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	del(void *content, size_t ivan)
{
	(void)ivan;
	free(content);
}

int		read_file_to_lists(int fd, int *height, int *width, t_list *begin)
{
	char *str;
	t_list *tmp;
	t_list *new;

	begin->next = NULL;
	tmp = begin;
	*height = 0;
	*width = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		{
			free(str);
			ft_lstdel(&begin->next, &del);
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
	char *ptr;
	int **line;
	int i;

	if (!(map->map = ft_memalloc((map->heigth + 1) * sizeof(int *))))
		return (ERR);
	line = map->map;
	while (lst)
	{
		if (!(*line = malloc(map->width * sizeof(int))))
			return (ERR);
		ft_memset(*line, OUT, map->width * sizeof(int));
		ptr = lst->content;
		i = -1;
		while(ptr[++i])
			(*line)[i] = ptr[i] - '0';
		line++;
		lst = lst->next;
	}
	return (NO_ERR);
}

int		validate_map(int **map, int heigth, int width)
{
	int y;
	int x;

	y = -1;
	while (++y < heigth)
	{
		x = -1;
		while (++x < width)
		{
			if (map[y][x] != EMPTY)
				continue;
			if (x == 0 || x == width - 1 || y == 0 || y == heigth - 1)
				return (ERR);
			if (map[y][x + 1] == OUT || map[y][x - 1] == OUT
			|| map[y + 1][x] == OUT || map[y - 1][x] == OUT
			|| map[y + 1][x + 1] == OUT || map[y + 1][x - 1] == OUT
			|| map[y - 1][x + 1] == OUT || map[y - 1][x - 1] == OUT)
				return (ERR);
		}
	}
	return (NO_ERR);
}

int		file_to_map(char *file, t_map *map)
{
	int fd;
	t_list lst[1];

	if ((fd = open(file, O_RDWR)) < 0)
		return (ERR);
	if (!(read_file_to_lists(fd, &map->heigth, &map->width, lst))) //читаем в список строк
		return (ERR);
	close(fd);
	if (!(create_map_from_list(map, lst->next))) //создаем массив интов для прямоугольной карты
	{
		ft_lstdel(&lst->next, &del);
		return (ERR);
	}
	ft_lstdel(&lst->next, &del);
	if (!(validate_map(map->map, map->heigth, map->width))) //валидируем контур
		return (ERR);
	print_map(map);
	return (NO_ERR);
}