/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:58:50 by radler            #+#    #+#             */
/*   Updated: 2018/05/28 15:12:35 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;

	if (!(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	ft_strcpy(str, s);
	str[ft_strlen(s)] = '\0';
	return (str);
}
