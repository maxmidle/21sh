/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:29:18 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:29:22 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		getminsize(char *argform)
{
	int i;

	i = 0;
	while (argform[i])
	{
		if (argform[i] >= '1' && argform[i] <= '9')
		{
			if (i > 0 && argform[i - 1] == '.')
			{
				while (argform[i] && ft_isdigit(argform[i]))
					i++;
			}
			else
				return (ft_atoi(&argform[i]));
		}
		i++;
	}
	return (0);
}

char	*handleminsize(int minsize, char *argform, char *str)
{
	if (ft_strstr(argform, "-"))
	{
		while ((int)ft_strlen(str) < minsize)
			ft_strconc(&str, " ");
	}
	else
	{
		while ((int)ft_strlen(str) < minsize)
			ft_strbackconc(&str, " ");
	}
	return (str);
}
