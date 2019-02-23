#include "21sh.h"

t_cmd	*handle_line(char **command)
{
	t_cmd	*comd;
	t_cmd	*list;
	int	ispipe;
	int	i;

	comd = NULL;
	i = 0;
	if (!command || !command[i] || !(comd = init_elem(command, NULL, 0)))
		return (NULL);
	list = comd;
	while (command[i])
	{
		ispipe = 0;
		i = get_next_sep(command, i);
		if (command[i] && ft_iscmdsep(command[i]))
		{
			if (!ft_strcmp(command[i], "|"))
				ispipe = 1;
			i++;
		}
		list = make_list(&command[i], list, ispipe);
	}
	ft_freetab(command);
	return (comd);
}

t_cmd	*make_list(char **command, t_cmd *list, int ispipe)
{
	int	i;

	i = 0;
	if(command[i])
	{
		list->next = init_elem(command, list, ispipe);
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
