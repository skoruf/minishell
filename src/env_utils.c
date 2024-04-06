/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:47:12 by cthaler           #+#    #+#             */
/*   Updated: 2024/02/09 15:42:31 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env(char **env_a, char *key)
{
	int	i;

	i = 0;
	while (env_a[i])
	{
		if (ft_strncmp(env_a[i], key, ft_strlen(key)) == 0
			&& env_a[i][ft_strlen(key)] == '=')
			return (env_a[i]);
		i++;
	}
	return (NULL);
}

int	set_env_value(char **env_a, char *key, char *value)
{
	int		i;
	char	*key2;

	i = 0;
	while (env_a[i])
	{
		if (ft_strncmp(env_a[i], key, ft_strlen(key)) == 0
			&& env_a[i][ft_strlen(key)] == '=')
		{
			free(env_a[i]);
			key2 = ft_strjoin(key, "=");
			env_a[i] = ft_strjoin_free(key2, value);
			if (!env_a[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_env(char **env_a, char *key, char *s)
{
	int	i;

	i = 0;
	while (env_a[i])
	{
		if (ft_strncmp(env_a[i], key, ft_strlen(key)) == 0
			&& (env_a[i][ft_strlen(key)] == '='
			|| !env_a[i][ft_strlen(key)]))
			return (free(env_a[i]), env_a[i] = s, 1);
		i++;
	}
	return (0);
}

int	env_pattern(char c, int i)
{
	if (c == '_' || (c >= '0' && c <= '9' && i != 1)
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*get_env_value(char **env_a, char *s)
{
	char	*ret;

	ret = get_env(env_a, s);
	if (!ret)
		return (NULL);
	while (*ret != '=')
		ret++;
	ret++;
	return (ret);
}
