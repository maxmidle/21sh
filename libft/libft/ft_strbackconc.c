/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbackconc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:40:06 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:40:09 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strbackconc(char **s1, char *s2)
{
	char	*tmp;

	if (!*s1)
		*s1 = ft_strnew(0);
	if (!s2)
		return ;
	tmp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strdup(s2);
	ft_strconc(s1, tmp);
	ft_strdel(&tmp);
}
