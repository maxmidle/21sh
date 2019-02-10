/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:06:19 by radler            #+#    #+#             */
/*   Updated: 2017/11/16 19:23:10 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	d;
	unsigned char	*ps;

	ps = (unsigned char *)s;
	d = (unsigned char)c;
	while (n--)
	{
		if (d == *ps)
			return (ps);
		ps++;
	}
	return (NULL);
}
