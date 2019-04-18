/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:17:08 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:55:11 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_echo(t_cmd *comd)
{
	int	i;

	i = 1;
	if (comd->cmd[1] && !ft_strcmp(comd->cmd[1], "-n"))
		i++;
	while (comd->cmd && comd->cmd[i])
	{
		ft_putstr(comd->cmd[i]);
		if (comd->cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!comd->cmd[1] || ft_strcmp(comd->cmd[1], "-n"))
		ft_putchar('\n');
	if (!comd->next)
		ft_putstr("\x1b[32m");
}
