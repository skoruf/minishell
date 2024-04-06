/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:45:28 by cthaler           #+#    #+#             */
/*   Updated: 2024/02/21 08:45:32 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_bigger(char *env_a, char *env_b)
{
	int	i;

	i = 0;
	while (env_a[i] && env_b[i])
	{
		if (env_a[i] == '=' && env_b[i] == '=')
			return (0);
		else if (env_a[i] == '=' && env_b[i] != '=')
			return (-1);
		else if (env_a[i] != '=' && env_b[i] == '=')
			return (1);
		else if (env_a[i] < env_b[i])
			return (-1);
		else if (env_a[i] > env_b[i])
			return (1);
		i++;
	}
	return (0);
}

static void	sort_env2(char **env, char **env_sorted, int i, int j)
{
	int	index;

	while (env[i])
	{
		j = 0;
		index = 0;
		while (env[j])
		{
			if (is_bigger(env[i], env[j]) == 1)
				index++;
			j++;
		}
		env_sorted[index] = env[i];
		i++;
	}
}

char	**sort_env(char **env)
{
	char	**env_sorted;
	int		i;
	int		len;

	i = 0;
	len = arr_len(env) + 1;
	env_sorted = malloc(sizeof(env_sorted) * len);
	if (!env_sorted)
		return (NULL);
	while (i < len)
		env_sorted[i++] = 0;
	i = 0;
	sort_env2(env, env_sorted, i, 0);
	return (env_sorted);
}
