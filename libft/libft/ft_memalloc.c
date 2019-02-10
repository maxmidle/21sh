/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:29:01 by radler            #+#    #+#             */
/*   Updated: 2017/11/14 17:52:07 by radler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem;
	char *pmem;

	mem = NULL;
	mem = (void *)malloc(sizeof(char) * size);
	if (mem == NULL)
		return (NULL);
	pmem = (char *)mem;
	while (size--)
	{
		*pmem = '\0';
		pmem++;
	}
	return (mem);
}
