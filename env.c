/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:19:41 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:54:37 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**env(char **command, char **envorig, char **envexec)
{
	int i;
	int stop;

	stop = 0;
	i = 1;
	while (!stop && command[i] && ft_strcmp(command[i], "env"))
	{
		if (ft_strchr(command[i], '='))
			envexec = ft_setenv(envexec, command[i]);
		else if (command[i][0] == '-')
			envexec = env_option(envexec, &command[i], &i);
		else
		{
			stop = 1;
			i--;
		}
		i++;
	}
	if (!command[i])
		ft_print_words_tables(envexec);
	if (command[i] && !ft_strcmp(command[i], "env"))
		return (env(&command[i], envorig, envexec));
	else
		return (envexec);
}

char	**env_option(char **envexec, char **command, int *u)
{
	int i;

	i = 1;
	while (command[0][i])
	{
		if (command[0][i] == 'i')
			envexec = ft_unsetenv_all(envexec);
		else if (command[0][i] == 'u')
		{
			envexec = ft_unsetenv(envexec, command[1]);
			u[0]++;
		}
		i++;
	}
	return (envexec);
}

char	**ft_setenv(char **environ, char *var)
{
	int		i;
	char	**envout;

	i = ft_tablen(environ);
	if (!(envout = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (environ[i])
	{
		if (!ft_strccmp(environ[i], var, '='))
		{
			envout[i] = ft_strdup(var);
			var = NULL;
		}
		else
			envout[i] = ft_strdup(environ[i]);
		i++;
	}
	if (var)
		envout[i++] = ft_strdup(var);
	envout[i] = NULL;
	ft_freetab(environ);
	return (envout);
}

char	**ft_unsetenv(char **environ, char *var)
{
	int		i;
	int		y;
	char	**envout;

	i = ft_tablen(environ);
	if (!(envout = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	y = 0;
	while (environ[i + y])
	{
		if (ft_strcmp(environ[i + y], var) == 61)
			y++;
		else if (environ[i + y])
		{
			envout[i] = ft_strdup(environ[i + y]);
			i++;
		}
	}
	envout[i] = NULL;
	ft_freetab(environ);
	return (envout);
}

char	**ft_unsetenv_all(char **envexec)
{
	char **envout;

	envout = NULL;
	if (!(envout = (char **)malloc(sizeof(char *))))
		return (NULL);
	envout[0] = NULL;
	ft_freetab(envexec);
	return (envout);
}
