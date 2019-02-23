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

int	run_bin(char **command, char **envexec)
{
	char	**bpath;
	int		y;
	pid_t	pid;
	
	y = 0;
	if (!(bpath = ft_strsplit(getenv("PATH"), ':')))
		return (0);
	while (bpath[y])
	{
		ft_strconc(&bpath[y], "/");
		ft_strconc(&bpath[y], command[0]);
		if (!access(bpath[y], X_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(bpath[y], command, envexec);
			wait(0);
			ft_freetab(bpath);
			return (1);
		}
		y++;
	}
	ft_freetab(bpath);
	return (0);
}
