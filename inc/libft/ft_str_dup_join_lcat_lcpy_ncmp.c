/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dup_join_lcat_lcpy_ncmp.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:22:05 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 13:22:06 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
/*DESCRIPTION: The strdup function returns a pointer to a new string which is a
duplicate of the string s. Memory for the new string is obtained with malloc(3),
and can be freed with free(3).
RETURN VALUE: On success, the strdup function returns a pointer to the
duplicated string. It returns NULL if insufficient memory was available.*/
{
	char	*dup;
	int		i;
	int		l;

	i = -1;
	l = ft_strlen(src);
	dup = (char *)malloc(sizeof(*dup) * (l + 1));
	if (!dup)
		return (NULL);
	while (src[++i])
		dup[i] = src[i];
	return (dup[i] = '\0', dup);
}
/*
#include <stdio.h>


int	main(void)
{
	printf("%s\n", ft_strdup("Lorem ipsum dolor sit amet"));
}*/

char	*ft_strjoin(char const *s1, char const *s2)
/*
DESCRIPTION:  Allocates (with malloc(3)) and returns a new string, which is the
	      result of the concatenation of ’s1’ and ’s2’.
RETURN VALUE: The new string. NULL if the allocation fails.*/
{
	int		i;
	int		ls1;
	int		lsres;
	char	*res;

	i = -1;
	ls1 = ft_strlen(s1);
	lsres = ls1 + ft_strlen(s2);
	res = malloc((lsres + 1) * sizeof(char));
	if (res)
	{
		while (++i < ls1)
			res[i] = s1[i];
		while (i < lsres)
		{
			res[i] = s2[i - ls1];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strjoin("foo", "bar"));
}*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
/*
DESCRIPTION
     The strlcpy() and strlcat() functions copy and concatenate strings re‐
     spectively. Strlcpy() and strlcat() take the full size of the buffer (not
     just the length) and guarantee to NUL-terminate the result (as long as
     size is larger than 0 or, in the case of strlcat(), as long as there is at
     least one byte free in dst).  Note that a byte for the NUL should be in-
     cluded in size.  Also note that strlcpy() and strlcat() only operate on true “C”
     strings.  This means that for strlcpy() src must be NUL-terminated and
     for strlcat() both src and dst must be NUL-terminated.
     The strlcat() function appends the NUL-terminated string src to the end
     of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
     nating the result.
RETURN VALUES
     The strlcpy() and strlcat() functions return the total length of the
     string they tried to create. For strlcat() that means the initial length
     of dst plus the length of src. While this may seem somewhat confusing, it
     was done to make truncation detection simple.
     Note, however, that if strlcat() traverses size characters without find‐
     ing a NUL, the length of the string is considered to be size and the des‐
     tination string will not be NUL-terminated (since there was no space for
     the NUL).  This keeps strlcat() from running off the end of a string.  In
     practice this should not happen (as it means that either size is incor‐
     rect or that dst is not a proper “C” string).  The check exists to pre‐
     vent potential security problems in incorrect code.
*/
{
	const char	*src_copy;
	char		*dest_copy;
	size_t		i;
	size_t		l_dest;

	src_copy = src;
	dest_copy = dest;
	i = size;
	while (i-- != 0 && *dest_copy)
		dest_copy++;
	l_dest = ft_strlen(dest) - ft_strlen(dest_copy);
	i = size - l_dest;
	if (i == 0)
		return (l_dest + ft_strlen(src_copy));
	while (*src_copy)
	{
		if (i != 1)
		{
			*dest_copy++ = *src_copy;
			i--;
		}
		src_copy++;
	}
	return (*dest_copy = '\0', l_dest + (src_copy - src));
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char test[256] = "\0zxcvzxcvzxcvxzcvzxcv";
	printf("%zu-", ft_strlcat(test, "asdf", 16));
	printf("%s\n", test);
	printf("%zu-", ft_strlcat(test, "asdf", 6));
	printf("%s\n", test);
	printf("%zu-", ft_strlcat(test, "asdf", 4));
	printf("%s\n", test);
	printf("%zu-", ft_strlcat(test, "", 16));
	printf("%s\n", test);
	printf("%zu-", ft_strlcat(test, "asdf", 0));
	printf("%s\n\n", test);
	printf("4-asdf\n8-asdfa\n8-asdfa\n5-asdfa\n4-asdfa\n");
}*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = -1;
	if (size != 0)
	{
		while (++i < size - 1 && src[i] != '\0')
			dest[i] = src[i];
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "foofoofoo";
	char	dest[] = "bar";
	unsigned int	size_dest;
	unsigned int	l;

	printf("Content of src: %s\n", src);
	printf("Content of dest: %s\n", dest);
	size_dest = ft_strlen(dest) + 1;
	l = ft_strlcpy(dest, src, 15);
	printf("Content of dest after strlcpy: %s\n", dest);
	printf("Return value = length of src: %d\n", l);
}*/

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
/*DESCRIPTION: The strncmp function compares only the first (at most) n bytes
of s1 and s2.
RETURN VALUES: 0 if the s1 and s2 are equal, a negative value if s1 is less
than s2, or a positive value if s1 is greater than s2.*/
{
	unsigned int	i;

	i = 0;
	while (i < n && !(s1[i] == '\0' && s2[i] == '\0'))
	{
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char *argv[])
{

	(void)argc;
	(void)argv;
	char *bla = "";
	printf("%d\n", ft_strncmp("", bla, ft_strlen(bla)));
	printf("%d\n", strncmp("bla", "bld", 3));
}*/
