/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:39:46 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/10 14:39:48 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*parse_env2(char *env, int i, int j)
{
	char	*new_env;

	new_env = malloc(ft_strlen(env) + 1);
	if (!new_env)
		return (free(env), NULL);
	while (env[i])
	{
		if (env[i] == '|')
			new_env[j++] = 25;
		else if (env[i] == '>')
			new_env[j++] = 23;
		else if (env[i] == '<')
			new_env[j++] = 22;
		else if (env[i] == '\'')
			new_env[j++] = 17;
		else if (env[i] == '"')
			new_env[j++] = 18;
		else
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = 0;
	return (free(env), new_env);
}

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
	else if ((env[i] == '\'' && closed_quotes(env, 1))
		|| (env[i] == '"' && closed_quotes(env, 2)))
		return (free(env), NULL);
	while (env[i] && env_pattern(env[i], i + 1))
		i++;
	env[i] = 0;
	env_value = get_env_value(data->envp, env);
	if (!env_value)
		return (free(env), NULL);
	free(env);
	env = ft_strdup(env_value);
	protecc(!env, data, 1);
	env = parse_env2(env, 0, 0);
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

char	*insert_env(char *s, t_msd *data, int i)
{
	char	*env;
	char	*new_s;

	while (s[i] && s[i] != '$')
		i++;
	env = ft_strdup(s + i + 1);
	if (!env)
		return (free(s), NULL);
	env = parse_env(data, env, 0);
	if ((ft_strlen(s) + ft_strlen(env)) > 10000000)
	{
		ft_putendl_fd("🧙: You shell not allocate! Exiting", 2);
		free(env);
		protecc(1, data, 2);
	}
	new_s = malloc(ft_strlen(s) + ft_strlen(env) + 1);
	if (!new_s)
		return (free(s), free(env), NULL);
	i = 0;
	insert_env2(s, new_s, env, i);
	return (free(s), free(env), new_s);
}
