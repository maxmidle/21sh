/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_stop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:44:59 by radler            #+#    #+#             */
/*   Updated: 2019/04/05 15:32:39 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

t_line		*tc_stop(t_line *line)
{
	char buff[7];

	buff[0] = '\n';
	line->cpos = tc_end(line);
	ft_strclr(line->str);
	line->stop = 1;
	line->str = tc_putchar(line, buff);
	return (line);
}

t_line		*tc_quit(t_line *line)
{
	char buff[7];

	buff[0] = '\n';
	line->str = tc_putchar(line, buff);
	free(line->str);
	line->str = ft_strdup("exit");
	line->stop = 1;
	return (line);
}

t_line		*tc_quithd(t_line *line, char *eof)
{
	char buff[7];

	buff[0] = '\n';
	line->str = tc_putchar(line, buff);
	free(line->str);
	line->str = ft_strdup(eof);
	line->stop = 1;
	return (line);
}
