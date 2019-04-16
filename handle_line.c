/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:15:27 by radler            #+#    #+#             */
/*   Updated: 2019/04/16 11:48:41 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_cmd	*handle_line(char **command)
{
	t_cmd	*comd;
	t_cmd	*list;
	int		ispipe;
	int		i;

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
	if (command[i])
	{
		list->next = init_elem(command, list, ispipe);
		list = list->next;
	}
	return (list);
}

char	get_last_char(char *str)
{
	int		i;
	char	lastchar;

	i = 0;
	lastchar = '\0';
	while (str[i])
	{
		if (!ft_issep(str[i]))
			lastchar = str[i];
		i++;
	}
	return (lastchar);
}

int		get_next_sep(char **command, int i)
{
	while (command[i] && !ft_iscmdsep(command[i]))
		i++;
	return (i);
}
