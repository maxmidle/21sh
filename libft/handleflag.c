/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:30:42 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:30:44 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handleflag(char *argform, char *str)
{
	int		prec;
	int		min;
	char	last;

	last = argform[ft_strlen(argform) - 1];
	prec = getprec(argform);
	min = getminsize(argform);
	if (argform[ft_strlen(argform) - 1] == 'p')
		min -= 2;
	if (ft_strstr(argform, ".") && prec > -1)
		str = handleprec(prec, argform, str);
	if (is_zero(argform) && !ft_strstr(argform, "-"))
		str = handlezero(min, argform, str, prec);
	if (ft_strstr(argform, "#"))
		str = handlehashtag(prec, argform, str);
	if (ft_strstr(argform, "p"))
		ft_strbackconc(&str, "0x");
	if (ft_strstr(argform, "+") || ft_strstr(argform, " "))
		str = handlespaceplus(prec, argform, str);
	if (ft_isnumconv(last) && !ft_strcmp(str, "0") && prec == 0)
		str = preczero(str, argform);
	if (min > 0)
		str = handleminsize(min, argform, str);
	return (str);
}

char	*preczero(char *str, char *argform)
{
	if (!ft_strstr(argform, "#") || !ft_strstr(argform, "o"))
	{
		free(str);
		str = ft_strdup("");
	}
	return (str);
}
