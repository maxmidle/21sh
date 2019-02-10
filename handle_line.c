#include "21sh.h"

t_cmd	*handle_line(char **command)
{
	t_cmd	*comd;
	t_cmd	*list;
	int	fd[2];
	int	i;

	comd = NULL;
	i = 0;
	if (!command || !command[i] || !(comd = init_elem(command, NULL, NULL)))
		return (NULL);
	list = comd;
	while (command[i])
	{
		i = get_next_sep(command, i);
		if (command[i] && ft_iscmdsep(command[i]))
		{
			if (!ft_strcmp(command[i], "|"))
				pipe(fd);
			else
				fd[0] = -1;
			i++;
		}
		list = add_elem(&command[i], list, fd);
	}
	ft_freetab(command);
	return (comd);
}

t_cmd	*add_elem(char **command, t_cmd *list, int *fd)
{
	int	i;

	i = 0;
	if(command[i])
	{
		list->next = init_elem(command, list, fd);
		list = list->next;
	}
	return (list);	
}

int	get_next_sep(char **command, int i)
{
	while (command[i] && !ft_iscmdsep(command[i]) && !ft_isredi(command[i]))
		i++;
	if (command[i] && ft_isredi(command[i]))
	{
		while (command[i + 2] && ft_isredi(command[i + 2]))
			i = i + 2;
		i = i + 2;
	}
	return (i);
}
