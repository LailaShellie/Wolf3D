/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:38:46 by lshellie          #+#    #+#             */
/*   Updated: 2020/01/13 17:38:47 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_num(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

int				ft_isdouble(char *s)
{
	int		i;

	i = 0;
	if (!s || s[i] == 0)
		return (0);
	if (s[i + 1] != 0 && s[i] == '-')
		++i;
	while (s[i])
	{
		if (s[i] == '.')
			return (is_num(&s[++i]));
		if (s[i] < '0' || s[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

int				ft_isnumber(char *s)
{
	int		i;

	i = 0;
	if (!s || s[i] == 0)
		return (0);
	if (s[i + 1] != 0 && (s[i] == '+' || s[i] == '-'))
		++i;
	return (is_num(&s[i]));
}
