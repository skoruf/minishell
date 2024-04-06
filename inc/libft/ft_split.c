/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:12:19 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/11 13:12:20 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	switcher;

	count = 0;
	switcher = 0;
	while (*s)
	{
		if (*s != c && switcher == 0)
		{
			switcher = 1;
			count++;
		}
		else if (*s == c)
			switcher = 0;
		s++;
	}
	return (count);
}

static char	**graceful_exit(char **res, int x)
{
	int	i;

	i = -1;
	while (++i < x)
		free(res[i]);
	free(res);
	return (NULL);
}

static char	*fill_array(const char *s, int start, int end)
{
	int		i;
	int		size;
	char	*res;

	i = 0;
	size = end - start;
	if (end <= 0 || start < 0)
		return (NULL);
	res = malloc((size + 1) * sizeof(*res));
	if (!res)
		return (NULL);
	ft_bzero(res, (size + 1) * sizeof(*res));
	while (start < end)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split(const char *s, char c)
/*
DESCRIPTION: Allocates (with malloc(3)) and returns an array of strings
	     obtained by splitting ’s’ using the character ’c’ as a delimiter.
	     The array must end with a NULL pointer.
RETURN VALUE: The array of new strings resulting from the split. NULL if the
	     allocation fails.*/
{
	int		i;
	int		x;
	int		pos;
	char	**res;

	res = ft_calloc(count_words(s, c) + 1, sizeof(res));
	if (!res)
		return (NULL);
	x = 0;
	pos = -1;
	i = -1;
	while (++i <= (int)ft_strlen(s))
	{
		if ((s[i] != c) && (pos < 0))
			pos = i;
		else if ((s[i] == c || i == (int)ft_strlen(s)) && pos >= 0)
		{
			res[x++] = fill_array(s, pos, i);
			if (!res[x - 1])
				return (graceful_exit(res, x));
			pos = -1;
		}
	}
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	char ** bla = ft_split("   fg zih  ", ' ');
	if (bla)
	{
		printf("%s\n", bla[0]);
		printf("%s\n", bla[1]);
		//printf("%s\n", bla[2]);
		//printf("%s\n", bla[3]);
		//printf("%s\n", bla[4]);
		//printf("%s\n", bla[5]);
		//free(bla[5]);
		//free(bla[4]);
		//free(bla[3]);
		//free(bla[2]);
		free(bla[1]);
		free(bla[0]);
		free(bla);
	}
}*/
