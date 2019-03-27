/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:41:32 by radler            #+#    #+#             */
/*   Updated: 2019/01/30 18:43:33 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tabl)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!tabl)
		return (NULL);
	cpy = (char **)malloc(sizeof(char *) * (ft_tablen(tabl) + 1));
	while (tabl[i])
	{
		cpy[i] = ft_strdup(tabl[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
