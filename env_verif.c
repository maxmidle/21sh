/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:21:03 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:21:04 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
		if ((cmd[i][y] != 'i' && cmd[i][y] != 'u') ||
			(cmd[i][y] == 'u' && !cmd[i + 1]))
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
		if (!cmd[i][y])
			ft_putendl("env : any options specified");
		else if (cmd[i][y] == 'u')
			write(2, "env : option requires an argument -- u\n", 39);
		else
			ft_printf("env: illegal option -- %c\n", cmd[i][y]);
		ft_putendl("usage: env [-i] [-u name] [name=value]");
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
