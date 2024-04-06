/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:17:14 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/08 17:17:17 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*do_the_thing(char const *s, unsigned int st, unsigned int ms)
/*norminette knows no mercy...*/
{
	unsigned int	i;
	char			*sub;

	i = 0;
	sub = (char *)malloc(ms * sizeof(char));
	if (sub != NULL)
	{
		while (i < ms - 1)
		{
			sub[i] = s[st + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
/*
DESCRIPTION: Allocates (with malloc(3)) and returns a substring from the string
	     ’s’. The substring begins at index ’start’ and is of maximum size
	     ’len’.
RETURN VALUE: The substring. NULL if the allocation fails.*/
{
	char			*sub;
	unsigned int	memsize;

	if ((size_t)start > ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > ft_strlen(s) - start)
		memsize = ft_strlen(s) - start + 1;
	else
		memsize = len + 1;
	return (do_the_thing(s, start, memsize));
}
/*
#include <stdio.h>
int	main(void)
{
	char *bla = ft_substr("0123456789", 9, 10);
	printf("%s\n", bla);
	char *bla2 = ft_substr("0123456789", 9, 1);
	printf("%s\n", bla2);
	free(bla);
	free(bla2);
}*/
