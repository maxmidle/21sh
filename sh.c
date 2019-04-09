/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:14:34 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 15:20:47 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(void)
{
	extern char	**environ;
	char		**envorig;
	char		**history;
	t_cmd		*comd;

	envorig = ft_tabdup(environ);
	history = NULL;
	while (envorig)
	{
		comd = NULL;
		comd = handle_line(read_line(envorig, &history, ft_prompt(envorig)));
		if (comd && comd->cmd && comd->cmd[0] &&
			!ft_strcmp(comd->cmd[0], "exit"))
		{
			ft_freetab(envorig);
			envorig = NULL;
		}
		else if (comd && comd->cmd && comd->cmd[0])
			envorig = run_full_cmd(comd, envorig);
		free_chain(comd);
	}
	ft_freetab(history);
	return (0);
}

int		ft_prompt(char **envorig)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envorig[i] && ft_strcmp(envorig[i], "PWD") != 61)
		i++;
	if (envorig[i] && (tmp = ft_strrchr(envorig[i], '/') + 1))
	{
		ft_printf("|------------|\n-21sh: \x1B[34m%s/\x1B[33m )>\x1B[0m", tmp);
		return (11 + ft_strlen(tmp));
	}
	else
	{
		ft_printf("|------------|\n-21sh: \x1B[34mPWD/\x1B[33m )>\x1B[0m\n");
		return (14);
	}
}