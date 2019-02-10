/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:48:42 by radler            #+#    #+#             */
/*   Updated: 2017/11/16 19:54:35 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		ret;
	char	*pstr;

	i = 0;
	ret = -1;
	pstr = (char *)s;
	if (c == '\0')
		return (pstr + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			ret = i;
		i++;
	}
	if (ret == -1)
		return (NULL);
	return (pstr + ret);
}
