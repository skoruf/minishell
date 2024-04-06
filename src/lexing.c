/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:20:31 by cthaler           #+#    #+#             */
/*   Updated: 2023/12/14 15:20:32 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	closed_quotes(char *s, int flag)
{
	int	i;

	i = 0;
	if ((*s == '"' && flag == 2) || (*s == '\'' && flag == 1))
		s++;
	while (s[i])
	{
		if (s[i] == '"' && flag == 2)
			break ;
		else if (s[i] == '\'' && flag == 1)
			break ;
		i++;
	}
	if (!s[i])
		return (0);
	return (flag);
}

int	next_str(char *s, int i)
{
	int	s_quotes;
	int	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	while (s[i] && (!pattern(s[i], 1) || ((s_quotes || d_quotes)
				&& closed_quotes(s + i, d_quotes + 1))))
	{
		if (s[i] == '"' && !d_quotes && !s_quotes)
			d_quotes = 1;
		else if (s[i] == '"' && d_quotes)
			d_quotes = 0;
		else if (s[i] == '\'' && !d_quotes && !s_quotes)
			s_quotes = 1;
		else if (s[i] == '\'' && s_quotes)
			s_quotes = 0;
		i++;
	}
	return (i);
}

int	add_token(char *s, t_list **lst, int i)
{
	int		j;
	char	*temp;
	t_list	*new;

	j = 1;
	if (pattern(s[i], 1) != 2)
		return (0);
	if ((s[i] == '>' && s[i + 1] == '>')
		|| (s[i] == '<' && s[i + 1] == '<'))
		j = 2;
	s += i;
	temp = ft_strdup(s);
	if (!temp)
		return (-1);
	temp[j] = 0;
	new = ft_strlstnew(temp);
	if (!new)
		return (free(temp), 0);
	ft_strlst_back(lst, new);
	return (j);
}

static int	lex_it2(char *s, t_msd *data, int check, int i)
{
	int	j;

	while (s[i])
	{
		j = 0;
		while (pattern(*s, 0))
			s++;
		if (!*s)
			return (1);
		i = next_str(s, i);
		if (!s[i])
			check = 0;
		if (!add_str(data, s, i))
			return (0);
		j = add_token(s, &data->arg_list, i);
		if (j == -1)
			return (0);
		if (check)
		{
			s += i + j;
			i = 0;
		}
	}
	return (1);
}

int	lex_it(char *s, t_msd *data, int check)
{
	return (lex_it2(s, data, check, 0));
}
