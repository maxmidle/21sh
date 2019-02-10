/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:17:08 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:17:10 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ft_echo(char **command)
{
	int	i;

	i = 1;
	if (command[1] && !ft_strcmp(command[1], "-n"))
		i++;
	while (command && command[i])
	{
		ft_putstr(command[i]);
		if (command[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!command[1] || ft_strcmp(command[1], "-n"))
		ft_putchar('\n');
}
