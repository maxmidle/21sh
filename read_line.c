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
	char	**cmd;
	int		i;
	int		start;
	int		end;

	i = 0;
	end = 0;
	cmd = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	while (str[end] && ft_issep(str[end]))
		end++;
	while (str[end])
	{
		start = end;
		if (str[end] && !ft_isaggr(&str[end]))
		{
			while (str[end] && !ft_issep(str[end]) &&
				!ft_ischarsep(str[end]))
				end++;
		}
		end += fill_sep_line(str, &cmd[i++], start, end);
	//	i++;
		while (str[end] && ft_issep(str[end]))
			end++;
	}
		cmd[i] = NULL;
	return (cmd);
}

int		fill_sep_line(char *str, char **command, int start, int end)
{
	if (str[end] && ft_isaggr(&str[end]))
		*command = fill_aggr(&str[end]);
	else if ((*command = ft_strsub(str, start, end - start)))
		return(0);
	else if (str[end] && !ft_strncmp(&str[end], ">>", 2))
		*command = ft_strdup(">>");
	else if (str[end] && !ft_strncmp(&str[end], ">", 1))
		*command = ft_strdup(">");
	else if (str[end] && !ft_strncmp(&str[end], "<<", 2))
		*command = ft_strdup("<<");
	else if (str[end] && !ft_strncmp(&str[end], "<", 1))
		*command = ft_strdup("<");
	else if (str[end] && !ft_strncmp(&str[end], "|", 1))
		*command = ft_strdup("|");
	else if (str[end] && !ft_strncmp(&str[end], ";", 1))
		*command = ft_strdup(";");
	return (ft_strlen(*command));
}

char	*fill_aggr(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	i += 2;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == '-'))
		i++;
	return (ft_strndup(str, i));	
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
