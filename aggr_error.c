/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggr_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:02:44 by radler            #+#    #+#             */
/*   Updated: 2019/04/17 15:51:43 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		bad_aggr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] && str[i + 1] == '&')
		{
			if (bad_aggr_form(str, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int		bad_aggr_form(char *str, int i)
{
	int		nbr;
	int		size;
	char	*tmp;

	size = 0;
	tmp = NULL;
	while (str[i] && !ft_issep(str[i]) && !ft_isdigit(str[i]))
		i++;
	if (ft_isdigit(str[i]))
	{
		nbr = ft_atoi(&str[i]);
		tmp = ft_itoa(nbr);
	}
	else
		return (0);
	if (nbr < 0 || nbr > 2)
	{
		write(2, "-21sh: syntax error:\n\tunexpected file descriptor : '", 52);
		write(2, tmp, ft_strlen(tmp));
		write(2, "'\n", 2);
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}
