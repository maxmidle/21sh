/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:19:12 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 09:02:24 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	run_bin(char **command, char **envorig, char **envexec)
{
	char	**bpath;
	int		y;

	y = 0;
	if (ft_strchr(command[0], '/') && !access(command[0], X_OK))
		return (exec_bin(command[0], command, envexec));
	if ((y = env_search(envorig, "PATH")) == -1)
		return (0);
	bpath = ft_strsplit(&envorig[y][5], ':');
	y = 0;
	while (bpath[y])
	{
		ft_strconc(&bpath[y], "/");
		ft_strconc(&bpath[y], command[0]);
		if (!access(bpath[y], X_OK))
		{
			exec_bin(bpath[y], command, envexec);
			ft_freetab(bpath);
			return (1);
		}
		y++;
	}
	ft_freetab(bpath);
	return (0);
}

int	exec_bin(char *cmd, char **command, char **envexec)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		execve(cmd, command, envexec);
		exit(0);
	}
	wait(0);
	return (1);
}

void	ft_kill(int prevpid, char **envorig)
{
	char **cmd;
	pid_t pid;

	pid = fork();
	cmd = (char **)malloc(sizeof(char *) * 4);
	cmd[0] = ft_strdup("pkill");
	cmd[1] = ft_strdup("-P");
	cmd[2] = ft_itoa(prevpid);
	cmd[3] = NULL;
	if (!pid)
	{
		execve("/usr/bin/pkill", cmd, envorig);
		exit(0);
	}
	wait(0);
	ft_freetab(cmd);
}
