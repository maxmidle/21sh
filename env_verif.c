/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:21:03 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:54:46 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	env_verif(char **cmd, int mode)
{
	int i;
	int stop;

	i = 1;
	stop = 0;
	if (ft_strcmp(cmd[0], "env"))
		return (0);
	while (!stop && cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			if (env_param_error(cmd, i))
				return (env_error_print(cmd, i, mode));
			if (ft_strchr(cmd[i], 'u'))
				i++;
		}
		else if (ft_strcmp(cmd[i], "env") && !ft_strchr(cmd[i], '='))
		{
			stop = 1;
			i--;
		}
		i++;
	}
	return (i);
}

int	env_param_error(char **cmd, int i)
{
	int y;

	y = 1;
	if (!cmd[i][y])
		return (1);
	while (cmd[i][y])
	{
		if ((cmd[i][y] != 'i' && cmd[i][y] != 'u')
			|| (cmd[i][y] == 'u' && !cmd[i + 1]))
			return (y);
		y++;
	}
	return (0);
}

int	env_error_print(char **cmd, int i, int mode)
{
	int y;

	y = env_param_error(cmd, i);
	if (mode)
	{
		write(2, "env: ", 5);
		if (!cmd[i][y])
			write(2, "any options specified", 21);
		else if (cmd[i][y] == 'u')
			write(2, "option requires an argument -- u", 32);
		else
		{
			write(2, "illegal option -- ", 18);
			write(2, &cmd[i][y], 1);
		}
		write(2, "\nusage: env [-i] [-u name] [name=value]\n", 40);
	}
	return (-1);
}

int	env_search(char **environ, char *var)
{
	int i;

	i = 0;
	while (environ[i] && !(ft_strstr(environ[i], var)))
		i++;
	if (environ[i])
		return (i);
	else
		return (-1);
}

void	env_rederror(char *command)
{
	if (!command)
		ft_putstr("\x1b[32m");
}
