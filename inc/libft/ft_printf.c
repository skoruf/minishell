/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:20:01 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/09/18 14:20:02 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count(unsigned int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned long n)
{
	char	*res;
	int		pos;

	pos = count(n);
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

static void	check_format_specifier(va_list argf, int *length, char f)
{
	if (f == 'c')
		add_char(length, va_arg(argf, int));
	else if (f == 's')
		string_along(length, va_arg(argf, char *));
	else if (f == 'd' || f == 'i')
		toa(length, va_arg(argf, int), 0);
	else if (f == 'u')
		toa(length, va_arg(argf, unsigned int), 1);
	else if (f == 'x')
		hexhex(length, va_arg(argf, unsigned int), 0, 16);
	else if (f == 'X')
		hexhex(length, va_arg(argf, unsigned int), 1, 16);
	else if (f == 'p')
		hexhex(length, (unsigned long int)va_arg(argf, void *), 2, 16);
	else if (f == '%')
		add_char(length, '%');
}

int	ft_printf(const char *s, ...)
{
	va_list			argf;
	int				i;
	int				length;

	if (!s)
		return (-1);
	va_start(argf, s);
	length = 0;
	i = -1;
	while (++i < (int)ft_strlen(s))
	{
		if (s[i] != '%')
			add_char(&length, s[i]);
		else if (ft_strchr("cspdiuxX%", s[i + 1]))
			check_format_specifier(argf, &length, s[++i]);
	}
	va_end(argf);
	return (length);
}
