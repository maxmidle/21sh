/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_endhome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:42 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 14:03:43 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

int		tc_end(t_line *line)
{
	while (line->str[line->cpos])
			line->cpos = tc_right(line->cpos);
	return (line->cpos);
}

int		tc_home(t_line *line)
{
	while (line->cpos > 0)
			line->cpos = tc_left(line->cpos);
	return (line->cpos);
}
