#include "21sh.h"

int	handle_file(t_cmd *comd, char **envorig)
{
	int pid;
	int fd;
	char **arg;
	char buff[50];

	pid = 1;
	arg = malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("rm");
	arg[1] = ft_strdup(comd->file_out[0]);
	arg[2] = NULL;
	if (!ft_strcmp(comd->file_out[1], ">"))
		pid = fork();
	if (!pid)
	{
		run_bin(arg, envorig);
		exit(0);
	}
	wait(0);
	ft_freetab(arg);
	fd = open(comd->file_out[0], O_RDWR | O_CREAT);
	if (!ft_strcmp(comd->file_out[1], ">>"))
		while (read(fd, buff, 50));
	return (fd);
}

void	create_file(t_cmd *comd, char **envorig)
{
	t_cmd *list;

	list = comd;
	if (list->file_out)
		list->fd_out = handle_file(list, envorig);
	list = list->next;
	while (list && list->is_pipe)
	{
		if (list->file_out)
			list->fd_out = handle_file(list, envorig);
		list = list->next;
	}
}
