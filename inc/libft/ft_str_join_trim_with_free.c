/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join_trim_with_free.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:15:39 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/11/14 18:15:41 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
/*
DESCRIPTION:  Allocates (with malloc(3)) and returns a new string, which is the
	   result of the concatenation of ’s1’ and ’s2’. Frees s1 before returning.
RETURN VALUE: The new string. NULL if the allocation fails.*/
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1)
		free((char *)s1);
	return (res);
}

static size_t	check_set(const char c, const char *set)
{
	size_t	res;

	res = 0;
	while (*set)
	{
		if (*set == c)
			res = 1;
		set++;
	}
	return (res);
}

static char	*graceful_exit(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_strtrim_free(const char *s1, const char *set)
/*
DESCRIPTION: Allocates (with malloc(3)) and returns a copy of ’s1’ with the
	     characters specified in ’set’ removed from the beginning and the
	     end of the string. Frees s1 before returning.
RETURN VALUE:The trimmed string. NULL if the allocation fails.
*/
{
	int		i;
	char	*res;

	s1 = (char *)s1;
	while (*s1 && check_set(*s1, set))
		s1++;
	i = ft_strlen(s1) - 1;
	if (i <= 0)
		return (graceful_exit());
	while (*s1 && check_set(s1[i], set))
		i--;
	i++;
	if (i < 1)
		return (graceful_exit());
	res = (char *)malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, i);
	res[i] = '\0';
	return (res);
}
