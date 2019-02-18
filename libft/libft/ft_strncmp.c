/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:46:56 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 21:38:41 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char *ps1;
	const unsigned char *ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ps1 && ps2 && i < n)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
			
		i++;
		ps1++;
		ps2++;
	}
	if (i >= n)
		return (0);
	return (*ps1 - *ps2);
}
