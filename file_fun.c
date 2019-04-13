/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:27:31 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:57:25 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_file(t_cmd *comd)
{
	int		fd;
	char	buff[50];

	fd = 0;
	if (!ft_strcmp(comd->file_out[1], ">"))
	{
		fd = open(comd->file_out[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (access(comd->file_out[0], W_OK))
			return (file_error(comd->file_out[0]));
	}	
	else if (!ft_strcmp(comd->file_out[1], ">>"))
	{	
		fd = open(comd->file_out[0], O_RDWR | O_CREAT, 0644);
		if (access(comd->file_out[0], W_OK))
			return (file_error(comd->file_out[0]));
		while (read(fd, buff, 50))
			fd = fd + 0;
	}
	return (fd);
}

int	create_file(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	if (list->file_in && access(list->file_in, R_OK))
		return (file_error(list->file_in));
	if (list->file_out)
		list->fd_out = handle_file(list);
	if (!list->fd_out)
		return (0);
	list = list->next;
	while (list && list->is_pipe)
	{
		if (list->file_in && access(list->file_in, R_OK))
			return (file_error(list->file_in));
		if (list->file_out)
			list->fd_out = handle_file(list);
		if (!list->fd_out)
			return (0);
		list = list->next;
	}
	return (1);
}


int	file_error(char *filename)
{
	int error;

	error = errno;
	write (2, "-21sh: ", 7);
	write (2, filename, ft_strlen(filename));
	if (errno == EACCES)
		write (2, ": Permission denied\n", 20);
	if (errno == ENOENT)
		write (2, ": No such file or directory\n", 28);
	return (0);
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
