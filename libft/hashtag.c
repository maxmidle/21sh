/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:26:19 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:26:21 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handlehashtag(int prec, char *argform, char *str)
{
	char	last;
	int		i;

	i = 0;
	last = argform[ft_strlen(argform) - 1];
	if ((last == 'x' || last == 'X') && ft_strcmp(str, "0"))
	{
		while (str[i] == '0')
			i++;
		if (i == 0 || prec > -1)
			ft_strbackconc(&str, "0x");
		else if (i == 1)
		{
			str[0] = 'x';
			ft_strbackconc(&str, "0");
		}
		else if (i > 1)
			str[1] = 'x';
		if (last == 'X')
			str[1] -= 32;
	}
	if (last == 'o' && str[0] != '0')
		ft_strbackconc(&str, "0");
	return (str);
}
