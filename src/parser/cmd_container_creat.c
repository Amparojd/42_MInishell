/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_container_creat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:27:20 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/23 11:27:20 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ms_new_cmd_lst(void)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->command = NULL;
	new_node->path = NULL;
	new_node->args = NULL;
	new_node->pipe_output = false;
	new_node->pipe_fd = 0;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ms_addlst_cmd_container(t_mshl *ms, t_command **cmd_list)
{
	t_command	*new_node;
	t_command	*aux;

	new_node = ms_new_cmd_lst();
	if (!new_node)
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	aux = *cmd_list;
	if (!aux)
	{
		*cmd_list = new_node;
		return ;
	}
	if (new_node)
	{
		ms_scroll_lstcmd(aux);
		aux->next = new_node;
		new_node->prev = aux;
	}
}
