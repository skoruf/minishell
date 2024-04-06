/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_calloc_strnstr_tolower_toupper.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:36:58 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 13:36:58 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
/*DESCRIPTION
       The  bzero()  function  erases  the  data  in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros (bytes  con‐
       taining '\0') to that area.
*/
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (i < n)
			((char *)s)[i++] = '\0';
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char bla[] = "zzzzzzzzzzzz";
	ft_bzero(bla, 3);
	printf("%c\n", bla[2]);
	printf("%c\n", bla[3]);
	bzero(bla, 3);
	printf("%c\n", bla[2]);
	printf("%c\n", bla[3]);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
/*
DESCRIPTION
       The calloc() function allocates memory for an array of  nmemb  elements
       of  size bytes each and returns a pointer to the allocated memory.  The
       memory is set to zero.  If nmemb or size is 0,  then  calloc()  returns
       either  NULL,  or a unique pointer value that can later be successfully
       passed to free().  If the multiplication of nmemb and size would result
       in  integer  overflow, then calloc() returns an error.
RETURN VALUE
       The malloc() and calloc() functions return a pointer to  the  allocated
       memory,  which  is  suitably  aligned for any built-in type.  On error,
       these functions return NULL.  NULL may also be returned by a successful
       call  to  malloc() with a size of zero, or by a successful call to cal‐
       loc() with nmemb or size equal to zero.
*/
{
	void		*mem;

	if (nmemb <= 0 || size <= 0)
		return (malloc(0));
	if (size < 2147483648 / nmemb)
	{
		mem = malloc(nmemb * size);
		if (mem)
		{
			ft_bzero(mem, nmemb * size);
			return (mem);
		}
		else
			return (NULL);
	}
	else
		return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{	
	
	char *bla = malloc(6);
	printf("%s\n", bla);
	char *bla2 = (char *)calloc(6, sizeof(bla2));
	printf("%s\n", bla2);

	bla2[0] = 'a';
	printf("%s\n", bla2);
}*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
/*DESCRIPTION
     The strnstr() function locates the first occurrence of the null-terminated
     string little in the string big, where not more than len characters are
     searched.  Characters that appear after a ‘\0’ character are not searched.
RETURN VALUES
     If little is an empty string, big is returned; if little occurs nowhere in
     big, NULL is returned; otherwise a pointer to the first character of the
     first occurrence of little is returned.
*/
{
	char	*b;
	size_t	ll;

	b = (char *)big;
	ll = ft_strlen(little);
	if (ll == 0)
		return (b);
	while (*b && len >= ll)
	{
		if (ft_strncmp(b, little, ll) == 0)
			return (b);
		b++;
		len--;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	const char big[30] = "aaabcabcd";
	//const char little[10] = "abcd";
//	printf("%d\n", ft_strncmp (big, "aaabc", 8));

//      8
	printf("8: %s\n", ft_strnstr(big, "aaabc", 5));
	printf("%s\n", strnstr(big, "aaabc", 5));
	//10
	printf("10: %s\n", ft_strnstr(big, "abcd", 9));
	printf("%s\n", strnstr(big, "abcd", 9));
	//12
	printf("12: %s\n", ft_strnstr("1", "a", 1));
	printf("%s\n", strnstr("1", "a", 1));
}*/

int	ft_tolower(int c)
/*
DESCRIPTION
       If c is an uppercase letter, tolower() returns  its  lowercase  equiva‐
       lent, if a lowercase representation exists in the current locale.  Oth‐
       erwise, it returns c. 
       If  c  is neither an unsigned char value nor EOF, the behavior of these
       functions is undefined.
RETURN VALUE
       The value returned is that of the converted letter, or c if the conver‐
       sion was not possible.*/
{
	if (c < -128)
		return (c);
	if (c >= -128 && c < -1)
		return (c + 256);
	if (c > 64 && c < 91)
		return (c + 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	int i = -2147483647;
	while (++i < 2147483647)
	{
		if (tolower(i) != ft_tolower(i))
			printf("%d\n", (i));
	}
	//printf("%d\n", (tolower(-1)));
	//printf("%d\n", (ft_tolower(-1)));
}*/

int	ft_toupper(int c)
/*
DESCRIPTION
       If c is a lowercase letter, toupper() returns its uppercase equivalent,
       if an uppercase representation exists in the  current  locale.   Other‐
       wise,  it  returns c.
       If  c  is neither an unsigned char value nor EOF, the behavior of these
       functions is undefined.
RETURN VALUE
       The value returned is that of the converted letter, or c if the conver‐
       sion was not possible.*/
{
	if (c < -128)
		return (c);
	if (c >= -128 && c < -1)
		return (c + 256);
	if (c > 96 && c < 123)
		return (c - 32);
	else
		return (c);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	int i = -2147483647;
	while (++i < 2147483647)
	{
		if (toupper(i) != ft_toupper(i))
			printf("%d\n", (i));
	}
	printf("%c\n", (toupper('s')));
	printf("%c\n", (ft_toupper('s')));
}*/
