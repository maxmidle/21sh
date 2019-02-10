/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:58:01 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 19:33:42 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	str = NULL;
	if (!(str = ft_strdup(s)))
		return (NULL);
	while (str[i])
	{
		str[i] = f(str[i]);
		i++;
	}
	return (str);
}
