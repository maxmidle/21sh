/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:16:34 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:56:39 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		init_heredoc(char **command)
{
	int	i;

	i = 0;
	while (command[i] && !ft_iscmdsep(command[i]) &&
		ft_isredi(command[i]) != 2)
		i++;
	if (command[i] && ft_isredi(command[i]) == 2)
	{
		while (command[i + 2] && ft_isredi(command[i + 2]) == 2)
			i = i + 2;
		if (!ft_strcmp(command[i], "<<"))
			return (get_heredoc(command[i + 1]));
	}
	return (0);
}

int		get_heredoc(char *endline)
{
	char	*str;
	int		fd[2];
	int		stop;

	pipe(fd);
	stop = 1;
	while (stop)
	{
		ft_printf("here_doc : \x1B[35m%s \x1B[33m}>\x1B[0m", endline);
		str = tc_readhd(endline, 14 + ft_strlen(endline));
		if (ft_strcmp(str, endline))
		{
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
		}
		else
			stop = 0;
		free(str);
	}
	close(fd[1]);
	return (fd[0]);
}

char	*init_aggreg(char **command)
{
	int		infile;
	int		i;
	char	*tmp;

	infile = 0;
	i = 0;
	while (command[i] && !ft_iscmdsep(command[i]))
	{
		if (ft_isredi(command[i]) == 1)
			infile = 1;
		if (ft_isaggr(command[i]))
		{
			if (infile == 0 ||
				command[i][ft_strlen(command[i]) - 1] != '1')
				return (ft_strdup(command[i]));
			else
			{
				tmp = ft_strdup(command[i]);
				tmp[ft_strlen(tmp) - 1] = 'f';
				return (tmp);
			}
		}
		i++;
	}
	return (NULL);
}

void	dup_aggreg(t_cmd *comd)
{
	int	dest;

	dest = 0;
	if (comd->aggreg)
	{
		while (ft_isdigit(comd->aggreg[dest]))
			dest++;
		dest += 2;
		if (comd->aggreg[dest] == 'f')
			dup2(comd->fd_out, ft_atoi(comd->aggreg));
		else if (comd->aggreg[dest] == '-')
			close(ft_atoi(comd->aggreg));
		else if (ft_atoi(&comd->aggreg[dest]) == 0)
			dup2(comd->fd_in, ft_atoi(comd->aggreg));
		else if (ft_atoi(&comd->aggreg[dest]) == 1)
		{
			if (comd->next && comd->next->is_pipe)
				dup2(comd->fd_out, ft_atoi(comd->aggreg));
			else
				dup2(comd->save_out, ft_atoi(comd->aggreg));
		}
		else if (ft_atoi(&comd->aggreg[dest]) == 2)
			dup2(comd->fd_err, ft_atoi(comd->aggreg));
	}
}
