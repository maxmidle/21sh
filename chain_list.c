#include "21sh.h"


t_cmd	*init_elem(char **command, t_cmd *prev, int *fd)
{
	int	i;
	t_cmd	*elem;

	elem = NULL;
	i = 0;
	if (!(elem = malloc(sizeof(t_cmd))))
		return (NULL);
	elem->cmd = init_cmd(command);
	elem->fd_out = init_fdout(command);
	elem->fd_err = 2;
	if (fd && fd[0] != -1 && prev)
	{
		prev->fd_out = fd[1];
		elem->pipe = fd[0];
	}
	else
		elem->pipe = -1;
	elem->next = NULL;
	elem->prev = prev;
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

int	init_fdout(char **command)
{
	int	i;
	int	fd_out;

	i = 0;
	fd_out = 1;
	while (command[i] && !ft_iscmdsep(command[i]) && !ft_isredi(command[i]))
		i++;
	if (command[i] && ft_isredi(command[i]))
	{
		while (command[i + 2] && ft_isredi(command[i + 2]))
			i = i + 2;
		fd_out = open(command[i + 1], O_WRONLY);
	}
	return (fd_out);
}
