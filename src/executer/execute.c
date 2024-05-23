/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:51:59 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/05 18:17:47 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	ms_child_status(t_mshl *ms)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	ms_close_fds(ms->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == ms->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	ms_create_children(t_mshl *ms)
{
	t_command	*cmd;

	cmd = ms->cmd;
	while (ms->pid != 0 && cmd)
	{
		ms->pid = fork();
		if (ms->pid == -1)
			return (ms_msg_err("fork", NULL, strerror(errno), \
			EXIT_FAILURE));
		else if (ms->pid == 0)
			ms_command_exec(ms, cmd);
		cmd = cmd->next;
	}
	return (ms_child_status(ms));
}

int	ms_prep_command(t_mshl *ms)
{
	if (!ms || !ms->cmd || !ms->cmd->command
		|| (ms->cmd->command[0] == '\0' && ms->token->has_quotes == false))
		return (EXIT_SUCCESS);
	if (ms->cmd && !ms->cmd->command)
	{
		if (ms->cmd->fds
			&& !ms_check_io(ms->cmd->fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!ms_create_pipes(ms))
		return (EXIT_FAILURE);
	return (CMD_UNKNOWN);
}

int	ms_execute_main(t_mshl *ms)
{
	int	res;

	res = ms_prep_command(ms);
	if (res != CMD_UNKNOWN)
		return (res);
	if (!ms->cmd->pipe_output && !ms->cmd->prev
		&& ms_check_io(ms->cmd->fds))
	{
		ms_config_io(ms->cmd->fds);
		res = ms_exec_builtin_cmd(ms, ms->cmd);
		ms_reset_io(ms->cmd->fds);
	}
	if (res != CMD_UNKNOWN)
		return (res);
	return (ms_create_children(ms));
}
