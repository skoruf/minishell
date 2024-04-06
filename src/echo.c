/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:15:24 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/04 15:15:26 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_flag(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 1;
		if (!args[i][0] || args[i][0] != '-')
			return (i);
		if (!args[i][j])
			return (i);
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j])
			return (i);
		i++;
	}
	return (i);
}

int	echo(char **args)
{
	int	i;
	int	flag;

	flag = 1;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = check_flag(args);
	if (i > 1)
		flag = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}
