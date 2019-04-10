/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:20:41 by radler            #+#    #+#             */
/*   Updated: 2019/04/10 09:58:02 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_chain(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	while (list && list->prev)
		list = list->prev;
	while (list)
	{
		ft_strdel(&list->aggreg);
		if (list->cmd)
			ft_freetab(list->cmd);
		if (list->fd_in != 0 && list->fd_in > 2)
			close(list->fd_in);
		if (list->fd_out != 1 && list->fd_in > 2)
			close(list->fd_out);
		if (list->file_in)
			ft_strdel(&list->file_in);
		close_chain(list);
		list->prev = NULL;
		list = list->next;
		comd->next = NULL;
		free(comd);
		comd = list;
	}
}

void	close_chain(t_cmd *comd)
{
	t_cmd *list;

	list = comd;
	if (list->file_out)
	{
		ft_freetab(list->file_out);
		list->file_out = NULL;
	}
	close(list->save_in);
	close(list->save_out);
	close(list->save_err);
}
