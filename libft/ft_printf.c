/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:47:35 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:37:17 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int		i;
	int		size;
	int		strsize;
	va_list	ap;
	char	*str;

	i = 0;
	size = 0;
	va_start(ap, format);
	while (format[i])
	{
		str = ft_strcdup(&format[i], '%');
		i += (int)ft_strlen(str);
		if (format[i] == '%')
		{
			if ((strsize = getargflag(format, &i, &str, ap)) < 0)
				return (ft_error(&str));
		}
		else
			strsize = (int)ft_strlen(str);
		size += (int)ft_strlen(str);
		ft_putspecstr(str);
		ft_strdel(&str);
	}
	return (size);
}

char	*getarg(char *argform, va_list ap)
{
	char	*argtype;
	char	**argtab;
	char	*str;
	int		i;

	i = 0;
	argtype = NULL;
	argtype = getargtype(argform);
	argtab = argtabinit();
	while (!ft_strstr(argtab[i], argtype))
		i++;
	if (i >= 17)
		return (NULL);
	str = ptrfuninit(i, argtype, ap);
	ft_freetab(argtab);
	ft_strdel(&argtype);
	return (str);
}

int		getargflag(const char *format, int *i, char **str, va_list ap)
{
	char	*argform;
	char	*buff;
	char	last;
	int		size;

	size = 0;
	buff = NULL;
	argform = getargform(&format[*i]);
	last = argform[ft_strlen(argform) - 1];
	if (ft_isarg(last) || last == '%')
	{
		if (argform[ft_strlen(argform) - 1] == '%')
			buff = ft_strdup("%");
		else if (!(buff = getarg(argform, ap)))
			return (ft_error(&argform));
		buff = handleflag(argform, buff);
		ft_strconc(str, buff);
		size += (int)ft_strlen(*str);
		*i += (int)(ft_strlen(argform) + 1);
		ft_strdel(&buff);
	}
	else
		*i += (int)ft_strlen(argform) + 1;
	ft_strdel(&argform);
	return (size);
}

void	ft_putspecstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			ft_putchar(0);
		else
			ft_putchar(str[i]);
		i++;
	}
}

int		ft_error(char **argform)
{
	ft_strdel(argform);
	return (-1);
}
