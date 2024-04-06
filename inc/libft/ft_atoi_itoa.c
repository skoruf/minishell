/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:33:16 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 13:33:17 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	liberate_strarray(char **sta)
{
	int	i;

	i = -1;
	if (sta == NULL)
		return ;
	while (sta[++i])
		free(sta[i]);
	free(sta[i]);
	free(sta);
}

int	ft_atoi(const char *nptr)
/*
DESCRIPTION: The  atoi() function converts the initial portion of the string
	pointed to by nptr to int.  The behavior is the same as
	strtol(nptr, NULL, 10); except that atoi() does not detect errors.
RETURN VALUE: The converted value or 0 on error.*/
{
	int	i;
	int	nbr;
	int	negative;

	nbr = 0;
	negative = 1;
	i = 0;
	while ((nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		&& nptr[i] != '\0')
		i++;
	if (nptr[i] == '-')
	{
		negative *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		nbr *= 10;
		nbr += nptr[i++] - 48;
	}
	return (nbr * negative);
}
/*
#include <stdio.h>
int	main(void)
{
		printf("ft_ : %d\n", ft_atoi(" \t\v\n\r\f+42lyon"));
	printf("orig: %d\n", atoi(" \t\v\n\r\f+42lyon"));
		printf("ft_ : %d\n", ft_atoi(" \t\v\n\r\f101"));
	printf("orig: %d\n", atoi(" \t\v\n\r\f101"));
		printf("ft_ : %d\n", ft_atoi(" \t\v\n\r\f+-42"));
	printf("orig: %d\n", atoi(" \t\v\n\r\f+-42"));
		printf("ft_ : %d\n", ft_atoi(" \t\v\n\r\f-+42"));
	printf("orig: %d\n", atoi(" \t\v\n\r\f-+42"));
}*/

static int	count(int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*do_it_now(int n, int negative, int pos)
{
	char	*res;

	res = malloc(sizeof(*res) * (pos + 2));
	if (!res)
		return (NULL);
	res[pos + 1] = '\0';
	while (pos >= 0)
	{
		res[pos] = (n % 10) + 48;
		n = n / 10;
		pos--;
	}
	if (negative == -1)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
/*
DESCRIPTION: Allocates (with malloc(3)) and returns a string representing the
	     integer received as an argument. Negative numbers must be handled.
RETURN VALUE: The string representing the integer. NULL if the allocation
	      fails.*/
{
	int		negative;
	int		pos;
	char	*res;

	if (n == -2147483648)
	{
		res = malloc(sizeof(*res) * 12);
		if (!res)
			return (NULL);
		ft_strlcpy(res, "-2147483648", 12);
		return (res);
	}
	negative = 1;
	if (n < 0)
	{
		n *= -1;
		negative *= -1;
	}
	pos = count(n);
	if (negative == -1)
		pos++;
	return (do_it_now(n, negative, pos));
}
/*
int	main(void)
{
	char *bla = ft_itoa(-987654);
	printf("%s\n", bla);
	free(bla);
}*/
