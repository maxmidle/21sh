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

char	**run_cmd(t_cmd *comd, char **envorig)
{
	char **envexec;
	int	i;

	envexec = get_envexec(comd, envorig);
	if (!comd->cmd)
		return (exit_runcmd(envorig, envexec, 0));
	if ((i = env_verif(comd->cmd, 0)) == -1)
		i = ft_tablen(comd->cmd);
	if (comd->cmd[i] && ft_isbuiltins(comd->cmd[i]))
		envorig = run_builtins(comd->cmd, envorig);
	else if (comd->cmd[i] && !run_bin(&comd->cmd[i], envorig, envexec))
	{
		if (ft_strcmp(comd->cmd[i], "exit"))
		{
			write(2, "-21sh: ", 7);
			write(2, comd->cmd[i], ft_strlen(comd->cmd[i]));
			write(2, ": command not found \n", 21);
		}
		else
			return (exit_runcmd(envorig, envexec, 1));
	}
	return (exit_runcmd(envorig, envexec, 0));
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

char	**exit_runcmd(char **envorig, char **envexec, int mode)
{
	ft_freetab(envexec);
	if (mode == 1)
	{
		ft_freetab(envorig);
		return (NULL);
	}
	return (envorig);
}

int		ft_isbuiltins(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "unsetenv") ||	!ft_strcmp(command, "setenv") ||
		 !ft_strcmp(command, "cd") || !ft_strcmp(command, "exit"))
		return (2);
	return (0);
}
