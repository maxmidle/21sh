/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_readhd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:00:29 by radler            #+#    #+#             */
/*   Updated: 2019/04/05 13:18:24 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

char			*tc_readhd(char *eof)
{
	struct termios	termorig;
	t_line			*line;
	char	buff[7];
	char	*tmp;

	termorig = term_init();
	line = (t_line *)malloc(sizeof(t_line));
	line->str = ft_strnew(0);
	line->clipboard = ft_strnew(0);
	line->stop = 0;
	line->cpos = 0;
	line->hpos = -1;
	ft_bzero(buff, 7);
	read(0, &buff, 6);
	while (buff[0] != '\n' && !line->stop)
	{
		line = tc_handlehdchar(line, buff, eof);
		ft_bzero(buff, 7);
		if (!line->stop)
			read(0, &buff, 6);
	}
	tcsetattr(STDIN_FILENO, TCSADRAIN, &termorig);
	tmp = NULL;
	if (line->str)
		tmp = ft_strdup(line->str);
	free(line->str);
	free(line->clipboard);
	free(line);
	return (tmp);
}

t_line			*tc_handlehdchar(t_line *line, char buff[7], char *eof)
{
	if (buff[0] == '\x1b')
		line = tc_handlehdctrl(line, buff, eof);
	else if (buff[0] == 127)
		line = tc_delchar(line);
	else if (buff[0] != '\t')
		line->str = tc_putchar(line, buff);
	return (line);
}

t_line			*tc_handlehdctrl(t_line *line, char buff[7], char *eof)
{
	if (!ft_strcmp(buff, "\x1b[D") && line->cpos > 0)
		line->cpos = tc_left(line->cpos);
	else if (!ft_strcmp(buff, "\x1b[C")
			&& line->cpos < (int)ft_strlen(line->str))
		line->cpos = tc_right(line->cpos);
	else if (!ft_strcmp(buff, "\x1b[1;2D")
			&& line->cpos > 0)
		line->cpos = tc_leftword(line);
	else if (!ft_strcmp(buff, "\x1b[1;2C")
			&& line->cpos < (int)ft_strlen(line->str))
		line->cpos = tc_rightword(line);
	else if (!ft_strcmp(buff, "\x1b[H") && line->cpos > 0)
		line->cpos = tc_home(line);
	else if (!ft_strcmp(buff, "\x1b[F"))
		line->cpos = tc_end(line);
	else if (!ft_strcmp(buff, "\x1b[6~"))
		line->clipboard = tc_copy(line);
	else if (!ft_strcmp(buff, "\x1b[5~"))
		line->str = tc_paste(line);
	else if (!ft_strcmp(buff, "\x1b[1;2P") && !ft_strlen(line->str))
		line = tc_quithd(line, eof);
	return (line);
}
