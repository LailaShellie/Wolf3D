/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:33:58 by lshellie          #+#    #+#             */
/*   Updated: 2019/08/15 20:34:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			ft_free_mas(char **mas, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(mas[i]);
		++i;
	}
	free(mas);
	return (0);
}
