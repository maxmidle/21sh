/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:47:40 by radler            #+#    #+#             */
/*   Updated: 2018/05/28 17:00:13 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *pstr;

	pstr = NULL;
	if (s == NULL)
		return (NULL);
	pstr = (char *)s;
	while (*pstr != c)
	{
		if (*pstr == '\0' && c != '\0')
			return (NULL);
		pstr++;
	}
	return (pstr);
}
