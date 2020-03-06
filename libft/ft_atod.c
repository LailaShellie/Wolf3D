/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:20:26 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:20:28 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static double	ft_fract(double res, char *str, int sign)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res += (str[i] - '0') /
				(double)(ft_fast_bin_pow(10, i + 1));
	}
	return (res * (double)sign);
}

double			ft_atod(char *str)
{
	int		i;
	int		sign;
	double	res;

	res = 0;
	i = -1;
	sign = 1;
	if (str[i + 1] == '-')
	{
		sign *= -1;
		++i;
	}
	while (str[++i])
	{
		if (str[i] == '.')
			return (ft_fract(res, &str[++i], sign));
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res = res * 10 + str[i] - '0';
	}
	return (res * (double)sign);
}
