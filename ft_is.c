#include "21sh.h"

int	ft_iscmdsep(char *cmd)
{
	if (!ft_strncmp(cmd, "|", 1) || !ft_strncmp(cmd, ";", 1))
		return (1);
	return (0);
}

int	ft_isredi(char *cmd)
{
	if (!ft_strcmp(cmd, ">") || !ft_strcmp(cmd, ">>"))
		return (1);
	if (!ft_strcmp(cmd, "<") || !ft_strcmp(cmd, "<<"))
		return (2);
	return (0);
}

int	ft_ischarsep(char cmd)
{
	if (cmd == '<' || cmd == '>' || cmd == ';' || cmd == '|')
		return (1);
	return (0);
}
