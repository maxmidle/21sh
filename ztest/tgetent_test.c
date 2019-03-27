#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include "../libft/libft/libft.h"


typedef struct s_curso
{
	size_t c;
	size_t l;
	size_t lc[500];
}		t_curso;

int	main()
{
	char		buff[5];
	struct termios	term;
	struct termios	termorig;
	char		*str;
	t_curso cpos;
	cpos.c = 0;
	cpos.l = 0;
	cpos.lc[0] = 0;

	write(1, "&>", 2);
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &termorig);
	term.c_lflag = ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	tgetent(NULL, getenv("TERM"));
	buff[4] = '\0';
	read(0, &buff, 4);
	str = ft_strnew(0);
	while (buff[0] != '\n')
	{
		if (buff[0] == '\033')
		{
			if (!ft_strcmp(buff, "\033[D") && cpos.c > 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				cpos.c--;
			}
			if (!ft_strcmp(buff, "\033[C") && cpos.c < ft_strlen(str))
			{
				tputs(tgetstr("nd", NULL), 1, ft_putchar);
				cpos.c++;
			}
		}
		else if (buff[0] == 127)
		{
			if (cpos.c > 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				tputs(tgetstr("dm", NULL), 1, ft_putchar);
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
				tputs(tgetstr("ed", NULL), 1, ft_putchar);	
				cpos.c--;
			}
		}
		else
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar);
			write(1, &buff, 1);
			tputs(tgetstr("ei", NULL), 1, ft_putchar);
			ft_strins(&str, buff, cpos.c);
			cpos.c++;
			cpos.lc[0]++;
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
