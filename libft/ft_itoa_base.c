/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:06:20 by radler            #+#    #+#             */
/*   Updated: 2018/06/21 19:02:35 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(unsigned long long value, unsigned long long base)
{
	char	*hexstr;
	char	*ret;
	int		buff;

	if (base < 2 || base > 17)
		return (NULL);
	ret = ft_strnew(0);
	hexstr = ft_strdup("0123456789abcdef");
	if (base == 17)
	{
		hexstr = ft_upcase(hexstr);
		base--;
	}
	while (value >= base)
	{
		buff = (value % base);
		ret = ft_strnconc(&ret, ft_strlen(ret), &hexstr[buff], 1);
		value /= base;
	}
	buff = value;
	ft_strnconc(&ret, ft_strlen(ret), &hexstr[buff], 1);
	ret = ft_strrev(ret);
	free(hexstr);
	return (ret);
}

char	*ft_negitoa(long long value)
{
	int					size;
	char				*str;
	unsigned long long	tmp;

	size = 2;
	tmp = value * -1;
	if (value == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	while (tmp >= 10)
	{
		size++;
		tmp /= 10;
	}
	str = ft_strnew(size);
	value *= -1;
	if (value <= 0 || str == NULL)
		return (NULL);
	while (size--)
	{
		str[size] = value % 10 + 48;
		value /= 10;
	}
	str[size] = value + 48;
	str[0] = '-';
	return (str);
}
