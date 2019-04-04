/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_stop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:44:59 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 16:09:37 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

t_line		*tc_stop(t_line *line)
{
	line->cpos = tc_end(line);
	ft_strclr(line->str);
	line->stop = 1;
	return (line);
}

t_line		*tc_quit(t_line *line)
{
	free(line->str);
	line->str = ft_strdup("exit");
	line->stop = 1;
	return (line);
}
