#include <curses.h>
#include <term.h>
#include <stdlib.h>

char *tgetstr(char *id, char **area);

int	main()
{
		tgetent(NULL, getenv("TERM"));
		tputs(tgoto(tgetstr("up", NULL), 0, 2), 1, putchar);
	return (0);
}
