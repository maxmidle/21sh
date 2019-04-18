/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:19:12 by radler            #+#    #+#             */
/*   Updated: 2019/04/18 16:35:20 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	run_bin(t_cmd *comd, char **envorig, char **envexec)
{
	char	**bpath;
	int		y;

	y = 0;
	if (ft_strchr(comd->cmd[0], '/') && !access(comd->cmd[0], X_OK))
		return (exec_bin(comd->cmd[0], comd, envexec));
	if ((y = env_search(envorig, "PATH")) == -1)
		return (0);
	bpath = ft_strsplit(&envorig[y][5], ':');
	y = 0;
	while (bpath[y])
	{
		ft_strconc(&bpath[y], "/");
		ft_strconc(&bpath[y], comd->cmd[0]);
		if (!access(bpath[y], X_OK))
		{
			exec_bin(bpath[y], comd, envexec);
			ft_freetab(bpath);
			return (1);
		}
		y++;
	}
	ft_freetab(bpath);
	return (0);
}

int	exec_bin(char *cmd, t_cmd *comd, char **envexec)
{
	pid_t	pid;
	int		errwait;

	errwait = 0;
	pid = fork();
	if (!pid)
	{
		execve(cmd, comd->cmd, envexec);
		ft_exit_proc(envexec);
	}
	wait(&errwait);
	if (!comd->next)
	{
		dup2(comd->save_in, 1);
		if (errwait)
			ft_putstr("\x1b[31m");
		else
			ft_putstr("\x1b[32m");
	}
	return (1);
}
