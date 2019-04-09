#include "21sh.h"

char	**run_full_cmd(t_cmd *comd, char **envorig)
{
	char **envexec;
	t_cmd *list;

	list = comd;
	while (list)
	{
		envexec = get_envexec(list, envorig);
		if (ft_isbuiltins(list->cmd[0]) != 2)
		{
			create_file(list, envorig);
			run_proc_cmd(list, envorig, envexec, 0);
		}
		else
		{
			create_file(list, envorig);
			ft_dupfd(list);
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
		ft_freetab(envorig);
		ft_freetab(envexec);
		exit(0);
}

void	run_proc_cmd(t_cmd *comd, char **envorig, char **envexec, pid_t prevpid)
{
	t_cmd	*list;
	int	fd[2];
	pid_t	pid;
	pid_t	ctrlpid;

	list = comd;
	if (list->next && list->next->is_pipe)
	{
		pipe(fd);
		list->next->fd_in = fd[0];
		list->fd_out = fd[1];
	}
	pid = fork();
	if (!pid)
		run_proc(list, envorig, envexec, prevpid);
	if ((list->next && list->next->is_pipe))
		close(list->fd_out);
	if (list->next && list->next->is_pipe)
		run_proc_cmd(list->next, envorig, envexec, pid);
	waitpid(pid ,0, 0);
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
