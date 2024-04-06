/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:44:03 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/12 12:44:05 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(char **env)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	while (env[i])
	{
		j = 0;
		quotes = 0;
		if (ft_strncmp(env[i], "_=", 2))
		{
			ft_putstr_fd("declare -x ", 1);
			while (env[i][j])
			{
				ft_putchar_fd(env[i][j], 1);
				if (env[i][j] == '=' && ++quotes)
					ft_putchar_fd('"', 1);
				j++;
			}
			if (quotes)
				ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}

int	is_in_env(char **env, char *arg)
{
	int		i;
	int		len;
	char	*arg2;

	i = 0;
	arg2 = ft_strdup(arg);
	if (!arg2)
		return (-2);
	while (arg2[i] && arg2[i] != '=')
		i++;
	arg2[i] = 0;
	len = ft_strlen(arg2);
	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], arg2, len))
			&& env[i][len] == '=')
			return (free(arg2), i);
		i++;
	}
	return (free(arg2), -1);
}
