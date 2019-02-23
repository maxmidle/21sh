#include "21sh.h"

char	**run_full_cmd(t_cmd *comd, char **envorig)
{
	t_cmd *list;

	list = comd;
	while (list)
	{
		if (ft_isbuiltins(list->cmd[0]) != 2)
			run_proc(list, envorig);
		else
		{
			create_file(list, envorig);
			ft_dupfd(list);
			envorig = run_cmd(list, envorig);
		}
		while (list->next && list->next->is_pipe)
			list = list->next;
		list = list->next;
	}
	return (envorig);
}
void	run_proc(t_cmd *comd, char **envorig)
{
	t_cmd	*list;
	pid_t	pid_cmd;

	list = comd;
	pid_cmd = 1;
	pid_cmd = fork();
	if (!pid_cmd)
	{
		create_file(list, envorig);
		run_proc_cmd(list, envorig);
		exit (0);
	}
	wait(0);
}

void	run_proc_cmd(t_cmd *comd, char **envorig)
{
	t_cmd	*list;
	int	fd[2];

	list = comd;
	if (list->next && list->next->is_pipe)
	{
		pipe(fd);
		list->next->fd_in = fd[0];
		list->fd_out = fd[1];
	}	
	ft_dupfd(list);
	envorig = run_cmd(list, envorig);
	if ((list->next && list->next->is_pipe))
		close(list->fd_out);
	if (list->next && list->next->is_pipe)
		run_proc_cmd(list->next, envorig);
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
//	printf("|%d %d %d|", comd->fd_in, comd->fd_out, comd->fd_err);
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
}
