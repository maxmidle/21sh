/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:32:26 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 19:39:28 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int i;
	int nbmot;

	i = 0;
	nbmot = 0;
	while (str[i])
	{
		while (str[i] != c && str[i])
		{
			if (str[i + 1] == c || !str[i + 1])
				nbmot++;
			i++;
		}
		if (str[i])
			i++;
	}
	return (nbmot);
}

static char	**tab_init(const char *str, char **tstr, char c)
{
	int		taillemot;
	int		i;
	int		index;

	index = 0;
	i = 0;
	taillemot = 0;
	if (!(tstr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1))))
		return (NULL);
	while (index < count_words(str, c))
	{
		taillemot = 0;
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i])
		{
			taillemot++;
			i++;
		}
		if (!(tstr[index] = (char *)malloc(sizeof(char) * (taillemot + 1))))
			return (NULL);
		index++;
	}
	return (tstr);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**tstr;
	int		i;
	int		y;
	int		x;

	if (!s)
		return (NULL);
	i = 0;
	x = 0;
	tstr = NULL;
	if (!(tstr = tab_init(s, tstr, c)))
		return (NULL);
	while (i < count_words(s, c))
	{
		y = 0;
		while (s[x] == c && s[x])
			x++;
		while (s[x] != c && s[x])
			tstr[i][y++] = s[x++];
		tstr[i][y] = '\0';
		i++;
	}
	tstr[i] = NULL;
	return (tstr);
}
