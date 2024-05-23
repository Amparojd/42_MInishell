/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:02:37 by ampjimen          #+#    #+#             */
/*   Updated: 2024/05/02 10:58:51 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_close_un_pipes_fd(t_command *cmds, t_command *omit_cmd)
{
	while (cmds)
	{
		if (cmds != omit_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	ms_create_pipes(t_mshl *ms)
{
	int			*fd;
	t_command	*aux;

	aux = ms->cmd;
	while (aux)
	{
		if (aux->pipe_output || (aux->prev && aux->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				ms_data_free(ms, false);
				return (false);
			}
			aux->pipe_fd = fd;
		}
		aux = aux->next;
	}
	return (true);
}

bool	ms_config_pipes_fd(t_command *cmds, t_command *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	ms_close_un_pipes_fd(cmds, c);
	return (true);
}
