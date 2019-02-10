/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:09:25 by radler            #+#    #+#             */
/*   Updated: 2017/11/16 19:28:47 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*pdst;
	char			*psrc;

	c = (char)c;
	pdst = (char *)dst;
	psrc = (char *)src;
	while (n--)
	{
		*pdst = *psrc;
		if (*psrc == c)
			return (pdst + 1);
		pdst++;
		psrc++;
	}
	return (NULL);
}
