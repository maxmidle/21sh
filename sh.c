/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:06:10 by radler            #+#    #+#             */
/*   Updated: 2019/04/18 16:52:31 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(void)
{
	extern char	**environ;
	char		**envorig;
	char		**history;
	t_cmd		*comd;

	if (!sig_init())
		return (0);
	envorig = ft_tabdup(environ);
	history = NULL;
	while (envorig)
	{
		comd = handle_line(read_line(envorig, &history, ft_prompt(envorig)));
		if (comd && comd->cmd && comd->cmd[0]
			&& !ft_strcmp(comd->cmd[0], "exit"))
		{
			ft_freetab(envorig);
			envorig = NULL;
		}
		else if (comd && comd->cmd && comd->cmd[0])
			envorig = run_full_cmd(comd, envorig);
		free_chain(comd);
	}
	ft_freetab(history);
	exit(0);
	return (0);
}

int		ft_prompt(char **envorig)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envorig && envorig[i] && ft_strcmp(envorig[i], "PWD") != 61)
		i++;
	if (envorig && envorig[i] && (tmp = ft_strrchr(envorig[i], '/')))
	{
		tmp++;
		print_line_sep();
		ft_printf("-21sh: \x1B[34;1m%s/\x1B[0m\x1B[33m )>\x1B[0m", tmp);
		return (11 + strlen(tmp));
	}
	else
	{
		print_line_sep();
		ft_putstr("-21sh: \x1B[34;1mPWD/\x1B[0m\x1B[33m )>\x1B[0m");
		return (14);
	}
}

int		sig_init(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		write(2, "-21sh: redirection error: ", 26);
		write(2, "this shell must be run on :\n\t", 29);
		write(2, "- FD_IN = 0\n\t- FD_OUT = 1\n\t- FD_ERR = 2\n", 4);
		return (0);
	}
	signal(SIGINT, sighandler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	print_line_sep(void)
{
	char	*term;
	int		i;

	i = 20;
	term = getenv("TERM");
	if (term)
	{
		tgetent(NULL, term);
		i = tgetnum("co");
	}
	while (i > 0)
	{
		ft_putchar('_');
		i--;
	}
	ft_putchar('\n');
	ft_putstr("\x1b[0m");
}

void	sighandler(int sig)
{
	sig++;
}
