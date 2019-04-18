/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:50:51 by radler            #+#    #+#             */
/*   Updated: 2019/04/17 11:52:17 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_last_pipe(char **str)
{
	int		i;
	int		size;
	char	*tmp;

	i = ft_strlen(*str) - 1;
	tmp = NULL;
	while (i > 0 && str[0][i] != '|')
		i--;
	i--;
	while (i > 0 && str[0][i] != '|' && str[0][i] != ';')
		i--;
	if (i > 0)
		i++;
	size = ft_strlen(&str[0][i]);
	ft_putstr("pipe : \x1B[36m");
	ft_putstr(&str[0][i]);
	ft_putstr("\x1B[33m $>\x1B[0m");
	tmp = tc_readline(NULL, 10 + size);
	ft_strconc(str, tmp);
	free(tmp);
	if (get_last_char(*str) == '|')
		get_last_pipe(str);
}

int		bad_sep(char *str)
{
	int		i;
	int		res;

	i = 0;
	while (str && str[i])
	{
		res = 0;
		while (str[i] && str[i] != '|' && str[i] != ';')
		{
			if (!ft_issep(str[i]) && str[i] != '|' && str[i] != ';')
				res = 1;
			i++;
		}
		if (res == 0)
		{
			write(2, "-21sh: syntax error:\n\ttoken requiered before \'", 46);
			write(2, &str[i], 1);
			write(2, "\'\n", 2);
			ft_putstr("\x1b[31m");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int		bad_redi(char *str)
{
	int		i;
	int		res;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			res = 0;
			if (str[i + 1] && str[i + 1] == str[i])
				i++;
			i++;
			while (str[i] && str[i] && !ft_ischarsep(str[i]))
			{
				if (!ft_issep(str[i]))
					res = 1;
				i++;
			}
			if (!res)
				return (print_bad_redi());
		}
		else
			i++;
	}
	return (0);
}

int		print_bad_redi(void)
{
	write(2, "-21sh: syntax error:\n\t", 22);
	write(2, "token requiered after redirection\n", 34);
	ft_putstr("\x1b[31m");
	return (1);
}

int		bad_redi_form(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] && str[i + 1] == str[i])
			{
				if (str[i + 2] && str[i + 2] == str[i + 1])
				{
					write(2, "-21sh: syntax error:\n\t", 22);
					write(2, "unexpected redirection \'", 24);
					write(2, &str[i], 3);
					write(2, "\'\n", 2);
					ft_putstr("\x1b[31m");
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
