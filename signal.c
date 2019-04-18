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

char	**sig_init(char **envorig)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		write(2, "-21sh: redirection error: ", 26);
		write(2, "this shell \x1b[31mMUST\x1b[0m be run on :\n\t", 38);
		write(2, "- FD_IN = 0\n\t- FD_OUT = 1\n\t- FD_ERR = 2\n", 40);
		ft_freetab(envorig);
		return (NULL);
	}
	signal(SIGINT, sighandler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	envorig = shlvl_up(envorig);
	return (envorig);
}

char	**shlvl_up(char **envorig)
{
	char	*str;
	char	*tmp;
	int		shlevel;

	str = NULL;
	shlevel = 0;
	tmp = ft_strdup("SHLVL=");
	if ((str = getenv("SHLVL")))
	{
		shlevel = ft_atoi(str);
		shlevel++;
		str = ft_itoa(shlevel);
		ft_strconc(&tmp, str);
		envorig = ft_setenv(envorig, tmp);
		ft_strdel(&tmp);
		ft_strdel(&str);
	}
	return (envorig);
}

void	sighandler(int sig)
{
	sig++;
}
