/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:47:41 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/10 14:47:42 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	remove_dollars(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\'')
	{
		if (s[i] == '$')
			s[i] = 30;
		i++;
	}
	if (s[i])
		i++;
	return (i);
}

static int	check_double_quotes(char *s)
{
	int	i;
	int	d_quote;

	i = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '"')
			d_quote++;
		else if (s[i] == '\'' && !d_quote)
			return (0);
		if (d_quote == 2)
			return (i + 1);
		i++;
	}
	return (0);
}

static void	in_squotes(char *s, int i, int q)
{
	while (s[i])
	{
		if (check_double_quotes(s + i))
		{
			i += check_double_quotes(s + i);
			continue ;
		}
		while (s[i] && s[i] != '\'' && s[i] != '$')
			i++;
		if (s[i] == '\'')
		{
			while (q)
			{
				q = no_dollar(s + i);
				i += q;
			}
		}
		if (s[i] == '\'' && closed_quotes(s + i, 1))
			i += remove_dollars(s + i + 1) + 1;
		while (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
		if (s[i] && (!closed_quotes(s + i, 1)
				|| !closed_quotes(s + i, 2)))
			i++;
	}
}

static int	has_env(char *s)
{
	int	i;

	i = 0;
	in_squotes(s, 0, 1);
	while (s[i])
	{
		if (s[i] == '$' && i > 0 && s[i - 1] == '"' && s[i + 1] == '"')
			s[i] = 30;
		else if ((s[i] == '$' && (s[i + 1] == '\''
					&& closed_quotes(s + 1, 1)))
			|| (s[i] == '$' && (s[i + 1] == '"'
					&& closed_quotes(s + 1, 2))))
			return (1);
		else if (s[i] == '$' && s[i + 1] != '?'
			&& !env_pattern(s[i + 1], 0))
			s[i] = 30;
		else if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	parse_hell(t_msd *data)
{
	int	i;

	i = 0;
	if (g_sig == SIGINT)
		data->exit_code = 130;
	if (g_sig == SIGINT)
		g_sig = DEFAULT;
	data->line_history = ft_strdup(data->line);
	protecc(!data->line_history, data, 1);
	while (data->line)
	{
		if (!has_env(data->line))
			break ;
		data->line = insert_env(data->line, data, 0);
	}
	if (!data->line)
		return (0);
	while (data->line[i])
	{
		if (data->line[i] == 30)
			data->line[i] = '$';
		i++;
	}
	return (1);
}
