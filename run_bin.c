/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:19:12 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:22:02 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	run_bin(char **command, char **envorig, char **envexec)
{
	char	**bpath;
	int		y;
	pid_t	pid;

	y = 0;
	if ((y = env_search(envorig, "PATH=")) == -1)
		return (0);
	bpath = ft_strsplit(&envorig[y][5], ':');
	y = 0;
	while (bpath[y])
	{
		ft_strconc(&bpath[y], "/");
		ft_strconc(&bpath[y], command[0]);
		if (!access(bpath[y], X_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(bpath[y], command, envexec);
			ft_freetab(bpath);
			return (1);
		}
		y++;
	}
	ft_freetab(bpath);
	return (0);
}
