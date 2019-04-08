/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:51:52 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 14:16:42 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

char	*tc_putchar(t_line *line, char buff[7])
{
		buff[1] = '\0';
		tputs(tgetstr("im", NULL), 1, ft_putchar);
		write(1, buff, 1);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		ft_strins(&line->str, buff, line->cpos);
		line->cpos++;
		return (line->str);
}

t_line	*tc_delchar(t_line *line)
{
	size_t firstline;

	firstline = line->ssize - line->psize -1;
	if (line->cpos > 0)
	{
		tc_left(line);
		tputs(tgetstr("dm", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar);
		line->cpos--;
		line->str = ft_strcdel(line->str, line->cpos);
		if (tc_is_next_line(line, line->cpos))
			tc_del_next_line(line, line->cpos, 1);
	}
	return (line);
}

void	tc_del_next_line(t_line *line, int cursorpos, int first)
{
	int	firstline;

	firstline = line->ssize - line->psize -1;
	if (first)
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (cursorpos % line->ssize != firstline)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		cursorpos++;
	}
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	write(1, &line->str[cursorpos], 1);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	tputs(tgetstr("dm", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	tputs(tgetstr("ed", NULL), 1, ft_putchar);
	if (tc_is_next_line(line, cursorpos + 1))
		tc_del_next_line(line, cursorpos + 1, 0);
	else
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

int	tc_is_next_line(t_line *line, int cursorpos)
{
	int	firstline;
	int	textsize;

	firstline = line->ssize - line->psize;
	if (cursorpos < firstline)
	{
		if ((int)strlen(line->str) > firstline)
			return(1);
	}
	else
	{
		textsize = (int)ft_strlen(&line->str[cursorpos -1]);
		if (textsize > line->ssize - (cursorpos - firstline) % line->ssize)
			return (1);
	}
	return (0);
}
