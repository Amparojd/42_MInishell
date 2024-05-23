/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:39:01 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/24 17:41:34 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_data_free(t_mshl *ms, bool clearhistory)
{
	if (ms && ms->line)
	{
		ms_ptr_free(ms->line);
		ms->line = NULL;
	}
	if (ms && ms->token)
		ms_del_all_nodes_tkn(&ms->token, &ms_ptr_free);
	if (ms && ms->cmd)
		ms_del_all_nodes_cmd(&ms->cmd, &ms_ptr_free);
	if (clearhistory == true)
	{
		if (ms && ms->pwd)
			ms_ptr_free(ms->pwd);
		if (ms && ms->old_pwd)
			ms_ptr_free(ms->old_pwd);
		if (ms && ms->env)
			ms_ptr_free_arr(ms->env);
		clear_history();
	}
}

void	ms_close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->fds)
	{
		if (cmds->fds->fd_in != -1)
			close(cmds->fds->fd_in);
		if (cmds->fds->fd_out != -1)
			close(cmds->fds->fd_out);
		if (close_backups)
			ms_reset_io(cmds->fds);
	}
	ms_close_un_pipes_fd(cmds, NULL);
}

void	ms_io_free(t_fds *io)
{
	if (!io)
		return ;
	ms_reset_io(io);
	if (io->heredoc_del)
	{
		unlink(io->infile);
		ms_ptr_free(io->heredoc_del);
	}
	if (io->infile)
		ms_ptr_free(io->infile);
	if (io->outfile)
		ms_ptr_free(io->outfile);
	if (io)
		ms_ptr_free(io);
}

void	ms_ptr_free_arr(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				ms_ptr_free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	ms_ptr_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
