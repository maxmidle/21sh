/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:49:01 by radler            #+#    #+#             */
/*   Updated: 2018/07/04 13:59:52 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft/libft.h"
# include <stdlib.h>

int		ft_printf(const char *format, ...);
char	*getarg(char *argform, va_list ap);
int		getargflag(const char *format, int *i, char **str, va_list ap);
void	ft_putspecstr(char *str);
int		ft_error(char **argform);

char	**argtabinit();
char	*getargtype(char *argform);
char	*getargform(const char *format);
char	*ptrfuninit(int i, char *argform, va_list ap);

char	*ft_itoa_base(unsigned long long value, unsigned long long base);
char	*ft_negitoa(long long value);

char	*handleflag(char *argform, char *str);
char	*preczero(char *str, char *argform);

int		getprec(char *argform);
char	*handleprec(int prec, char *argform, char *str);
char	*handlenegprec(int prec, char *str);

int		is_zero(char *argform);
char	*handlezero(int len, char *argform, char *str, int prec);

char	*handlehashtag(int prec, char *argform, char *str);

char	*handlespaceplus(int prec, char *argform, char *str);

int		getminsize(char *argform);
char	*handleminsize(int minsize, char *argform, char *str);

int		ft_isarg(char c);
int		ft_isnumconv(char c);
int		ft_isconv(char c);

char	*argtype_int(char *argtype, va_list ap);
char	*argtype_uint(char *argtype, va_list ap);
char	*argtype_charchar(char *argtype, va_list ap);
char	*argtype_void(char *argtype, va_list ap);
char	*argtype_short(char *argtype, va_list ap);
char	*argtype_char(char *argtype, va_list ap);
char	*argtype_long(char *argtype, va_list ap);
char	*argtype_longlong(char *argtype, va_list ap);
char	*argtype_ushort(char *argtype, va_list ap);
char	*argtype_uchar(char *argtype, va_list ap);
char	*argtype_ulong(char *argtype, va_list ap);
char	*argtype_ulonglong(char *argtype, va_list ap);
char	*argtype_intmax_t(char *argtype, va_list ap);
char	*argtype_uintmax_t(char *argtype, va_list ap);
char	*argtype_size_t(char *argtype, va_list ap);
char	*argtype_wint_t(char *argtype, va_list ap);
char	*argtype_wchar_t(char *argtype, va_list ap);
char	*ft_witoa(wint_t nbr);
char	*handlelocale(wchar_t *arg, char **str);
char	*ft_werror(char **buff, char **str);
#endif
