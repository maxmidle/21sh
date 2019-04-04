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
	if (line->cpos > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dm", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar);
		line->cpos--;
		line->str = ft_strcdel(line->str, line->cpos);
	}
	return (line);
}
