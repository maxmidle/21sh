/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:17:51 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:55:40 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**dollar(char **command, char **environ)
{
	int		i;
	char	*tmp;

	i = 0;
	while (command[i])
	{
		if (ft_strchr(command[i], '$'))
		{
			tmp = dollar_verif(command[i], environ);
			if (tmp)
				command[i] = dollar_fill(command[i], tmp);
		}
		i++;
	}
	return (command);
}

char	*dollar_verif(char *command, char **environ)
{
	char	*var;
	int		i;
	int		y;

	i = 0;
	var = NULL;
	while (command[i] && command[i] != '$')
		i++;
	i++;
	if (!command[i] || command[i] == '$')
		return(NULL);
	y = i;
	while (command[y] && ft_isalpha(command[y]))
		y++;
	var = ft_strsub(command, i, y - i);
	i = 0;
	while (environ[i] && ft_strcmp(environ[i], var) != 61)
		i++;
	ft_strdel(&var);
	return (environ[i]);
}

char	*dollar_fill(char *command, char *environ)
{
	int		i;
	char	*tmp;
	char	*cpy;

	i = 0;
	cpy = ft_strchr(environ, '=') + 1;
	tmp = ft_strcdup(command, '$');
	ft_strconc(&tmp, cpy);
	while (command[i] != '$')
		i++;
	i++;
	while (command[i] && ft_isalpha(command[i]))
		i++;
	if (command[i])
		ft_strconc(&tmp, &command[i]);
	ft_strdel(&command);
	return (tmp);
}
