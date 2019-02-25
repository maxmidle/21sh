/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:14:34 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:15:52 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		main(void)
{
	extern char	**environ;
	char		**envorig;
	t_cmd		*comd;

	envorig = ft_tabdup(environ);
	while (envorig)
	{
		comd = NULL;
		ft_prompt(envorig);
		comd = handle_line(read_line(envorig));
		if (comd && !ft_strcmp(comd->cmd[0], "exit"))
		{
			ft_freetab(envorig);
			envorig = NULL;
		}
		else if (comd)
			envorig = run_full_cmd(comd, envorig);
		free_chain(comd);
	}
	exit(0);
	return (0);
}

void	ft_prompt(char **envorig)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envorig[i] && ft_strcmp(envorig[i], "PWD") != 61)
		i++;
	if (envorig[i] && (tmp = ft_strrchr(envorig[i], '/') + 1))
		ft_printf("-21sh: \x1B[34m%s/\x1B[33m )>\x1B[0m", tmp);
	else
		ft_printf("-21sh: \x1B[34mPWD/\x1B[33m )>\x1B[0m");
}
