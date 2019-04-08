/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:43:43 by radler            #+#    #+#             */
/*   Updated: 2019/04/04 16:11:37 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H
# include "../libft/libft/libft.h"
# include <curses.h>
# include <term.h>
# include <termios.h>

typedef struct	s_line
{
	char	**hist;
	char	*str;
	char	*clipboard;
	int		cpos;
	int		stop;
	int		hpos;
	int		hsize;
	int		psize;
	int		ssize;
}				t_line;

char			*tc_readline(char **history, int promptsize);
t_line			*tc_handlechar(t_line *line, char buff[7]);
t_line			*tc_handlectrl(t_line *line, char buff[7]);
struct termios	term_init(void);

char			*tc_putchar(t_line *line, char buff[7]);
t_line			*tc_delchar(t_line *line);
void			tc_del_next_line(t_line *line, int cursorpo, int first);
int			tc_is_next_line(t_line *line, int cursorpos);

int				tc_left(t_line *line);
int				tc_right(t_line *line);
int				tc_leftword(t_line *line);
int				tc_rightword(t_line *line);

int				tc_end(t_line *line);
int				tc_home(t_line *line);

char			*tc_paste(t_line *line);
char			*tc_copy(t_line *line);

t_line			*tc_stop(t_line *line);
t_line			*tc_quit(t_line *line);

t_line			*tc_history(t_line *line, char buff[7]);
t_line			*tc_up(t_line *line);
t_line			*tc_down(t_line *line);
char			**hist_add(char ***history, char *str);

#endif
