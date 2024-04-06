/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:18:31 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/12 12:18:34 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*parse_env(t_msd *data, char *env, int i)
{
	char	*env_value;

	if (env[i] == '?')
	{
		free(env);
		env = ft_itoa(data->exit_code);
		protecc(!env, data, 1);
		return (env);
	}
	while (env[i] && env_pattern(env[i], i))
		i++;
	env[i] = 0;
	env_value = get_env_value(data->envp, env);
	if (!env_value)
		return (free(env), NULL);
	free(env);
	env = ft_strdup(env_value);
	protecc(!env, data, 1);
	return (env);
}

static void	insert_env2(char *s, char *new_s, char *env, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i] && s[i] != '$')
		new_s[j++] = s[i++];
	if (s[i + 1] == '?')
		i += 2;
	else
	{
		i++;
		if (!env_pattern(s[i], 0))
			;
		else
			while (env_pattern(s[i], i))
				i++;
	}
	while (env && env[k])
		new_s[j++] = env[k++];
	while (s[i])
		new_s[j++] = s[i++];
	new_s[j] = 0;
}

char	*env_heredoc(char *s, t_msd *data, int i)
{
	char	*env;
	char	*new_s;

	while (s[i] && s[i] != '$')
		i++;
	env = ft_strdup(s + i + 1);
	if (!env)
		return (free(s), NULL);
	env = parse_env(data, env, 0);
	new_s = malloc(ft_strlen(s) + ft_strlen(env) + 1);
	if (!new_s)
		return (free(s), free(env), NULL);
	i = 0;
	insert_env2(s, new_s, env, i);
	return (free(s), free(env), new_s);
}

int	no_dollar(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '$')
			return (0);
		else if (s[i] == '\'')
			return (i);
		i++;
	}
	return (0);
}
