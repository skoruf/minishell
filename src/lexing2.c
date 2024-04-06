/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:02:43 by cthaler           #+#    #+#             */
/*   Updated: 2024/01/21 12:02:45 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pattern(char c, int flag)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	else if (flag == 1 && (c == '>' || c == '<' || c == '|'))
		return (2);
	return (0);
}

int	add_str(t_msd *data, char *s, int i)
{
	char	*temp;
	t_list	*new;
	t_list	**arg_list;

	arg_list = &data->arg_list;
	if (i == 0)
		return (1);
	temp = ft_strdup(s);
	if (!temp)
		return (0);
	temp[i] = 0;
	new = ft_strlstnew(temp);
	if (!new)
		return (0);
	ft_strlst_back(arg_list, new);
	return (1);
}
