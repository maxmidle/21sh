/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnconc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 21:50:52 by radler            #+#    #+#             */
/*   Updated: 2018/05/28 17:11:16 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnconc(char **s1, size_t ls1, char *s2, size_t ls2)
{
	char	*tmp;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (ls1 > 0)
		tmp = ft_strndup(*s1, ls1);
	ft_strdel(s1);
	*s1 = (char *)malloc(sizeof(char) * (ls1 + ls2 + 1));
	while (i < ls1)
	{
		s1[0][i] = tmp[i];
		i++;
	}
	if (ls1 > 0)
		ft_strdel(&tmp);
	while (y < ls2)
	{
		s1[0][i + y] = s2[y];
		y++;
	}
	s1[0][i + y] = '\0';
	return (*s1);
}
