/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:02:05 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/02 15:02:06 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	env(char **env_a)
{
	int	i;

	i = 0;
	if (!env_a)
		return (1);
	while (env_a[i])
	{
		if (check_sign(env_a[i]))
			ft_putendl_fd(env_a[i], 1);
		i++;
	}
	return (0);
}
