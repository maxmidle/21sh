/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:58:38 by radler            #+#    #+#             */
/*   Updated: 2017/11/14 15:43:50 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *pdst;
	char *psrc;

	pdst = (char *)dst;
	psrc = (char *)src;
	while (n--)
	{
		*pdst = *psrc;
		pdst++;
		psrc++;
	}
	return (dst);
}
