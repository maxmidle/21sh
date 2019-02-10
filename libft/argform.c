/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:21:42 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 12:27:40 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*getargform(const char *format)
{
	int		i;
	char	*argform;

	i = 1;
	argform = NULL;
	while (format[i] && (!(ft_isalpha(format[i])) || ft_isconv(format[i])) &&
			format[i] != '%')
		i++;
	if (!ft_isarg(format[i]) && format[i] != '%')
	{
		if (i == 1)
			return (ft_strnew(0));
		i = 1;
		while (!ft_isalpha(format[i]) && format[i])
			i++;
		i--;
	}
	argform = ft_strsub(format, 1, i);
	if (!format[i])
		return (NULL);
	return (argform);
}

char	*getargtype(char *argform)
{
	char	*argtype;
	char	last;

	last = argform[ft_strlen(argform) - 1];
	if (!argform)
		return (NULL);
	if (ft_strstr(argform, "ll"))
		argtype = ft_strdup("ll");
	else if (ft_strstr(argform, "l"))
		argtype = ft_strdup("l");
	else if (ft_strstr(argform, "z"))
		argtype = ft_strdup("z");
	else if (ft_strstr(argform, "j"))
		argtype = ft_strdup("j");
	else if (ft_strstr(argform, "hh"))
		argtype = ft_strdup("hh");
	else if (ft_strstr(argform, "h"))
		argtype = ft_strdup("h");
	else
		argtype = ft_strnew(0);
	ft_strnconc(&argtype, ft_strlen(argtype), &last, 1);
	return (argtype);
}

char	**argtabinit(void)
{
	char **argtab;

	argtab = malloc(sizeof(char *) * 18);
	argtab[0] = ft_strdup("d i");
	argtab[1] = ft_strdup("o u x X b");
	argtab[2] = ft_strdup("s");
	argtab[3] = ft_strdup("p");
	argtab[4] = ft_strdup("hd hi");
	argtab[5] = ft_strdup("hhd hhi");
	argtab[6] = ft_strdup("D ld li");
	argtab[7] = ft_strdup("lld lli zd zi");
	argtab[8] = ft_strdup("O U hU hO lo lu lx lX lb");
	argtab[9] = ft_strdup("ho hu hx hX hb");
	argtab[10] = ft_strdup("c hho hhu hhx hhX hhb");
	argtab[11] = ft_strdup("llo llu llx llX llb");
	argtab[12] = ft_strdup("jd ji");
	argtab[13] = ft_strdup("jo ju jx jX jb");
	argtab[14] = ft_strdup("zo zu zx zX zb");
	argtab[15] = ft_strdup("C lc");
	argtab[16] = ft_strdup("S ls");
	argtab[17] = NULL;
	return (argtab);
}

char	*ptrfuninit(int i, char *argform, va_list ap)
{
	char	*str;
	char	*(**f)(char *, va_list);

	f = malloc(sizeof(*f) * 18);
	f[0] = argtype_int;
	f[1] = argtype_uint;
	f[2] = argtype_charchar;
	f[3] = argtype_void;
	f[4] = argtype_short;
	f[5] = argtype_char;
	f[6] = argtype_long;
	f[7] = argtype_longlong;
	f[8] = argtype_ulong;
	f[9] = argtype_ushort;
	f[10] = argtype_uchar;
	f[11] = argtype_ulonglong;
	f[12] = argtype_intmax_t;
	f[13] = argtype_uintmax_t;
	f[14] = argtype_size_t;
	f[15] = argtype_wint_t;
	f[16] = argtype_wchar_t;
	f[17] = NULL;
	str = f[i](argform, ap);
	free(f);
	return (str);
}
