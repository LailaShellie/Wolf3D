/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:09:37 by lshellie          #+#    #+#             */
/*   Updated: 2019/04/18 20:42:35 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	char	*begin;
	int		i;

	if (s == NULL)
		return (NULL);
	begin = (char *)s;
	while (begin[0] == ' ' || begin[0] == '\n' || begin[0] == '\t')
		begin++;
	if (begin[0] == '\0')
		return (ft_strnew(0));
	str = begin;
	i = ft_strlen(begin);
	while (str[i - 1] == ' ' || str[i - 1] == '\n' || str[i - 1] == '\t')
		i--;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i > 0)
	{
		str[i - 1] = begin[i - 1];
		i--;
	}
	return (str);
}
