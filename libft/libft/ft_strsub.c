/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:24:32 by radler            #+#    #+#             */
/*   Updated: 2017/12/01 16:58:04 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*scpy;
	int		i;

	i = 0;
	scpy = NULL;
	if (!s || start + len > ft_strlen(s))
		return (NULL);
	if (!len)
		return (NULL);
	if (!(scpy = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len--)
	{
		scpy[i] = s[start];
		i++;
		start++;
	}
	scpy[i] = '\0';
	return (scpy);
}
