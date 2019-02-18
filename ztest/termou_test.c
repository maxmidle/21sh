#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include "21sh/libft/libft/libft.h"


int main (void)
{
        struct termios attributs;
        int fd = STDIN_FILENO;
        char c[3];
 
        if (!isatty (fd)) {
                perror ("isatty");
                return EXIT_FAILURE;
        }
	printf("%d\n", fd);
 
        /* On récupère les attributs actuels */
        if (tcdrain (fd) == -1 || tcgetattr (fd, &attributs) == -1) {
                perror ("tcgetattr");
                return EXIT_FAILURE;
        }
 
        /* Passage en mode non canonique */
        attributs.c_lflag &= ~ICANON;
     
    /* Suppression de l'echo */
   attributs.c_lflag &= ~ECHO;
 
        /* On applique les nouveaux attributs */
        if (tcsetattr (fd, TCSADRAIN, &attributs) == -1) {
        perror ("tcsetattr");
                return EXIT_FAILURE;
        }
	char *str;
	int i = 0;
	int stop = 1;
	int cursor = 0;
	int size = 0;
 	str = ft_strnew(0);
        while (stop)
	{
		size = ft_strlen(str);
		ft_strclr(c);
		read (fd, c, 3);
		if ((c[0] >= 'A' && c[0] <= 'z'))
		{
			ft_strins(&str, c, cursor);
			cursor++;
		}
		else if (c[0] == 127 && cursor > 0)
		{
			ft_strnconc(&str, cursor - 1, &str[cursor] , size - cursor);
			cursor--;
		}
		else if (c[0] == '\n')
		{
			write(1, "\n", 1);
			cursor = 0;
        		if (!ft_strcmp(str, "exit"))
				stop = 0;
			ft_strclr(str);
		}
		else if (!ft_strcmp(c, "\033[D"))
		{
			if (cursor > 0)
				cursor--;
		}
		else if (!ft_strcmp(c, "\033[C"))
		{
			if (cursor < size)
				cursor++;
		}
		i = 0;
		while (cursor + i < ft_strlen(str))
		{
			write(1, "\033[C", 3);
			i++;
		}
		i = 0;
		while (i < size + 1)
		{
			write(1, "\033[D", 3);
			write(1, " ", 1);
			write(1, "\033[D", 3);
			i++;
		}	
		write (1, str, ft_strlen(str));
		i = 0;
		while (cursor + i < ft_strlen(str))
		{
			write(1, "\033[D", 3);
			i++;
		}
        }
        
        /* NE PAS OUBLIER DE REMETTRE LES ANCIENS ATTRIBUTS */
 
        attributs.c_lflag |= ICANON;
    attributs.c_lflag |= ECHO;
        if (tcsetattr (fd, TCSADRAIN, &attributs) == -1) {
        perror ("tcsetattr");
                return EXIT_FAILURE;
        }
 
        return EXIT_SUCCESS;
}
