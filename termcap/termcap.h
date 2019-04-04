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

#include "../libft/libft/libft.h"
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

typedef struct	s_line
{
	char	*str;
	char	*clipboard;
	int		cpos;
	int		stop;
}				t_line;

char			*tc_readline(void);
t_line			*tc_handlechar(t_line *line, char buff[7]);
t_line			*tc_handlectrl(t_line *line, char buff[7]);
struct termios	term_init(void);

char			*tc_putchar(t_line *line, char buff[7]);
t_line			*tc_delchar(t_line *line);

int				tc_left(int cpos);
int				tc_right(int cpos);
int				tc_leftword(t_line *line);
int				tc_rightword(t_line *line);

int				tc_end(t_line *line);
int				tc_home(t_line *line);

char			*tc_paste(t_line *line);
char			*tc_copy(t_line *line);

t_line			*tc_stop(t_line *line);
t_line			*tc_quit(t_line *line);
