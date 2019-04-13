/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_copypaste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:42 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 11:57:22 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

char	*tc_copy(t_line *line)
{
	free(line->clipboard);
	line->clipboard = ft_strdup(&line->str[line->cpos]);
	return (line->clipboard);
}

t_line	*tc_paste(t_line *line, int mode)
{
	char	buff[7];
	int		firstline;
	int		i;

	firstline = line->ssize - line->psize;
	buff[1] = '\0';
	i = 0;
	while (line->clipboard[i])
	{
		buff[0] = line->clipboard[i];
		buff[1] = '\0';
		tputs(tgetstr("im", NULL), 1, ft_putchar);
		write(1, buff, 1);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		if (mode)
			ft_strins(&line->str, buff, line->cpos);
		line->cpos++;
		tc_godown(line);
		i++;
	}
	if (!mode)
		line->cpos = tc_goback(line, i);
	return (line);
}

int		tc_goback(t_line *line, int i)
{
	while (i > 0)
	{
		line->cpos = tc_left(line);
		i--;
	}
	return (line->cpos);
}

void	tc_godown(t_line *line)
{
	int	firstline;

	firstline = line->ssize - line->psize;
	if (line->cpos % line->ssize == firstline)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
	}
}
