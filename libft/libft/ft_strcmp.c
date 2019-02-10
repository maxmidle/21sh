/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:56:27 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 21:38:08 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char *ps1;
	const unsigned char *ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (*ps1 || *ps2)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		ps1++;
		ps2++;
	}
	return (0);
}
