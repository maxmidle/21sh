/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_proc_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:32:56 by radler            #+#    #+#             */
/*   Updated: 2019/04/15 09:13:41 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**run_full_cmd(t_cmd *comd, char **envorig)
{
	char	**envexec;
	t_cmd	*list;

	list = comd;
	while (list && envorig)
	{
		envexec = get_envexec(list, envorig);
		if (ft_isbuiltins(list->cmd[0]) != 2)
		{
			if (create_file(list))
				run_proc_cmd(list, envorig, envexec, 0);
		}
		else
		{
			ft_dupfd(list);
			if (create_file(list))
				envorig = run_cmd(list, envorig, envexec);
		}
		while (list->next && list->next->is_pipe)
			list = list->next;
		list = list->next;
		ft_freetab(envexec);
	}
	return (envorig);
}

void	run_proc(t_cmd *list, char **envorig, char **envexec, pid_t prevpid)
{
	ft_dupfd(list);
	envorig = run_cmd(list, envorig, envexec);
	if (prevpid != 0)
		ft_kill(prevpid, envorig);
	ft_exit_proc(envorig);
}

void	run_proc_cmd(t_cmd *comd, char **envorig, char **envexec, pid_t prepid)
{
	t_cmd	*list;
	int		fd[2];
	pid_t	pid;

	list = comd;
	if (list->next && list->next->is_pipe)
	{
		pipe(fd);
		list->next->fd_in = fd[0];
		list->fd_out = fd[1];
	}
	pid = fork();
	if (!pid)
		run_proc(list, envorig, envexec, prepid);
	if ((list->next && list->next->is_pipe))
		close(list->fd_out);
	if (list->next && list->next->is_pipe)
		run_proc_cmd(list->next, envorig, envexec, pid);
	waitpid(pid, 0, 0);
}

char	**get_envexec(t_cmd *comd, char **envorig)
{
	char **envexec;

	envexec = ft_tabdup(envorig);
	if (comd && comd->cmd[0] && !ft_strcmp(comd->cmd[0], "env"))
	{
		if (env_verif(comd->cmd, 1) != -1)
			envexec = env(comd->cmd, envorig, envexec);
	}
	return (envexec);
}

void	ft_dupfd(t_cmd *comd)
{
	if (comd->file_in)
		comd->fd_in = open(comd->file_in, O_RDONLY);
	if (comd->fd_in != 0)
		dup2(comd->fd_in, 0);
	else
		dup2(comd->save_in, 0);
	if (comd->fd_out != 1)
		dup2(comd->fd_out, 1);
	else
		dup2(comd->save_out, 1);
	if (comd->fd_err != 2)
		dup2(comd->fd_err, 2);
	else
		dup2(comd->save_err, 2);
	dup_aggreg(comd);
}
