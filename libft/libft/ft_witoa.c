/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_witoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:52:41 by radler            #+#    #+#             */
/*   Updated: 2018/06/21 17:21:19 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_witoa(wint_t nbr)
{
	char	*str;
	char	*c;

	c = (char*)&nbr;
	if (nbr < 0 || nbr > 0x10ffff)
		return (NULL);
	if (nbr <= 0x7f)
		return (ft_strndup(c, 1));
	str = ft_strnew(4);
	if (nbr <= 0x7ff)
		str[0] = (char)(nbr / 64 + 192);
	else if (nbr <= 0xffff)
	{
		str[0] = (char)(nbr / (64 * 64) + 224);
		str[1] = (char)((nbr / 64) % 64 + 128);
	}
	else if (nbr <= 0x10ffff)
	{
		str[0] = (char)(nbr / (64 * 64 * 64) + 240);
		str[1] = (char)((nbr / (64 * 64)) % 64 + 128);
		str[2] = (char)((nbr / 64) % 64 + 128);
	}
	str[ft_strlen(str)] = (char)(nbr % 64 + 128);
	return (str);
}
