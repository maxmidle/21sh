/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:22:36 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:22:52 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	**run_cmd(char **command, char **envorig, char **envexec)
{
	int	i;

	if (!command)
		return (envorig);
	if ((i = env_verif(command, 0)) == -1)
		i = ft_tablen(command);
	if (command[i] && ft_isbuiltins(command[i]))
		envorig = run_builtins(command, envorig);
	else if (command[i] && !run_bin(&command[i], envorig, envexec))
	{
		if (ft_strcmp(command[i], "exit"))
		{
			write(2, "-21sh: ", 7);
			write(2, command[i], ft_strlen(command[i]));
			write(2, ": command not found \n", 21);
		}
		else
		{
			ft_freetab(envorig);
			return (NULL);
		}
	}
	return (envorig);
}

char	**run_builtins(char **command, char **envorig)
{
	if (!ft_strcmp(command[0], "cd"))
		ft_cd(command, envorig);
	else if (!ft_strcmp(command[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command[0], "setenv"))
	{
		if (!command[1] || !ft_strchr(command[1], '='))
			write(2, "usage: setenv [VAR=value]\n", 26);
		else
			envorig = ft_setenv(envorig, command[1]);
	}
	else if (!ft_strcmp(command[0], "unsetenv"))
	{
		if (command[1])
			envorig = ft_unsetenv(envorig, command[1]);
		else
			write(2, "usage: unsetenv [VAR]\n", 22);
	}
	return (envorig);
}

int		ft_isbuiltins(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "unsetenv") ||
		!ft_strcmp(command, "setenv") || !ft_strcmp(command, "cd"))
		return (1);
	return (0);
}
