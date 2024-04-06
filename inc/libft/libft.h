/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:39:06 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/06 14:39:07 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define BASE_SMALL "0123456789abcdef"
# define BASE_BIG "0123456789ABCDEF"
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_lst
{
	void			*content;
	struct s_list	*next;
}					t_lst;
/*DESCRIPTION: The  atoi() function converts the initial portion of the string
pointed to by nptr to int.  The behavior is the same as	strtol(nptr, NULL, 10);
except that atoi() does not detect errors.
RETURN VALUE: The converted value or 0 on error.*/
int					ft_atoi(const char *nptr);
/*DESCRIPTION: The  bzero()  function  erases  the  data  in the n bytes of the
memory starting at the location pointed to by s, by writing zeros (bytes  con‐
taining '\0') to that area.*/
void				ft_bzero(void *s, size_t n);
/*DESCRIPTION: The calloc() function allocates memory for an array of nmemb
elements of  size bytes each and returns a pointer to the allocated memory.
The memory is set to zero.  If nmemb or size is 0,  then  calloc()  returns
either  NULL,  or a unique pointer value that can later be successfully
passed to free().  If the multiplication of nmemb and size would result
in  integer  overflow, then calloc() returns an error.
RETURN VALUE: The malloc() and calloc() functions return a pointer to the
allocated memory, which is suitably aligned for any built-in type. On error,
these functions return NULL.  NULL may also be returned by a successful call to
malloc() with a size of zero, or by a successful call to calloc() with nmemb or
size equal to zero.*/
void				*ft_calloc(size_t nmemb, size_t size);
/*DESCRIPTION: checks for an alphanumeric character; it is equivalent to
(isalpha(c) || isdigit(c)).
RETURN VALUE: The values returned are nonzero if the character c falls into the
tested class, and zero if not.*/
int					ft_isalnum(int c);
/*DESCRIPTION: checks  for an alphabetic character; in the standard "C" locale,
it is equivalent to (isupper(c) ||  islower(c)).
RETURN VALUE: The values returned are nonzero if the character c falls into the
tested class, and zero if not.*/
int					ft_isalpha(int c);
/*DESCRIPTION: checks whether c is a 7-bit unsigned char value that  fits  into
the ASCII character set.
RETURN VALUE: The values returned are nonzero if the character c falls into the
tested class, and zero if not.*/
int					ft_isascii(int c);
/*DESCRIPTION: checks for a digit (0 through 9).
RETURN VALUE: The values returned are nonzero if the character c falls into the
tested class, and zero if not.*/
int					ft_isdigit(int c);
/*DESCRIPTION: checks for any printable character including space.
RETURN VALUE: The values returned are nonzero if the character c falls into the
tested class, and zero if not.*/
int					ft_isprint(int c);
/*DESCRIPTION: Allocates (with malloc(3)) and returns a string representing the
integer received as an argument. Negative numbers must be handled.
RETURN VALUE: The string representing the integer.
NULL if the allocation fails.*/
char				*ft_itoa(int n);
/*DESCRIPTION: The memchr function scans the initial n bytes of the memory area
pointed to by s for the first instance of c.  Both c and the  bytes  of the
memory area pointed to by s are interpreted as unsigned char.
RETURN VALUE: Returns a pointer to the matching byte or NULL if the character
does not occur in the given memory area.*/
void				*ft_memchr(const void *s, int c, size_t n);
/*DESCRIPTION: The memcmp function compares the first n bytes (each interpreted
as unsigned char) of the memory areas s1 and s2.
RETURN VALUE: The memcmp function returns an integer less than, equal to, or
greater than zero if the first n bytes of s1 is found, respectively, to be less
than, to match, or be greater than the first n bytes of s2.
For a nonzero return value the sign is determined by the sign of the difference
between the first pair of bytes (interpreted as unsigned char) that differ in
s1 and s2. If n is zero, the return value is zero.*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);
/*DESCRIPTION: The memcpy() function copies n bytes from memory area src to
memory area dest. The memory areas must not overlap. Use memmove(3) if the
memory areas do overlap.
RETURN VALUE: The memcpy() function returns a pointer to dest.*/
void				*ft_memcpy(void *dest, const void *src, size_t n);
/*DESCRIPTION: The memmove() function  copies n bytes from memory area src to
memory area dest. The memory areas may overlap: copying takes place as though
the bytes in src are first copied into a temporary array that does not overlap
src or dest, and the bytes are then copied from the temporary array to dest.
RETURN VALUE: The memmove() function returns a pointer to dest.*/
void				*ft_memmove(void *dest, const void *src, size_t n);
/*DESCRIPTION: The memset() function fills the first n bytes of the memory area
pointed to by s with the constant byte c.
RETURN VALUE: The memset() function returns a pointer to the memory area s.*/
void				*ft_memset(void *s, int c, size_t n);
//DESCRIPTION: Outputs the character ’c’ to the file descriptor.
void				ft_putchar_fd(char c, int fd);
//DESCRIPTION: Outputs the string 's' and a newline to the file descriptor.
void				ft_putendl_fd(char *s, int fd);
//DESCRIPTION: Outputs the integer ’n’ to the file descriptor.
void				ft_putnbr_fd(int n, int fd);
//DESCRIPTION: Outputs the string 's' to the file descriptor.
void				ft_putstr_fd(char *s, int fd);
/*DESCRIPTION: Allocates (with malloc(3)) and returns an array of strings
obtained by splitting ’s’ using the character ’c’ as a delimiter.
The array must end with a NULL pointer.
RETURN VALUE: The array of new strings resulting from the split. NULL if the
allocation fails.*/
char				**ft_split(const char *s, char c);
/*DESCRIPTION: The strchr function returns a pointer to the first occurrence of
the character c in the string s.
RETURN VALUE: Returns a pointer to the matched character or NULL if the
character is not found. The terminating null byte is considered part of the
string, so that if c is specified as '\0', these functions return a pointer to
the terminator.*/
char				*ft_strchr(const char *s, int c);
/*DESCRIPTION: The strdup function returns a pointer to a new string which is a
duplicate of the string s. Memory for the new string is obtained with malloc(3),
and can be freed with free(3).
RETURN VALUE: On success, the strdup function returns a pointer to the
duplicated string. It returns NULL if insufficient memory was available.*/
char				*ft_strdup(char *src);
/*DESCRIPTION: Applies the function ’f’ on each character of the string passed
as argument, passing its index as first argument. Each character is passed by
address to ’f’ to be modified if necessary.*/
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
/*DESCRIPTION: Allocates (with malloc) and returns a new string, which is the
result of the concatenation of ’s1’ and ’s2’.
RETURN VALUE: The new string. NULL if the allocation fails.*/
char				*ft_strjoin(char const *s1, char const *s2);
/*DESCRIPTION: The strlcpy() and strlcat() functions copy and concatenate
strings respectively. Strlcpy() and strlcat() take the full size of the buffer
(not just the length) and guarantee to NUL-terminate the result (as long as
size is larger than 0 or, in the case of strlcat(), as long as there is at
least one byte free in dst).  Note that a byte for the NUL should be included
in size.
Also note that strlcpy() and strlcat() only operate on true “C” strings. This
means that for strlcpy() src must be NUL-terminated and for strlcat() both src
and dst must be NUL-terminated.
The strlcat() function appends the NUL-terminated string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result
RETURN VALUES: The strlcpy() and strlcat() functions return the total length of
the string they tried to create. For strlcat() that means the initial length of
dst plus the length of src. While this may seem somewhat confusing, it was done
to make truncation detection simple.
Note, however, that if strlcat() traverses size characters without finding a
NUL, the length of the string is considered to be size and the destination
string will not be NUL-terminated (since there was no space for the NUL).  This
keeps strlcat() from running off the end of a string. In practice this should
not happen (as it means that either size is incorrect or that dst is not a
proper “C” string).  The check exists to prevent potential security problems in
incorrect code.*/
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
//DESCRIPTION: Returns the length of the string excluding the NUL-Terminator.
size_t				ft_strlen(const char *str);
/*DESCRIPTION: Applies the function ’f’ to each character of the string ’s’,
and passing its index as first argument to create a new string (with malloc(3))
resulting from successive applications of ’f’.
RETURN VALUE: The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*DESCRIPTION: The strncmp function compares only the first (at most) n bytes
of s1 and s2.
RETURN VALUES: 0 if the s1 and s2 are equal, a negative value if s1 is less
than s2, or a positive value if s1 is greater than s2.*/
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
/*DESCRIPTION: The strnstr() function locates the first occurrence of the null-
terminated string little in the string big, where not more than len characters
are searched.  Characters that appear after a ‘\0’ character are not searched.
RETURN VALUES: If little is an empty string, big is returned; if little occurs
nowhere in big, NULL is returned; otherwise a pointer to the first character of
the first occurrence of little is returned.*/
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
/*DESCRIPTION: The strrchr() function returns a pointer to the last occurrence
of the character c in the string s.
RETURN VALUE: The strrchr() function returns a pointer to the matched character
or NULL if the character is not found. The terminating null byte is considered
part of the string, so that if c is specified as '\0', these functions return a
pointer to the terminator.*/
char				*ft_strrchr(const char *s, int c);
/*DESCRIPTION: Allocates (with malloc(3)) and returns a copy of ’s1’ with the
characters specified in ’set’ removed from the beginning and the end of the
string.
RETURN VALUES: The trimmed string. NULL if the allocation fails.*/
char				*ft_strtrim(char const *s1, char const *set);
/*DESCRIPTION: Allocates (with malloc(3)) and returns a substring from the
string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.
RETURN VALUE: The substring. NULL if the allocation fails.*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
/*DESCRIPTION: If c is an uppercase letter, tolower() returns its lowercase 
equivalent, if a lowercase representation exists in the current locale.
Otherwise, it returns c. If c is neither an unsigned char value nor EOF, the
behavior of these functions is undefined.
RETURN VALUES: The value returned is that of the converted letter, or c if the
conversion was not possible.*/
int					ft_tolower(int c);
/*DESCRIPTION: If c is a lowercase letter, toupper() returns its uppercase
equivalent, if an uppercase representation exists in the current locale.
Otherwise, it returns c. If  c  is neither an unsigned char value nor EOF, the
behavior of these functions is undefined.
RETURN VALUES: The value returned is that of the converted letter, or c if the
conversion was not possible.*/
int					ft_toupper(int c);
/*DESCRIPTION: Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with the value of the parameter
’content’. The variable ’next’ is initialized to NULL.
RETURN VALUE: The new node.*/
t_lst				*ft_lstnew(void *content);
//DESCRIPTION: Adds the node ’new’ at the beginning of the list.
void				ft_lstadd_front(t_lst **lst, t_lst *new);
/*DESCRIPTION: Counts the number of nodes in a list.
RETURN VALUE: The length of the list*/
int					ft_lstsize(t_lst *lst);
/*DESCRIPTION: Returns the last node of the list.
RETURN VALUE: Last node of the list*/
t_lst				*ft_lstlast(t_lst *lst);
//DESCRIPTION: Adds the node ’new’ at the end of the list.
void				ft_lstadd_back(t_lst **lst, t_lst *new);
/*DESCRIPTION: Takes as a parameter a node and frees the memory of the node’s
content using the function ’del’ given as a parameter and free the node. The
memory of ’next’ must not be freed.*/
void				ft_lstdelone(t_lst *lst, void (*del)(void*));
/*DESCRIPTION: Deletes and frees the given node and everysuccessor of that node,
using the function ’del’ and free(3). Finally, the pointer to the list must be
set to NULL.*/
void				ft_lstclear(t_lst **lst, void (*del)(void*));
/*DESCRIPTION: Iterates the list ’lst’ and applies the function ’f’ on the
content of each node.*/
void				ft_lstiter(t_lst *lst, void (*f)(void *));
/*DESCRIPTION: Iterates the list ’lst’ and applies the function ’f’ on the
content of each node. Creates a new list resulting of the successive
applications of the function ’f’. The ’del’ function is used to delete the
content of a node if needed.
RETURN VALUE: The new list. NULL if the allocation fails.*/
t_lst				*ft_lstmap(t_lst *lst, void *(*f)(void *),
						void (*del)(void *));
//Same as strjoin, but frees s1 before returning.
char				*ft_strjoin_free(char const *s1, char const *s2);
//Same as strtrim, but frees s1 before returning.
char				*ft_strtrim_free(const char *s1, const char *set);
//Frees the array and it's char*s. Does nothing if the pointer is NULL.
void				liberate_strarray(char **sta);
//Gets the next line from the indicated file descriptor. Returns NULL on error.
char				*get_next_line(int fd);
int					ft_printf(const char *s, ...);
char				*ft_utoa(unsigned long n);
void				add_char(int *length, char c);
void				all_your_base(int *length, long long nbr, int flag,
						int base);
void				hexhex(int *length, long long nbr, int flag, int base);
void				string_along(int *length, const char *src);
void				toa(int *length, int nbr, int flag);
#endif
