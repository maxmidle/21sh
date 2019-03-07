#include "21sh.h"

t_cmd	*init_elem(char **command, t_cmd *previous, int ispipe)
{
	t_cmd	*elem;

	elem = NULL;
	if (!(elem = malloc(sizeof(t_cmd))))
		return (NULL);
	elem->cmd = init_cmd(command);
	elem->fd_in = init_heredoc(command);
	elem->fd_out = 1;
	elem->fd_err = 2;
	elem->save_in = init_saves(previous, 0);
	elem->save_out = init_saves(previous, 1);
	elem->save_err = init_saves(previous, 2);
	elem->is_pipe = ispipe;
	elem->file_in = init_fin(command);
	elem->file_out = init_fout(command);
	elem->aggreg = init_aggreg(command);
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
	while (command[i] && !ft_iscmdsep(command[i]) && !ft_isredi(command[i]))
		i++;
	if (!(cmd = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (command[size + i] && !ft_iscmdsep(command[size + i]) &&
		!ft_isredi(command[size + i]))
	{
		if (ft_isaggr(command[size + i]))
			i++;
		if (command[size + i] && !ft_iscmdsep(command[size + i]) &&
			!ft_isredi(command[size + i]))
		{
			cmd[size] = ft_strdup(command[size + i]);
			size++;
		}
	}
	cmd[size] = NULL;
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
		if (!ft_strcmp(command[i], "<"))
			return (ft_strdup(command[i + 1]));
	}
	return (NULL);
}

int	init_saves(t_cmd *previous, int mode)
{
	if (mode == 0 && !previous)
		return (dup(0));
	else if (mode == 0)
		return (previous->save_in);
	if (mode == 1 && !previous)
		return (dup(1));
	else if (mode == 1)
		return (previous->save_out);
	if (mode == 2 && !previous)
		return (dup(2));
	else if (mode == 2)
		return (previous->save_err);
	return(-1);
}
