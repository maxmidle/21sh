/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:50:55 by radler            #+#    #+#             */
/*   Updated: 2017/11/16 15:14:06 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words_tables(char **tabl)
{
	unsigned long	i;
	int				j;

	i = 0;
	j = 0;
	while (tabl[i] != '\0')
	{
		j = 0;
		while (tabl[i][j] != '\0')
		{
			ft_putchar(tabl[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
