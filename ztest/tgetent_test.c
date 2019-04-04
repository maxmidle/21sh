#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include "../libft/libft/libft.h"

int	main()
{
	char		buff[5];
	struct termios	term;
	struct termios	termorig;
	char		*str;
	int cpos;

	write(1, "&>", 2);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &termorig);
	term.c_lflag = ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	tgetent(NULL, getenv("TERM"));
	buff[0] = '\0';
	buff[1] = '\0';
	buff[2] = '\0';
	buff[3] = '\0';
	buff[4] = '\0';
	cpos = 0;
	read(0, &buff, 4);
	str = ft_strnew(0);
	while (buff[0] != '\n')
	{
		if (buff[0] == '\033')
		{
			if (!ft_strcmp(buff, "\033[D") && cpos > 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				cpos--;
			}
			else if (!ft_strcmp(buff, "\033[C") && cpos < (int)ft_strlen(str))
			{
				tputs(tgetstr("nd", NULL), 1, ft_putchar);
				cpos++;
			}
		}
		else if (buff[0] == 127)
		{
			if (cpos > 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				tputs(tgetstr("dm", NULL), 1, ft_putchar);
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
				tputs(tgetstr("ed", NULL), 1, ft_putchar);	
				cpos--;
				str = ft_strcdel(str, cpos);
			}
		}
		else
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar);
			write(1, &buff, 1);
			tputs(tgetstr("ei", NULL), 1, ft_putchar);
			buff[1] = '\0';
			ft_strins(&str, buff, cpos);
			cpos++;
		}
		buff[0] = '\0';
		buff[1] = '\0';
		buff[2] = '\0';
		buff[3] = '\0';
		read(0, &buff, 4);
	}
	write(1, "\n", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	free(str);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &termorig);
	return (0);
}
