/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:45:18 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/27 11:45:21 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*new_str(char *s)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	s2 = malloc(ft_strlen(s) - 1);
	if (!s2)
		return (NULL);
	while (s[i])
	{
		if (s[i] != 31)
			s2[j++] = s[i];
		i++;
	}
	s2[j] = 0;
	return (s2);
}

char	check_quotes(char *s, int i, char first)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !first)
			first = s[i];
		if (s[i] == '\'')
			s_quote++;
		else if (s[i] == '"')
			d_quote++;
		i++;
	}
	if ((first == '\'' && s_quote > 1) || (first == '"' && d_quote > 1))
		return (first);
	else if (first == '\'' && d_quote > 1)
		return ('"');
	else if (first == '"' && s_quote > 1)
		return ('\'');
	else
		return (0);
}

static void	remove_quotes2(char *s, int quoted, char q, int i)
{
	while (s[i])
	{
		if (quoted == 0 && s[i] == q)
		{
			quoted = 1;
			s[i] = 31;
		}
		else if (s[i] == q)
		{
			quoted = 0;
			s[i] = 31;
			q = check_quotes(s + i, 0, 0);
			if (!q)
				break ;
		}
		i++;
	}
}

char	*remove_quotes(char *s)
{
	char	*s2;
	int		i;
	char	q;
	int		quoted;

	i = 0;
	quoted = 0;
	q = check_quotes(s, 0, 0);
	if (!q)
		return (s);
	remove_quotes2(s, quoted, q, i);
	s2 = new_str(s);
	if (!s2)
		return (free(s), NULL);
	return (free(s), s2);
}
