/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:17:29 by radler            #+#    #+#             */
/*   Updated: 2019/04/05 15:04:31 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H
# include "../libft/libft/libft.h"
# include "../21sh.h"
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
}				t_line;

char			*tc_readline(char **history);
t_line			*tc_handlechar(t_line *line, char buff[7]);
t_line			*tc_handlectrl(t_line *line, char buff[7]);
struct termios	term_init(void);

char			*tc_readhd(char *eof);
t_line			*tc_handlehdchar(t_line *line, char buff[7], char *eof);
t_line			*tc_handlehdctrl(t_line *line, char buff[7], char *eof);

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
t_line			*tc_quithd(t_line *line, char *eof);
void			tc_killproc(pid_t pid, char **envorig);

t_line			*tc_history(t_line *line, char buff[7]);
t_line			*tc_up(t_line *line);
t_line			*tc_down(t_line *line);
char			**hist_add(char ***history, char *str);

#endif
