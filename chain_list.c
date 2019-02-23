#include "21sh.h"

t_cmd	*init_elem(char **command, t_cmd *previous, int ispipe)
{
	t_cmd	*elem;

	elem = NULL;
	if (!(elem = malloc(sizeof(t_cmd))))
		return (NULL);
	elem->cmd = init_cmd(command);
	elem->fd_in = 0;
	elem->fd_out = 1;
	elem->fd_err = 2;
	if (!previous)
	{
		elem->save_in = dup(0);
		elem->save_out = dup(1);
		elem->save_err = dup(2);
	}
	else
	{
		elem->save_in = previous->save_in;
		elem->save_out = previous->save_out;
		elem->save_err = previous->save_err;
	}	
	elem->is_pipe = ispipe;
	elem->file_in = init_fin(command);
	elem->file_out = init_fout(command);
	elem->next = NULL;
	elem->prev = previous;
	return (elem);
}

char	**init_cmd(char **command)
{
	int	size;
	int	i;
	char	**cmd;

	size = 0;
	i = 0;
	cmd = NULL;
	while (command[size] && !ft_iscmdsep(command[size]) &&
		!ft_isredi(command[size]))
		size++;
	if (!(cmd = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		cmd[i] = ft_strdup(command[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**init_fout(char **command)
{
	int	i;
	char	**file_out;

	i = 0;
	while (command[i] && !ft_iscmdsep(command[i]) &&
		ft_isredi(command[i]) != 1)
		i++;
	if (command[i] && ft_isredi(command[i]) == 1)
	{
		while (command[i + 2] && ft_isredi(command[i + 2]) == 1)
			i = i + 2;
		file_out = malloc(sizeof(char *) * 3);
		file_out[0] = ft_strdup(command[i + 1]);
		file_out[1] = ft_strdup(command[i]);
		file_out[2] = NULL;
		return (file_out);
	}
	return (NULL);
}

char	*init_fin(char **command)
{
	int	i;

	i = 0;
	while (command[i] && !ft_iscmdsep(command[i]) &&
		ft_isredi(command[i]) != 2)
		i++;
	if (command[i] && ft_isredi(command[i]) == 2)
	{
		while (command[i + 2] && ft_isredi(command[i + 2]) == 2)
			i = i + 2;
//		if (!ft_strcmp(command[i], "<<"))
//			file_in = get_here_doc(command[i + 1])
		if (!ft_strcmp(command[i], "<"))
			return (ft_strdup(command[i + 1]));
	}
	return (NULL);
}

void	free_chain(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	while (list && list->prev)
		list = list->prev;
	while (list)
	{
//	printf("cmd : %s\nin : %d\nout : %d\nerr : %d\npipe : %d\n", list->cmd[0], list->fd_in, list->fd_out, list->fd_err, list->is_pipe);
		if (list->cmd)	
			ft_freetab(list->cmd);
		if (list->fd_in != 0 && list->fd_in > 2)
			close(list->fd_in);
		if (list->fd_out != 1 && list->fd_in > 2)
			close(list->fd_out);
		if (list->file_in)
			ft_strdel(&list->file_in);
		if (list->file_out)
		{
			ft_freetab(list->file_out);
			list->file_out = NULL;
		}
		close(list->save_in);
		close(list->save_out);
		close(list->save_err);
		list->prev = NULL;
		list = list->next;
		comd->next = NULL;
		free(comd);
		comd = list;
	}
}	
