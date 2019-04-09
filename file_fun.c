/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:27:31 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 17:30:00 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		handle_file(t_cmd *comd, char **envorig)
{
	pid_t	pid;
	int		fd;
	char	**arg;
	char	buff[50];

	pid = 1;
	arg = malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("/bin/rm");
	arg[1] = ft_strdup(comd->file_out[0]);
	arg[2] = NULL;
	if (!ft_strcmp(comd->file_out[1], ">") && !access(comd->file_out[0], F_OK))
		pid = fork();
	if (!pid)
	{
		run_bin(arg, envorig, envorig, 1);
		ft_exit_proc(envorig);
	}
	wait(0);
	ft_freetab(arg);
	fd = open(comd->file_out[0], O_RDWR | O_CREAT);
	perm_file(comd, envorig);
	if (!ft_strcmp(comd->file_out[1], ">>"))
		while (read(fd, buff, 50))
			pid++;
	return (fd);
}

void	create_file(t_cmd *comd, char **envorig)
{
	t_cmd *list;

	list = comd;
	if (list->file_out)
		list->fd_out = handle_file(list, envorig);
	list = list->next;
	while (list && list->is_pipe)
	{
		if (list->file_out)
			list->fd_out = handle_file(list, envorig);
		list = list->next;
	}
}

void	perm_file(t_cmd *comd, char **envorig)
{
	char	**arg;
	pid_t	pid;

	pid = 1;
	arg = malloc(sizeof(char *) * 4);
	arg[0] = ft_strdup("/bin/chmod");
	arg[1] = ft_strdup("644");
	arg[2] = ft_strdup(comd->file_out[0]);
	arg[3] = NULL;
	if (!access(comd->file_out[0], F_OK))
		pid = fork();
	if (!pid)
	{
		run_bin(arg, envorig, envorig, 1);
		ft_exit_proc(envorig);
	}
	wait(0);
	ft_freetab(arg);
}

void	ft_kill(int prevpid, char **envorig)
{
	char	**cmd;
	pid_t	pid;

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

void	ft_exit_proc(char **envorig)
{
	char **cmd;

	cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("env");
	cmd[1] = ft_strdup("-i");
	cmd[2] = NULL;
	execve("/usr/bin/env", cmd, envorig);
}
