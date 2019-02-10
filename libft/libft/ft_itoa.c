/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:30:18 by radler            #+#    #+#             */
/*   Updated: 2017/11/16 20:32:05 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int len;
	int size;

	size = 1;
	len = 1;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	if (n == 0)
		return (2);
	while (len <= n && len <= 1000000000)
	{
		size++;
		len *= 10;
	}
	return (size);
}

static char	*minnbr(char *str)
{
	ft_strcpy(str, "-2147483648");
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	neg = 0;
	i = ft_size(n) - 1;
	str = NULL;
	if (!(str = (char *)malloc(sizeof(char) * ft_size(n))))
		return (NULL);
	if (n == -2147483648)
		return (minnbr(str));
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	str[i] = '\0';
	while (i--)
	{
		str[i] = n % 10 + 48;
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
