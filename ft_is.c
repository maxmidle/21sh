#include "21sh.h"

int	ft_iscmdsep(char *cmd)
{
	if (!ft_strcmp(cmd, "|") || !ft_strcmp(cmd, ";"))
		return (1);
	return (0);
}

int	ft_isredi(char *cmd)
{
	if (!ft_strcmp(cmd, ">") || !ft_strcmp(cmd, ">>") ||
		!ft_strcmp(cmd, "<") || !ft_strcmp(cmd, "<<"))
		return (1);
	return (0);
}
