/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_len_chr_rchr_iteri_mapi.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:16:22 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 13:16:23 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
//DESCRIPTION: Returns the length of the string excluding the NUL-Terminator.
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
/*
DESCRIPTION
       The  strchr() function returns a pointer to the first occurrence of the
       character c in the string s.
RETURN VALUE
       The strchr() and strrchr() functions return a pointer  to  the  matched
       character  or NULL if the character is not found.  The terminating null
       byte is considered part of the string, so that if  c  is  specified  as
       '\0', these functions return a pointer to the terminator.*/
{
	if (s)
		while (*s)
			if (*s++ == (char)c)
				return ((char *)--s);
	return ((char *) NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char bla[] = "foobar";
	printf("%s\n", ft_strchr(bla, 111));
	printf("%s\n", strchr(bla, 111));
}*/

char	*ft_strrchr(const char *s, int c)
/*
DESCRIPTION
       The strrchr() function returns a pointer to the last occurrence of  the
       character c in the string s.
RETURN VALUE
       The strchr() and strrchr() functions return a pointer  to  the  matched
       character  or NULL if the character is not found.  The terminating null
       byte is considered part of the string, so that if  c  is  specified  as
       '\0', these functions return a pointer to the terminator.*/
{
	int	i;
	int	pos;

	i = -1;
	pos = 0;
	while (s[++i])
		if (s[i] == (const char)c)
			pos = i;
	if (s[pos] == (const char)c)
		return (((char *)s) + pos);
	else if (s[i] == (const char)c)
		return (((char *)s) + i);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char bla[] = "";
	//char * empty = (char*)calloc(1, 1);
	printf("outside: %d\n", ft_strncmp(bla, "", ft_strlen(bla)));
	printf("%s\n", ft_strrchr(bla, 0)); 
	printf("%s\n", strrchr(bla, 0)); 
	//free(empty);
	
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
/*
DESCRIPTION: Applies the function ’f’ to each character of the string ’s’, and
	     passing its index as first argument to create a new string (with
	     malloc(3)) resulting from successive applications of ’f’.
RETURN VALUE: The string created from the successive applications of ’f’.
	     Returns NULL if the allocation fails.*/
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) + ft_strlen(s));
	if (!res)
		return (NULL);
	while (++i < (int)ft_strlen(s))
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
/*
DESCRIPTION: Applies the function ’f’ on each character of the string passed as
	     argument, passing its index as first argument. Each character is
	     passed by address to ’f’ to be modified if necessary.*/
{
	unsigned int	i;
	size_t			l;

	i = -1;
	l = ft_strlen(s);
	while (++i < l)
		f(i, &s[i]);
}
