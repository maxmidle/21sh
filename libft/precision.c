/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:25:04 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:25:06 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		getprec(char *argform)
{
	int i;

	i = 0;
	while (argform[i] && argform[i] != '.')
		i++;
	if (argform[i] == '.')
	{
		if (argform[i + 1] >= '0' && argform[i + 1] <= '9')
			return (ft_atoi(&argform[i + 1]));
		return (0);
	}
	return (-1);
}

char	*handleprec(int prec, char *argform, char *str)
{
	char last;
	char *buff;

	last = argform[ft_strlen(argform) - 1];
	prec = getprec(argform);
	if (last == 's' || last == 'S')
	{
		buff = ft_strndup(str, prec);
		free(str);
		str = buff;
	}
	if (last == 'd' || last == 'D' || last == 'i' || last == 'o'
		|| last == 'O' || last == 'u' || last == 'U' || last == 'x'
		|| last == 'X' || last == 'p' || last == 'b')
	{
		if (str[0] == '-')
			str = handlenegprec(prec, str);
		else
		{
			while ((int)ft_strlen(str) < prec)
				ft_strbackconc(&str, "0");
		}
	}
	return (str);
}

char	*handlenegprec(int prec, char *str)
{
	char	*tmp;

	tmp = ft_strdup(&str[1]);
	ft_strdel(&str);
	while ((int)ft_strlen(tmp) < prec)
		ft_strbackconc(&tmp, "0");
	str = ft_strdup("-");
	ft_strconc(&str, tmp);
	ft_strdel(&tmp);
	return (str);
}
