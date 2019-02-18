#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	pid_t pid = 1;
	pid_t pid2 = 1;
	char buff[60];
	int df[2];
	int fd = open(av[1], O_RDWR);
	while (read(fd, buff, 1))
		putchar(buff[0]);
	int fd2 = open(av[2], O_WRONLY);
	pid = fork();
	if (!pid)
	{
		dup2(fd, 2);
		dup2(fd, 1);
		printf("si je suis pas dans un fichier c'est relou\n");
		write(2, "test\n", 5);
		write(2, "test2\n", 5);
		write(2, "test3\n", 5);
		write(2, "test4\n", 5);
		write(2, "test5\n", 5);
		printf("et ca ?\n");
		return (0);
	}
	else
	{
		printf("attente du fils\n");
		wait(0);
		printf("fils  [OK]\n");
	//	dup2(df[0], 0);
	//	read(df[0], buff, 60);
	//	printf("%s\n", buff);
		return (0);
	}
}
