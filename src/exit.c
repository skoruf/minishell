/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:26:32 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/06 15:26:35 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_numeric_str(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

static int	check_overflow(char *s, t_msd *data)
{
	int			i;
	int			j;
	long long	nr;
	char		*s2;

	i = 0;
	j = 0;
	nr = ft_atoll(s);
	if (s[0] == '+' || (s[0] && s[0] == '-' && s[1] == '0'))
		i++;
	else if (nr < 0)
		j++;
	s2 = ft_lltoa(nr);
	protecc(!s2, data, 1);
	if (strncmp(s + i + j, s2 + j, ft_strlen(s + i + j)))
		return (free(s2), 1);
	return (free(s2), 0);
}

void	ft_exit(t_msd *data, char **bin)
{
	unsigned char	i;

	i = 0;
	if (!bin)
		ft_putendl_fd("exit", 2);
	if (!bin)
		protecc(1, data, data->exit_code);
	if (bin[1] && (!is_numeric_str(bin[1]) || check_overflow(bin[1], data)))
	{
		ft_putendl_fd("🧙: exit: numeric argument required", 2);
		data->exit_code = 2;
	}
	else if (bin[1] && bin[2])
	{
		ft_putendl_fd("🧙: exit: too many arguments", 2);
		data->exit_code = 1;
		return ;
	}
	else if (bin[0] && bin[1])
	{
		i = ft_atoll(bin[1]);
		data->exit_code = (int)i;
	}
	ft_putendl_fd("exit", 2);
	data->quit = 1;
}
