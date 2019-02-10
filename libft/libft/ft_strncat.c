/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:48:12 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 16:35:00 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	while (dest[i])
		i++;
	while (y < n && src[y])
	{
		dest[i + y] = src[y];
		y++;
	}
	dest[i + y] = '\0';
	return (dest);
}
