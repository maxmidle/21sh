/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:15:26 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 11:51:19 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

int		tc_left(t_line *line)
{
	int i;
	int	firstline;

	i = 0;
	firstline = line->ssize - line->psize;
	if (line->cpos % line->ssize == firstline)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		while (i < line->ssize - 1)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
			i++;
		}
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	return (line->cpos - 1);
}

int		tc_right(t_line *line)
{
	int	firstline;

	firstline = line->ssize - line->psize;
	if (line->cpos % line->ssize == firstline - 1)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	return (line->cpos + 1);
}

int		tc_rightword(t_line *line)
{
	while (line->str[line->cpos] && !ft_issep(line->str[line->cpos]))
		line->cpos = tc_right(line);
	while (line->str[line->cpos] && ft_issep(line->str[line->cpos]))
		line->cpos = tc_right(line);
	return (line->cpos);
}

int		tc_leftword(t_line *line)
{
	while (line->cpos > 0 && !ft_issep(line->str[line->cpos]))
		line->cpos = tc_left(line);
	while (line->cpos > 0 && ft_issep(line->str[line->cpos]))
		line->cpos = tc_left(line);
	return (line->cpos);
}
