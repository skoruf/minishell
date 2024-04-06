/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrappers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:55:38 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/22 14:55:39 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	all_your_base(int *length, long long nbr, int flag, int base)
{
	if (nbr < 0)
	{
		nbr *= -1;
		add_char(length, '-');
	}
	if (nbr < base)
	{
		if (flag == 1)
			add_char(length, BASE_BIG[nbr]);
		else
			add_char(length, BASE_SMALL[nbr]);
	}
	else
	{
		all_your_base(length, nbr / base, flag, base);
		all_your_base(length, nbr % base, flag, base);
	}
}

void	hexhex(int *length, long long nbr, int flag, int base)
{
	if (flag == 2)
	{
		if (nbr == 0)
		{
			write(1, "(nil)", 5);
			*length += 5;
		}
		else
		{
			write(1, "0x", 2);
			*length += 2;
			all_your_base(length, nbr, flag, base);
		}
	}
	else
		all_your_base(length, nbr, flag, base);
}

void	string_along(int *length, const char *src)
{
	if (!src)
	{
		write(1, "(null)", 6);
		*length += 6;
	}
	else
	{
		write(1, src, ft_strlen(src));
		*length += ft_strlen(src);
	}
}

void	toa(int *length, int nbr, int flag)
{
	char	*res;

	if (flag == 0)
	{
		res = ft_itoa(nbr);
		write(1, res, ft_strlen(res));
		*length += ft_strlen(res);
		free(res);
	}
	if (flag == 1)
	{
		res = ft_utoa((unsigned int)nbr);
		write(1, res, ft_strlen(res));
		*length += ft_strlen(res);
		free(res);
	}
}

void	add_char(int *length, char c)
{
	write(1, &c, 1);
	*length += 1;
}
