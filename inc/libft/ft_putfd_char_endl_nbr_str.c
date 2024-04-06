/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfd_char_endl_nbr_str.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwalchsh <der.grex@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:08:26 by gwalchsh          #+#    #+#             */
/*   Updated: 2023/10/28 13:08:27 by gwalchsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
// DESCRIPTION:  Outputs the character ’c’ to the given file descriptor.
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
//DESCRIPTION: Outputs the string 's' and a newline to the file descriptor.
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
// DESCRIPTION:  Outputs the integer ’n’ to the given file descriptor.
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + 48, fd);
}

void	ft_putstr_fd(char *s, int fd)
//DESCRIPTION: Outputs the string 's' to the file descriptor.
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			ft_putchar_fd(s[i], fd);
}
