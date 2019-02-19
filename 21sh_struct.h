#ifndef SH_STRUCT_H
# define SH_STRUCT_H

typedef struct		s_cmd
{
	char		**cmd;
	int		fd_in;
	int		fd_out;
	int		fd_err;
	int		fd_dos;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}			t_cmd;

#endif
