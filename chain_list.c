#include "21sh.h"

t_cmd	*init_elem(char **command, t_cmd *previous, int *fd)
{
	int	i;
	t_cmd	*elem;

	elem = NULL;
	i = 0;
	if (!(elem = malloc(sizeof(t_cmd))))
		return (NULL);
	elem->cmd = init_cmd(command);
	elem->fd_in = 0;
	elem->fd_out = 1;
	elem->fd_err = 2;
	elem->fd_dos = init_fddos(command);
	if (fd && fd[0] != -1 && previous)
	{
		previous->fd_out = fd[1];
		elem->fd_in = fd[0];
	}
	if (elem->fd_dos != -1 && elem->fd_out == 1)
		elem->fd_out = elem->fd_dos;
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

int	init_fddos(char **command)
{
	int	i;
	int	fd_dos;

	i = 0;
	fd_dos = -1;
	while (command[i] && !ft_iscmdsep(command[i]) && !ft_isredi(command[i]))
		i++;
	if (command[i] && ft_isredi(command[i]))
	{
		while (command[i + 2] && ft_isredi(command[i + 2]))
			i = i + 2;
		fd_dos = open(command[i + 1], O_WRONLY);
	}
	return (fd_dos);
}

void	free_chain(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	while (list)
	{
	printf("cmd : %s\nin : %d\nout : %d\nerr : %d\ndos : %d\n", list->cmd[0], list->fd_in, list->fd_out, list->fd_err, list->fd_dos);
		if (list->cmd)	
			ft_freetab(list->cmd);
		if (list->fd_in != 0)
			close(list->fd_in);
		if (list->fd_out != 1)
			close(list->fd_out);
		if (list->fd_err != 2)
			close(list->fd_err);
		if (list->fd_dos != -1)
			close(list->fd_dos);
		list->prev = NULL;
		list = list->next;
		comd->next = NULL;
		free(comd);
		comd = list;
	}
}	
