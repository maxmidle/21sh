/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:23:13 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:23:59 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	**read_line(char **environ)
{
	char	**command;
	char	*tmp;
	char	buff[2];
	int		i;

	i = 0;
	buff[1] = '\0';
	tmp = ft_strnew(0);
	read(0, &buff, 1);
	while (buff[0] != '\n')
	{
		ft_strconc(&tmp, buff);
		read(0, &buff, 1);
	}
	if (count_words(tmp) == 0)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	if (ft_strstr(tmp, " ~"))
		tmp = tilde(tmp, environ);
	command = split_line(tmp);
	command = dollar(command, environ);
	ft_strdel(&tmp);
	return (command);
}

char	**split_line(char *str)
{
	char	**command;
	int		wordct;
	int		i;
	int		start;
	int		end;

	i = 0;
	end = 0;
	wordct = count_words(str);
	command = (char **)malloc(sizeof(char *) * (wordct + 1));
	while (i < wordct)
	{
		while (str[end] && ft_issep(str[end]))
			end++;
		start = end;
		while (str[end] && !ft_issep(str[end]) &&
			!ft_ischarsep(str[end]))
			end++;
		command[i] = ft_strsub(str, start, end - start);
		if (str[end] && !command[i])
			end += fill_sep_line(&str[end], &command[i]);
		i++;
	}
	command[i] = NULL;
	return (command);
}

int		fill_sep_line(char *str, char **command)
{
	if (!ft_strncmp(str, ">>", 2))
		*command = ft_strdup(">>");
	else if (!ft_strncmp(str, ">", 1))
		*command = ft_strdup(">");
	else if (!ft_strncmp(str, "<<", 2))
		*command = ft_strdup("<<");
	else if (!ft_strncmp(str, "<", 1))
		*command = ft_strdup("<");
	else if (!ft_strncmp(str, "|", 1))
		*command = ft_strdup("|");
	else if (!ft_strncmp(str, ";", 1))
		*command = ft_strdup(";");
	return (ft_strlen(*command));
}

int		count_words(char *str)
{
	int i;
	int wordct;

	i = 0;
	wordct = 0;
	while (str[i])
	{
		while (str[i] && ft_issep(str[i]))
			i++;
		if (str[i] && ft_ischarsep(str[i]))
		{
			while (str[i] && ft_ischarsep(str[i]))
				i++;
			wordct++;
		}
		if (str[i] && !ft_issep(str[i]))
		{	
			while (str[i] && !ft_issep(str[i]) &&
				!ft_ischarsep(str[i]))
				i++;
			wordct++;
		}
	}
	return (wordct);
}
