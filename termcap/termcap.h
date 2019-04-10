/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:17:29 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 17:36:16 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H
# include "../libft/libft/libft.h"
# include "../sh.h"
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
	int		ssize;
	int		psize;
}				t_line;

char			*tc_readline(char **history, int promptsize);
t_line			*tc_handlechar(t_line *line, char buff[7]);
t_line			*tc_handlectrl(t_line *line, char buff[7]);
struct termios	term_init(void);
t_line			*line_init(t_line *line, char **history, int promptsize);

char			*tc_readhd(char *eof, int promptsize);
t_line			*tc_handlehdchar(t_line *line, char buff[7], char *eof);
t_line			*tc_handlehdctrl(t_line *line, char buff[7], char *eof);

t_line			*tc_putchar(t_line *line, char buff[7]);
t_line			*tc_delchar(t_line *line);
t_line			*tc_upline(t_line *line);
t_line			*tc_downline(t_line *line);

int				tc_left(t_line *line);
int				tc_right(t_line *line);
int				tc_leftword(t_line *line);
int				tc_rightword(t_line *line);

int				tc_end(t_line *line);
int				tc_home(t_line *line);

t_line			*tc_paste(t_line *line, int mode);
char			*tc_copy(t_line *line);
int				tc_goback(t_line *line, int i);
void			tc_godown(t_line *line);

t_line			*tc_stop(t_line *line);
t_line			*tc_quit(t_line *line);
t_line			*tc_quithd(t_line *line, char *eof);
void			tc_killproc(pid_t pid, char **envorig);

t_line			*tc_history(t_line *line, char buff[7]);
t_line			*tc_up(t_line *line);
t_line			*tc_down(t_line *line);
char			**hist_add(char ***history, char *str);

#endif
