/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alnum_alpha_ascii_digit_print.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:40 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 12:13:40 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	else
		return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isalnum(65));
	printf("%d", isalnum(65));
}*/

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1024);
	else
		return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	int i = -2147483645;
	i = 12600;
	
	while(++i < 12800)
		printf("builtin @ %d: %d\n", i, isalpha(i));
	i = 12600;
	while (++i < 2147483647)
	
	//while (--i >   -2147483646)
	
	
	{
		//printf("checking  %d\n", (i));
		if (isalpha(i) != ft_isalpha(i))
		{
			printf("fail %d\n", (i));
			break;
			}
		else
			printf("check %d\n", (i));
	}
	printf("____________\n");
	printf("orig: %d\n", isalpha(96));
	printf("ft_:  %d\n", ft_isalpha(96));
	printf("orig: %d\n", isalpha(97));
	printf("ft_:  %d\n", ft_isalpha(97));
	printf("orig: %d\n", isalpha(123));
	printf("ft_:  %d\n", ft_isalpha(123));
}*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{	
	int	i = -2147483647;
	while (++i < 2147483647)
	if (isascii (i) != ft_isascii(i))
	{
		printf("fail @ %d\n", i);
		break;
	}
	printf("%d\n", isascii(128));
	printf("%d", ft_isascii(128));
}*/

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	printf("%d\n", isdigit(2));
	printf("%d", ft_isdigit(2));
}*/

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{

	int	i = -1024;
	while (++i < 1024)//214748)
	printf("orig @ %d: %d\n", i, isprint(i));
	i = -214748;
	while (++i < 214748)
		if (isprint(i) != ft_isprint(i))
		{
			printf("fail @ %d\n", i);
			break;
		}
	printf("%d\n", isprint(50));
	printf("%d", ft_isprint(125));
}*/
