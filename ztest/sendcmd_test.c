#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int	main()
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	char buff[2];
	buff[0] = 'a';
	if (!pid)
	{
		dup2(fd[0], 0);
		printf("5sec\n");
		sleep(5);
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			putchar(buff[0]);
		}
	buff[0] = 'a';
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			putchar(buff[0]);
		}
	buff[0] = 'a';
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			putchar(buff[0]);
		}
		printf("\nchild over\n");
		return (0);
	}
	else
	{
		dup2(fd[1], 1);
		while(read(0, buff, 1))
			write(1, buff, 1);
	}
	wait(0);
	return (0);
}
