/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:37:02 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/23 12:37:03 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//MAX: 9223372036854775807
static int	count_len(long long nr)
{
	int	i;

	i = 1;
	if (nr < 0 && nr <= -10)
	{
		i ++;
		nr /= 10;
	}
	if (nr < 0)
		i++;
	if (nr < 0)
		nr *= -1;
	while (nr >= 10)
	{
		nr /= 10;
		i++;
	}
	return (i);
}

static char	*ft_ltoa(long long n)
{
	char	*res;
	int		pos;

	pos = count_len(n);
	res = malloc(sizeof(*res) * (pos + 1));
	if (!res)
		return (NULL);
	res[pos] = '\0';
	while (pos-- != 0)
	{
		res[pos] = (n % 10) + 48;
		n /= 10;
	}
	return (res);
}

char	*ft_lltoa(long long nr)
{
	char	*res;
	char	*res_neg;
	int		negative;

	if (nr == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	negative = 0;
	if (nr < 0)
	{
		negative = 1;
		nr *= -1;
	}
	res = ft_ltoa(nr);
	if (!res)
		return (NULL);
	if (!negative)
		return (res);
	res_neg = ft_strjoin("-", res);
	if (!res_neg)
		return (free(res), NULL);
	return (free(res), res_neg);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	nbr;
	int			negative;

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
