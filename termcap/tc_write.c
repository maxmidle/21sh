/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:51:52 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 11:55:57 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

t_line	*tc_putchar(t_line *line, char buff[7])
{
	char *tmp;

	tmp = NULL;
	if (line->cpos < (int)ft_strlen(line->str))
	{
		tmp = ft_strdup(line->clipboard);
		line->clipboard = tc_copy(line);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	buff[1] = '\0';
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	write(1, buff, 1);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_strins(&line->str, buff, line->cpos);
	line->cpos++;
	tc_godown(line);
	if (line->cpos < (int)ft_strlen(line->str))
	{
		line = tc_paste(line, 0);
		free(line->clipboard);
		line->clipboard = ft_strdup(tmp);
		free(tmp);
	}
	return (line);
}

t_line	*tc_delchar(t_line *line)
{
	char *tmp;

	tmp = NULL;
	if (line->cpos > 0)
	{
		if (line->cpos < (int)ft_strlen(line->str))
		{
			tmp = ft_strdup(line->clipboard);
			line->clipboard = tc_copy(line);
			tputs(tgetstr("cd", NULL), 1, ft_putchar);
		}
		line->cpos = tc_left(line);
		tputs(tgetstr("dm", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar);
		line->str = ft_strcdel(line->str, line->cpos);
		if (line->cpos < (int)ft_strlen(line->str))
		{
			line = tc_paste(line, 0);
			free(line->clipboard);
			line->clipboard = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (line);
}

t_line	*tc_upline(t_line *line)
{
	int	firstline;
	int	i;

	i = 0;
	firstline = line->ssize - line->psize;
	if (line->cpos >= firstline)
	{
		while (i < line->ssize && line->cpos > 0)
		{
			line->cpos = tc_left(line);
			i++;
		}
	}
	return (line);
}

t_line	*tc_downline(t_line *line)
{
	int	firstline;
	int	i;

	i = 0;
	firstline = line->ssize - line->psize;
	while (i < line->ssize && line->cpos < (int)ft_strlen(line->str))
	{
		line->cpos = tc_right(line);
		i++;
	}
	return (line);
}
