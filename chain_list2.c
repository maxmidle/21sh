#include "21sh.h"

int	init_heredoc(char **command)
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

int	get_heredoc(char *endline)
{
	char	*str;
	int		fd[2];
	int		stop;
	char	buff[2];

	pipe(fd);
	buff[1] = '\0';
	stop = 1;
	while (stop)
	{
		str = ft_strnew(0);
		buff[0] = 'a';
		ft_printf("here_doc : \x1B[35m%s \x1B[33m}>\x1B[0m", endline);
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			ft_strconc(&str, buff);
		} 
		if (ft_strncmp(str, endline, (ft_strlen(str) - 1)))
			write(fd[1], str, ft_strlen(str));
		else
			stop = 0;
		free(str);
	}
	close (fd[1]);
	return (fd[0]);
}

char	*init_aggreg(char **command)
{
	int	infile;
	int	i;
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
				tmp[ft_strlen(tmp)] = '\0';
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

void	free_chain(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	while (list && list->prev)
		list = list->prev;
	while (list)
	{
//	printf("cmd : %s\nin : %d\nout : %d\nerr : %d\npipe : %d\n", list->cmd[0], list->fd_in, list->fd_out, list->fd_err, list->is_pipe);
		ft_strdel(&list->aggreg);
		if (list->cmd)	
			ft_freetab(list->cmd);
		if (list->fd_in != 0 && list->fd_in > 2)
			close(list->fd_in);
		if (list->fd_out != 1 && list->fd_in > 2)
			close(list->fd_out);
		if (list->file_in)
			ft_strdel(&list->file_in);
		if (list->file_out)
		{
			ft_freetab(list->file_out);
			list->file_out = NULL;
		}
		close(list->save_in);
		close(list->save_out);
		close(list->save_err);
		list->prev = NULL;
		list = list->next;
		comd->next = NULL;
		free(comd);
		comd = list;
	}
}	
