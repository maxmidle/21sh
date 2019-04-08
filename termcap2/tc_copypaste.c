/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_endhome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:53:42 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 14:52:37 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

char	*tc_copy(t_line *line)
{
	free(line->clipboard);
	line->clipboard = ft_strdup(&line->str[line->cpos]);
	return (line->clipboard);
}

char	*tc_paste(t_line *line)
{
	int i;
	char buff[7];

	buff[1] = '\0';
	i = 0;
	while (line->clipboard[i])
	{
			buff[0] = line->clipboard[i];
			line->str = tc_putchar(line, buff);
			i++;
	}
	return (line->str);
}
