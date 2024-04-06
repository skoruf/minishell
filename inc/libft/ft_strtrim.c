/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:27:15 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/08 18:27:18 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strtrim(const char *s1, const char *set)
/*
DESCRIPTION: Allocates (with malloc(3)) and returns a copy of ’s1’ with the
	     characters specified in ’set’ removed from the beginning and the
	     end of the string.
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

/*

int	main(void)
{
	//char *str ="abcdba";
	char *res = ft_strtrim("abcdba", "acb");
	printf("Result: %s\n", res);
	printf("Length: %zu\n", ft_strlen(res));
	free(res);
}*/
