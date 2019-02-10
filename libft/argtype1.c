/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argtype1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:09:47 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:14:46 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*argtype_int(char *argtype, va_list ap)
{
	int last;
	int arg;

	last = ft_strlen(argtype) - 1;
	arg = va_arg(ap, int);
	if (argtype[last] == 'd' || argtype[last] == 'i')
	{
		if (arg >= 0)
			return (ft_itoa_base((unsigned long long)arg, 10));
		else
			return (ft_negitoa((long long)arg));
	}
	return (NULL);
}

char	*argtype_uint(char *argtype, va_list ap)
{
	int				last;
	unsigned int	arg;

	last = ft_strlen(argtype) - 1;
	arg = va_arg(ap, unsigned int);
	arg = (unsigned long long)arg;
	if (argtype[last] == 'o')
		return (ft_itoa_base(arg, 8));
	else if (argtype[last] == 'u')
		return (ft_itoa_base(arg, 10));
	else if (argtype[last] == 'x')
		return (ft_itoa_base(arg, 16));
	else if (argtype[last] == 'X')
		return (ft_itoa_base(arg, 17));
	else if (argtype[last] == 'b')
		return (ft_itoa_base(arg, 2));
	return (NULL);
}

char	*argtype_charchar(char *argtype, va_list ap)
{
	int		last;
	char	*arg;

	last = ft_strlen(argtype) - 1;
	arg = va_arg(ap, char *);
	if (!arg)
		return (ft_strdup("(null)"));
	if (argtype[last] == 's')
		return (ft_strdup(arg));
	return (NULL);
}

char	*argtype_void(char *argtype, va_list ap)
{
	int		last;
	void	*arg;

	last = ft_strlen(argtype) - 1;
	arg = va_arg(ap, void *);
	if (argtype[last] == 'p')
		return (ft_itoa_base((unsigned long long)arg, 16));
	return (NULL);
}

char	*argtype_short(char *argtype, va_list ap)
{
	short	arg;

	arg = (short)va_arg(ap, int);
	if (ft_strstr(argtype, "hi") || ft_strstr(argtype, "hd"))
	{
		if (arg >= 0)
			return (ft_itoa_base((unsigned long long)arg, 10));
		else
			return (ft_negitoa((long long)arg));
	}
	return (NULL);
}
