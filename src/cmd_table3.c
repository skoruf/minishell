/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <cthaler@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:07:42 by cthaler           #+#    #+#             */
/*   Updated: 2024/03/16 14:07:43 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	alloc_redir_head(t_msd *data)
{
	int	size;

	size = count_redirs(data->arg_list, 0);
	if (!size)
		return (1);
	data->redir_head = malloc(sizeof(data->redir_head) * (size + 1));
	if (!data->redir_head)
		return (0);
	data->redir_head[size] = NULL;
	return (1);
}
