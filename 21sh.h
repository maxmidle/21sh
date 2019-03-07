/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:24:53 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:24:55 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/ft_printf.h"
# include "21sh_struct.h"

int		run_bin(char **command, char **envexec);

char	**read_line(char **environ);
char	**split_line(char *str);
int		fill_sep_line(char *str, char **command, int start, int end);
char	*fill_aggr(char *str);
int		count_words(char *str);

char	*tilde(char *command, char **environ);

char	**env(char **command, char **envorig, char **envexec);
char	**env_option(char **envexec, char **command, int *u);
char	**ft_setenv(char **environ, char *var);
char	**ft_unsetenv(char **environ, char *var);
char	**ft_unsetenv_all(char **environ);

int		env_verif(char **command, int mode);
int		env_param_error(char **cmd, int i);
int		env_error_print(char **cmd, int i, int mode);
int		env_search(char **environ, char *var);

void	ft_cd(char **command, char **envorig);
void	cd_error(int mode, char *command);
void	change_pwd(char **envorig, char *oldpwd);
char	*getpath(char *command, char *oldpwd, char **envorig);

void	ft_echo(char **command);
void	ft_prompt(char **envorig);

char	**dollar(char **command, char **environ);
char	*dollar_verif(char *command, char **environ);
char	*dollar_fill(char *command, char *environ);

char	**run_cmd(t_cmd *comd, char **envorig);
char	**run_builtins(char **command, char **envorig);
char	**exit_runcmd(char **envorig, char **envexec, int mode);
int		ft_isbuiltins(char *command);

t_cmd	*handle_line(char **command);
t_cmd	*make_list(char **command, t_cmd *list, int ispipe);
int	get_next_sep(char **command, int i);

int	handle_file(t_cmd *comd, char **envorig);
void	create_file(t_cmd *comd, char **envorig);

int	ft_iscmdsep(char *cmd);
int	ft_isredi(char *cmd);
int	ft_ischarsep(char cmd);
int	ft_isaggr(char *cmd);

t_cmd	*init_elem(char **command, t_cmd *prev, int ispipe);
char	**init_cmd(char **command);
char	**init_fout(char **command);
char	*init_fin(char **command);
int	init_saves(t_cmd *previous, int mode);

int	init_heredoc(char **command);
char	*init_aggreg(char **command);
void	dup_aggreg(t_cmd *comd);
int	get_heredoc(char *endline);
void	free_chain(t_cmd *comd);

char	**run_full_cmd(t_cmd *comd, char **envorig);
void	run_proc(t_cmd *comd, char **envorig);
void	run_proc_cmd(t_cmd *comd, char **envorig);
void	ft_dupfd(t_cmd *comd);
char	**get_envexec(t_cmd *comd, char **envorig);
#endif
