/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_chr_cmp_cpy_move_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:25 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 12:52:26 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
/*DESCRIPTION
       The  memchr()  function  scans  the  initial n bytes of the memory area
       pointed to by s for the first instance of c.  Both c and the  bytes  of
       the memory area pointed to by s are interpreted as unsigned char.
RETURN VALUE
       The  memchr()  and memrchr() functions return a pointer to the matching
       byte or NULL if the character does not occur in the given memory area.*/
{
	int	i;

	i = -1;
	while (++i < (int)n)
	{
		if (((const char *)s)[i] == (const char)c)
			return ((void *)s + i);
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	void	*res;
	size_t	i;

	i = 0;
	char bla[] = "foobar";
	while (i < strlen(bla))
		printf("%p\n", &bla[i++]);
	res = ft_memchr(bla, 'b', 6);
	printf("Result: %p\n", &(ft_memchr(bla, 'b', 6)));
}*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
/*DESCRIPTION
       The  memcmp()  function compares the first n bytes (each interpreted as
       unsigned char) of the memory areas s1 and s2.

RETURN VALUE
       The memcmp() function returns  an  integer  less  than,  equal  to,  or
       greater than zero if the first n bytes of s1 is found, respectively, to
       be less than, to match, or be greater than the first n bytes of s2.

       For a nonzero return value, the sign is determined by the sign  of  the
       difference  between  the  first  pair of bytes (interpreted as unsigned
       char) that differ in s1 and s2.

       If n is zero, the return value is zero.*/
{
	int	i;

	i = -1;
	if (n == 0)
		return (0);
	while (++i < (int)n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return ((int)(((unsigned char *)s1)[i])
				- ((int)(((unsigned char *)s2)[i])));
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char bla[] = "foobar";
	char blubb[] = "f0obar";
	printf("%d\n", ft_memcmp(bla, blubb, 4));
	printf("%d\n", memcmp(bla, blubb, 4));
}*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
/*DESCRIPTION
       The memcpy() function copies n bytes from memory area src to memory area
       dest.  The memory areas must not overlap.  Use memmove(3) if the  memory
       areas do overlap.
RETURN VALUE
       The memcpy() function returns a pointer to dest.
*/
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	if (!dest || !src)
		return (NULL);
	while (++i < (int)n)
	{
		while (++j < (int)n)
		{
			if (((char *)&dest)[i] == ((char *)&src)[j])
				return (ft_memmove((char *)dest, (char *)src, n), dest);
		}
		j = -1;
	}
	while (++k < (int)n)
		((char *)dest)[k] = ((char *)src)[k];
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
	char bla[] = "qwertzui";
	char blubb[] = "asdfghk";
	ft_memcpy(blubb, bla, 8);
	printf("%s\n", blubb);
}*/

void	*ft_memmove(void *dest, const void *src, size_t n)
/*
DESCRIPTION
       The  memmove()  function  copies n bytes from memory area src to memory
       area dest.  The memory areas may overlap: copying takes place as though
       the  bytes in src are first copied into a temporary array that does not
       overlap src or dest, and the bytes are then copied from  the  temporary
       array to dest.
RETURN VALUE
       The memmove() function returns a pointer to dest.*/
{
	size_t	i;
	int		reverse;

	i = -1;
	reverse = 0;
	if (!dest || !src)
		return (dest);
	while (++i < n)
		if (&((char *)dest)[0] == &((char *)src)[i])
			reverse = 1;
	if (reverse == 1)
	{
		i = -1;
		while (++i < n)
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char bla[] = "foobar";
	char blubb[] = "------";
	void *res = ft_memmove(blubb, bla, 3);
	printf("%s\n", blubb);
	res = NULL;
}*/

void	*ft_memset(void *s, int c, size_t n)
/*DESCRIPTION The memset() function fills the first n bytes of the
memory area pointed to by s with the constant byte c.
RETURN VALUE
       The memset() function returns a pointer to the memory area s.
*/
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = c;
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	char bla[] = "zzzzzzzzzzzz";
	ft_memset(bla, 61, 3);
	printf("%s\n", bla);
	memset(bla, 122, 3);
	printf("%s\n", bla);
}*/
