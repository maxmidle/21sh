/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:22:36 by radler            #+#    #+#             */
/*   Updated: 2019/04/18 16:46:55 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**run_cmd(t_cmd *comd, char **envorig, char **envexec)
{
	int	i;

	if (!comd->cmd)
		return (exit_runcmd(envorig, 0));
	if ((i = env_verif(comd->cmd, 0)) == -1)
	{
		i = ft_tablen(comd->cmd);
		ft_putstr("\x1b[31m");
	}
	if (comd->cmd[i] && ft_isbuiltins(comd->cmd[i])
		&& ft_strcmp(comd->cmd[i], "exit"))
		envorig = run_builtins(comd, envorig);
	else if (comd->cmd[i] && !run_bin(comd, envorig, envexec))
	{
		if (ft_strcmp(comd->cmd[i], "exit"))
		{
			write(2, "-21sh: ", 7);
			write(2, comd->cmd[i], ft_strlen(comd->cmd[i]));
			write(2, ": command not found \n", 21);
		}
		else
			return (exit_runcmd(envorig, 1));
	}
	return (exit_runcmd(envorig, 0));
}

char	**run_builtins(t_cmd *comd, char **envorig)
{
	if (!ft_strcmp(comd->cmd[0], "cd"))
		ft_cd(comd, envorig);
	else if (!ft_strcmp(comd->cmd[0], "echo"))
		ft_echo(comd);
	else if (!ft_strcmp(comd->cmd[0], "setenv"))
	{
		if (!comd->cmd[1] || !ft_strchr(comd->cmd[1], '='))
			builtin_error(comd, 1);
		else
		{
			envorig = ft_setenv(envorig, comd->cmd[1]);
			builtin_error(comd, 3);
		}
	}
	else if (!ft_strcmp(comd->cmd[0], "unsetenv"))
	{
		if (comd->cmd[1])
		{
			envorig = ft_unsetenv(envorig, comd->cmd[1]);
			builtin_error(comd, 3);
		}
		else
			builtin_error(comd, 2);
	}
	return (envorig);
}

void	builtin_error(t_cmd *comd, int mode)
{
	if (mode == 1)
	{
		write(2, "usage: setenv [VAR=value]\n", 26);
		if (!comd->next)
			ft_putstr("\x1b[31m");
	}
	else if (mode == 2)
	{
		write(2, "usage: unsetenv [VAR]\n", 22);
		if (!comd->next)
			ft_putstr("\x1b[31m");
	}
	else if (mode == 3)
	{
		if (!comd->next)
			ft_putstr("\x1b[32m");
	}
}

char	**exit_runcmd(char **envorig, int mode)
{
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
	if (!ft_strcmp(command, "unsetenv") || !ft_strcmp(command, "setenv")
			|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "exit"))
		return (2);
	return (0);
}
