#include <curses.h>
#include <term.h>

char *tgetstr(char *id, char **area);

int	main()
{
		tputs(tgoto(tgetstr("up", NULL), 0, 2), 1, putchar);
	return (0);
}
