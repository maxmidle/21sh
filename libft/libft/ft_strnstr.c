/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:47:09 by radler            #+#    #+#             */
/*   Updated: 2017/11/30 15:58:33 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	clen;

	i = 0;
	if (!needle[0])
		return ((char *)&haystack[i]);
	while (haystack[i] && len)
	{
		y = 0;
		clen = len;
		while (haystack[i + y] == needle[y] && clen)
		{
			y++;
			if (!needle[y])
				return ((char *)&haystack[i]);
			clen--;
		}
		i++;
		len--;
	}
	return (NULL);
}
