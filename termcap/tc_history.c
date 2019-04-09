/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:51:35 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 11:52:48 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

t_line	*tc_history(t_line *line, char buff[7])
{
	if (line->hist)
	{
		if (!ft_strcmp(buff, "\x1b[A") && line->hpos < line->hsize - 1)
			line = tc_up(line);
		else if (!ft_strcmp(buff, "\x1b[B") && line->hpos > -1)
			line = tc_down(line);
	}
	if (!ft_strcmp(buff, "\x1b[1;2A"))
		line = tc_upline(line);
	else if (!ft_strcmp(buff, "\x1b[1;2B"))
		line = tc_downline(line);
	return (line);
}

t_line	*tc_up(t_line *line)
{
	int		i;
	char	buff[7];

	i = 0;
	tc_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free(line->str);
	line->str = ft_strnew(0);
	line->hpos++;
	while (line->hist[line->hpos][i])
	{
		buff[0] = line->hist[line->hpos][i];
		line = tc_putchar(line, buff);
		i++;
	}
	return (line);
}

t_line	*tc_down(t_line *line)
{
	int		i;
	char	buff[7];

	i = 0;
	tc_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free(line->str);
	line->str = ft_strnew(0);
	line->hpos--;
	while (line->hpos > -1 && line->hist[line->hpos][i])
	{
		buff[0] = line->hist[line->hpos][i];
		line = tc_putchar(line, buff);
		i++;
	}
	return (line);
}

char	**hist_add(char ***history, char *str)
{
	char	**tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(*history) + 2));
	tmp[i] = ft_strdup(str);
	i++;
	while (history[0] && history[0][y])
	{
		tmp[i] = ft_strdup(history[0][y]);
		i++;
		y++;
	}
	tmp[i] = NULL;
	if (history[0])
		ft_freetab(*history);
	return (tmp);
}
