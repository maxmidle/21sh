/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:08:03 by radler            #+#    #+#             */
/*   Updated: 2017/11/17 19:41:52 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	unsigned int	fspc;
	int				bspc;
	int				i;
	size_t			len;
	char			*str;

	if (!s)
		return (NULL);
	i = 0;
	bspc = 0;
	fspc = 0;
	str = NULL;
	while (ft_issep(s[i++]))
		fspc++;
	if (s[fspc] == '\0' || s[0] == '\0')
		return (ft_strnew(0));
	i = ft_strlen(s) - 1;
	while (ft_issep(s[i--]))
		bspc++;
	len = ft_strlen(s) - fspc - bspc;
	str = ft_strsub(s, fspc, len);
	if (str == NULL)
		return (NULL);
	return (str);
}
