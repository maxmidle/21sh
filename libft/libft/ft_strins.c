/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:41:19 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:41:24 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strins(char **dest, char *instr, size_t i)
{
	char *tmp;

	tmp = NULL;
	if (i >= ft_strlen(*dest))
		ft_strconc(dest, instr);
	else
	{
		tmp = ft_strsub(*dest, 0, i);
		if (tmp)
		{
			ft_strconc(&tmp, instr);
			ft_strconc(&tmp, &dest[0][i]);
		}
		free(*dest);
		*dest = tmp;
	}
}
