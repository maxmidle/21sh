/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:15:26 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 14:02:39 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

int		tc_left(int cpos)
{
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	return (cpos - 1);
}

int		tc_right(int cpos)
{
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	return (cpos + 1);
}

int		tc_rightword(t_line *line)
{
	while (line->str[line->cpos] && !ft_issep(line->str[line->cpos]))
			line->cpos = tc_right(line->cpos);
	while (line->str[line->cpos] && ft_issep(line->str[line->cpos]))
			line->cpos = tc_right(line->cpos);
	return (line->cpos);
}

int		tc_leftword(t_line *line)
{
	while (line->cpos > 0 && !ft_issep(line->str[line->cpos]))
			line->cpos = tc_left(line->cpos);
	while (line->cpos > 0 && ft_issep(line->str[line->cpos]))
			line->cpos = tc_left(line->cpos);
	return (line->cpos);
}
