/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:18:53 by radler            #+#    #+#             */
/*   Updated: 2019/04/18 16:51:29 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_cd(t_cmd *comd, char **envorig)
{
	struct stat	sb;
	char		*path;
	char		oldpwd[2048];

	getcwd(oldpwd, 2048);
	if (comd->cmd[1])
		path = getpath(comd->cmd[1], oldpwd, envorig);
	else
		path = tilde(ft_strdup("~"), envorig);
	if (!stat(path, &sb))
	{
		if (S_ISDIR(sb.st_mode) || S_ISLNK(sb.st_mode))
		{
			if (!chdir(path))
				change_pwd(envorig, oldpwd);
			else if (comd->cmd[1])
				cd_error(1, comd);
		}
		else if (comd->cmd[1])
			cd_error(2, comd);
	}
	else if (comd->cmd[1])
		cd_error(3, comd);
	ft_strdel(&path);
}

char	*getpath(char *command, char *oldpwd, char **envorig)
{
	int		i;
	char	*path;

	i = 0;
	while (envorig[i] && ft_strcmp(envorig[i], "OLDPWD") != 61)
		i++;
	if (!ft_strcmp(command, "-"))
	{
		if (envorig[i])
			return (ft_strdup(&envorig[i][7]));
		else
			return (ft_strdup("-"));
	}
	if (command && command[0] == '/')
		return (ft_strdup(command));
	path = ft_strdup(oldpwd);
	if (path[ft_strlen(path) - 1] != '/' && command[0] != '/')
		ft_strconc(&path, "/");
	if (command)
		ft_strconc(&path, command);
	return (path);
}

void	cd_error(int mode, t_cmd *comd)
{
	int error;

	error = errno;
	write(2, "-21sh: cd: ", 11);
	write(2, comd->cmd[1], ft_strlen(comd->cmd[1]));
	if (error == ELOOP)
		write(2, ": Too many levels of symbolic links\n", 36);
	else if (mode == 1)
		write(2, ": Permission denied\n", 20);
	else if (mode == 2)
		write(2, ": Not a directory\n", 18);
	else if (mode == 3)
		write(2, ": No such file or directory\n", 28);
	ft_putstr("\x1b[31m");
	
}

void	change_pwd(char **envorig, char *oldpwd)
{
	int		i;
	int		y;
	char	buff[2048];

	y = 0;
	i = 0;
	while (envorig[i] && ft_strcmp(envorig[i], "OLDPWD") != 61)
		i++;
	while (envorig[y] && ft_strcmp(envorig[y], "PWD") != 61)
		y++;
	if (envorig[i])
	{
		ft_strdel(&envorig[i]);
		envorig[i] = ft_strdup("OLDPWD=");
		ft_strconc(&envorig[i], oldpwd);
	}
	if (envorig[y])
	{
		ft_strdel(&envorig[y]);
		envorig[y] = ft_strdup("PWD=");
		ft_strconc(&envorig[y], getcwd(buff, 2048));
	}
	ft_putstr("\x1b[32m");
}
