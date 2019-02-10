/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:10:00 by radler            #+#    #+#             */
/*   Updated: 2017/11/30 17:25:45 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*pdest;
	const char	*psrc;
	size_t		n;
	size_t		destlen;

	pdest = dest;
	psrc = src;
	n = size;
	while (n-- != 0 && *pdest != '\0')
		pdest++;
	destlen = pdest - dest;
	n = size - destlen;
	if (n == 0)
		return (destlen + ft_strlen(psrc));
	while (*psrc != '\0')
	{
		if (n != 1)
		{
			*pdest++ = *psrc;
			n--;
		}
		psrc++;
	}
	*pdest = '\0';
	return (destlen + (psrc - src));
}
