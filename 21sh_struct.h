/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:38:50 by radler            #+#    #+#             */
/*   Updated: 2019/04/09 17:39:26 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCT_H
# define SH_STRUCT_H

typedef struct		s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	int				save_in;
	int				save_out;
	int				save_err;
	int				is_pipe;
	char			*file_in;
	char			**file_out;
	char			*aggreg;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

#endif
