/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:22:07 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:54:17 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*tilde(char *command, char **environ)
{
	int		i;
	int		y;
	char	*str;

	y = 0;
	while (environ[y] && !(ft_strstr(environ[y], "HOME=")))
		y++;
	if (!environ[y])
		return (command);
	str = ft_strnew(ft_strlen(command) + ft_strlen(environ[y]));
	str = ft_strccpy(str, command, '~');
	i = ft_strlen(str) + 1;
	str = ft_strcat(str, &environ[y][5]);
	str = ft_strcat(str, &command[i]);
	free(command);
	return (str);
}
