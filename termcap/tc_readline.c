/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:43:43 by radler            #+#    #+#             */
/*   Updated: 2019/04/11 17:20:41 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"

char			*tc_readline(char **history, int promptsize)
{
	struct termios	termorig;
	char			buff[7];
	char			*tmp;
	t_line			*line;

	line = NULL;
	termorig = term_init();
	line = line_init(line, history, promptsize);
	ft_bzero(buff, 7);
	read(0, &buff, 6);
	while (buff[0] != '\n' && !line->stop)
	{
		line = tc_handlechar(line, buff);
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

t_line			*tc_handlechar(t_line *line, char buff[7])
{
	int tabsize;

	tabsize = 4;
	if (buff[0] == '\x1b' || buff[0] == 4 || buff[0] == 3)
		line = tc_handlectrl(line, buff);
	else if (buff[0] == 127)
		line = tc_delchar(line);
	else if (buff[0] == '\t')
	{
		buff[0] = ' ';
		while (tabsize > 0)
		{
			line = tc_putchar(line, buff);
			tabsize--;
		}
	}
	else
		line = tc_putchar(line, buff);
	return (line);
}

t_line			*tc_handlectrl(t_line *line, char buff[7])
{
	if (!ft_strcmp(buff, "\x1b[D") && line->cpos > 0)
		line->cpos = tc_left(line);
	else if (!ft_strcmp(buff, "\x1b[C")
			&& line->cpos < (int)ft_strlen(line->str))
		line->cpos = tc_right(line);
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
		line = tc_paste(line, 1);
	else if (buff[0] == 3)
		line = tc_stop(line);
	else if (buff[0] == 4 && !ft_strlen(line->str))
		line = tc_quit(line);
	line = tc_history(line, buff);
	return (line);
}

struct termios	term_init(void)
{
	struct termios	term;
	struct termios	termorig;

	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &termorig);
	term.c_lflag = ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	tgetent(NULL, getenv("TERM"));
	return (termorig);
}

t_line			*line_init(t_line *line, char **history, int promptsize)
{
	line = (t_line *)malloc(sizeof(t_line));
	line->hist = history;
	line->str = ft_strnew(0);
	line->clipboard = ft_strnew(0);
	line->stop = 0;
	line->cpos = 0;
	line->hpos = -1;
	line->hsize = ft_tablen(history);
	line->psize = promptsize;
	line->ssize = tgetnum("co");
	return (line);
}
