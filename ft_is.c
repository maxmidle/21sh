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

int	ft_isaggr(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd[i] || !ft_isdigit(cmd[i]))
		return (0);
	while (ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] != '>' || !cmd[i + 1] || cmd[i + 1] != '&')
		return (0);
	i += 2;
	while (cmd[i] && !ft_issep(cmd[i]))
	{
		if (!ft_isdigit(cmd[i]) && cmd[i] != '-')
			return (0);
		i++;
	}
	return (1);
}
