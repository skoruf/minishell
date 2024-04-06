/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:43:33 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/21 11:43:35 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_str(char *s1, char *s2, int flag)
{
	int	len;

	len = ft_strlen(s2);
	if (flag == 1)
		len++;
	return (ft_strncmp(s1, s2, len));
}

int	is_builtin(char *s)
{
	if (!is_str(s, "echo", 1)
		|| !is_str(s, "cd", 1)
		|| !is_str(s, "pwd", 1)
		|| !is_str(s, "export", 1)
		|| !is_str(s, "unset", 1)
		|| !is_str(s, "env", 1)
		|| !is_str(s, "exit", 1))
		return (1);
	return (0);
}

int	token_type(char *s, int last)
{
	if (!is_str(s, "|", 0))
		return (PIPE);
	else if (!is_str(s, "<<", 0))
		return (HEREDOC);
	else if (!is_str(s, "<", 0))
		return (IN);
	else if (!is_str(s, ">>", 0))
		return (APPEND);
	else if (!is_str(s, ">", 0))
		return (OUT);
	else if (last == IN || last == HEREDOC
		|| last == OUT || last == APPEND)
		return (FILE);
	else if (last != ARG && last != FILE && last != CMD && last != CMD2)
	{
		if (is_builtin(s))
			return (CMD);
		else
			return (CMD2);
	}
	return (ARG);
}

static void	rework_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 25)
			s[i] = '|';
		else if (s[i] == 23)
			s[i] = '>';
		else if (s[i] == 22)
			s[i] = '<';
		else if (s[i] == 17)
			s[i] = '\'';
		else if (s[i] == 18)
			s[i] = '"';
		i++;
	}
}

int	tokenize(t_list **args)
{
	int		last_token;
	t_list	*cur;

	last_token = 0;
	cur = *args;
	while (cur)
	{
		cur->token = token_type(cur->s, last_token);
		if (last_token != HEREDOC)
			cur->s = remove_quotes(cur->s);
		if (!cur->s)
			return (0);
		if (cur->token == CMD2)
			cur->token = token_type(cur->s, last_token);
		last_token = cur->token;
		rework_str(cur->s);
		cur = cur->next;
	}
	return (1);
}
