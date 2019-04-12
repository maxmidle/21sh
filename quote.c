/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:50:51 by radler            #+#    #+#             */
/*   Updated: 2019/04/12 07:21:08 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_quote(char *str, int start)
{
	int		i;
	int		size;
	char	*tmp;
	char	*cmd;

	start++;
	i = get_next_quote(str, start, 0);
	size = i - start + 1;
	size--;
	if (size > 0)
		cmd = ft_strsub(str, start, size);
	else
		cmd = ft_strnew(0);
	if (!str[i])
	{
		tmp = prompt_quote(str, start);
		ft_strconc(&cmd, tmp);
		free(tmp);
	}
	return (cmd);
}

char	*prompt_quote(char *str, int start)
{
	char *tmp;
	char *cmd;
	char tquote;
	char *end;

	tmp = ft_strnew(0);
	cmd = ft_strnew(0);
	tquote = str[start - 1];
	while (!ft_strchr(tmp, tquote))
	{
		free(tmp);
		if (tquote == '\'')
			ft_putstr("squote : \x1B[32m\'\x1B[33m ]>\x1B[0m");
		if (tquote == '\"')
			ft_putstr("dquote : \x1B[32m\"\x1B[33m ]>\x1B[0m");
		tmp = tc_readline(NULL, 13);
		ft_strconc(&cmd, "\n");
		ft_strconc(&cmd, tmp);
	}
	free(tmp);
	end = ft_strchr(cmd, tquote);
	*end = '\0';
	return (cmd);
}

int		get_next_quote(char *str, int start, int mode)
{
	int		i;

	i = start;
	while (str[i] && !ft_isquote(str[i]))
		i++;
	if (!str[i] && mode)
		i--;
	return (i);
}

int		bad_quoting(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (i > 0 && !ft_issep(str[i - 1]))
			{
				write(2, "-21sh: syntax error :\n\t", 23);
				write(2, "space requiered next to ", 24);
				if (str[i] == '\'')
					write(2, "\'", 1);
				else
					write(2, "\"", 1);
				write(2, "\n", 1);
				return (1);
			}
			return (0);
		}
		i++;
	}
	return (0);
}
