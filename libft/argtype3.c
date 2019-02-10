/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argtype3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:15:49 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:17:10 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*argtype_ulong(char *argtype, va_list ap)
{
	unsigned long	argu;
	char			last;

	last = argtype[ft_strlen(argtype) - 1];
	argu = va_arg(ap, unsigned long);
	argu = (unsigned long long)argu;
	if (last == 'O' || ft_strstr(argtype, "lo"))
		return (ft_itoa_base(argu, 8));
	else if (last == 'U' || ft_strstr(argtype, "lu"))
		return (ft_itoa_base(argu, 10));
	else if (ft_strstr(argtype, "lx"))
		return (ft_itoa_base(argu, 16));
	else if (ft_strstr(argtype, "lX"))
		return (ft_itoa_base(argu, 17));
	else if (ft_strstr(argtype, "lb"))
		return (ft_itoa_base(argu, 2));
	return (NULL);
}

char	*argtype_ulonglong(char *argtype, va_list ap)
{
	unsigned long long argu;

	argu = va_arg(ap, unsigned long long);
	if (ft_strstr(argtype, "llo"))
		return (ft_itoa_base(argu, 8));
	else if (ft_strstr(argtype, "llu"))
		return (ft_itoa_base(argu, 10));
	else if (ft_strstr(argtype, "llx"))
		return (ft_itoa_base(argu, 16));
	else if (ft_strstr(argtype, "llX"))
		return (ft_itoa_base(argu, 17));
	else if (ft_strstr(argtype, "llb"))
		return (ft_itoa_base(argu, 2));
	return (NULL);
}

char	*argtype_intmax_t(char *argtype, va_list ap)
{
	intmax_t argu;

	argu = va_arg(ap, intmax_t);
	if (ft_strstr(argtype, "jd") || ft_strstr(argtype, "ji"))
	{
		if (argu >= 0)
			return (ft_itoa_base((unsigned long long)argu, 10));
		return (ft_negitoa((long long)argu));
	}
	return (NULL);
}

char	*argtype_uintmax_t(char *argtype, va_list ap)
{
	uintmax_t argu;

	argu = va_arg(ap, uintmax_t);
	argu = (unsigned long long)argu;
	if (ft_strstr(argtype, "jo"))
		return (ft_itoa_base(argu, 8));
	else if (ft_strstr(argtype, "ju"))
		return (ft_itoa_base(argu, 10));
	else if (ft_strstr(argtype, "jx"))
		return (ft_itoa_base(argu, 16));
	else if (ft_strstr(argtype, "jX"))
		return (ft_itoa_base(argu, 17));
	else if (ft_strstr(argtype, "jb"))
		return (ft_itoa_base(argu, 2));
	return (NULL);
}

char	*argtype_size_t(char *argtype, va_list ap)
{
	size_t argu;

	argu = va_arg(ap, size_t);
	if (ft_strstr(argtype, "zo"))
		return (ft_itoa_base((unsigned long long)argu, 8));
	else if (ft_strstr(argtype, "zu"))
		return (ft_itoa_base((unsigned long long)argu, 10));
	else if (ft_strstr(argtype, "zx"))
		return (ft_itoa_base((unsigned long long)argu, 16));
	else if (ft_strstr(argtype, "zX"))
		return (ft_itoa_base((unsigned long long)argu, 17));
	else if (ft_strstr(argtype, "zb"))
		return (ft_itoa_base((unsigned long long)argu, 2));
	return (NULL);
}
