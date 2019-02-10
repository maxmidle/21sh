/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:25:53 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:25:55 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_zero(char *argform)
{
	int i;

	i = 0;
	while (argform[i])
	{
		if (argform[i] == '0')
		{
			if (i == 0 || !ft_isdigit(argform[i - 1]))
			{
				if (argform[i - 1] != '.')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*handlezero(int len, char *argform, char *str, int prec)
{
	int		i;
	char	last;

	last = argform[ft_strlen(argform) - 1];
	i = 0;
	if (ft_isnumconv(last) && prec > -1)
		return (str);
	while ((int)ft_strlen(str) < len)
		ft_strbackconc(&str, "0");
	while (str[i] == '0')
		i++;
	if (last == 'd' || last == 'D' || last == 'i')
	{
		if (str[i] == '-')
		{
			str[i] = '0';
			str[0] = '-';
		}
	}
	return (str);
}
