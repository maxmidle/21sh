/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:25:18 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 10:32:44 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdel(char *str, int i)
{
	char *tmp;
	
	if (i > (int)ft_strlen(str) - 1 || i < 0)
		return (str);
	if (i == 0 && str[1])
		tmp = ft_strdup(&str[1]);
	else
	{
		tmp = ft_strndup(str, i);
		if (str[i + 1])
			ft_strconc(&tmp, &str[i + 1]);
	}
	free(str);
	return (tmp);
}
