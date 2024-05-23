/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:29:52 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/07 22:58:30 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_del_one_node_cmd(t_command *lst, void (*del)(void *))
{
	if (lst->command)
		(*del)(lst->command);
	if (lst->args)
		ms_ptr_free_arr(lst->args);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->fds)
		ms_io_free(lst->fds);
	(*del)(lst);
}

void	ms_del_all_nodes_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ms_del_one_node_cmd(*lst, del);
		*lst = temp;
	}
}
