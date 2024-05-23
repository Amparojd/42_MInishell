/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_command_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:51:43 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/04 18:58:13 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_builtin_cmd(t_mshl *ms, t_command *cmd)
{
	int	cmd_result;

	cmd_result = CMD_UNKNOWN;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		cmd_result = ms_exec_cd_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		cmd_result = ms_exec_echo_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		cmd_result = ms_exec_env_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		cmd_result = ms_exec_export_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		cmd_result = ms_exec_pwd_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		cmd_result = ms_exec_unset_builtin(ms, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		cmd_result = ms_exec_exit_builtin(ms, cmd->args);
	return (cmd_result);
}

int	ms_exec_sys_binary(t_mshl *ms, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_UNKNOWN);
	if (ms_is_directory(cmd->command))
		return (CMD_UNKNOWN);
	cmd->path = ms_get_cmd_path(ms, cmd->command);
	if (!cmd->path)
		return (CMD_UNKNOWN);
	if (execve(cmd->path, cmd->args, ms->env) == -1)
		ms_msg_err("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

int	ms_exec_local_binary(t_mshl *ms, t_command *cmd)
{
	int	res;

	res = ms_check_cmd_validity(ms, cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->command, cmd->args, ms->env) == -1)
		return (ms_msg_err("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

int	ms_command_exec(t_mshl *ms, t_command *cmd)
{
	int	res;

	if (!ms_check_io(cmd->fds))
		ms_exit_ms(ms, EXIT_FAILURE);
	ms_config_pipes_fd(ms->cmd, cmd);
	ms_config_io(cmd->fds);
	ms_close_fds(ms->cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		res = ms_exec_builtin_cmd(ms, cmd);
		if (res != CMD_UNKNOWN)
			ms_exit_ms(ms, res);
		res = ms_exec_sys_binary(ms, cmd);
		if (res != CMD_UNKNOWN)
			ms_exit_ms(ms, res);
	}
	res = ms_exec_local_binary(ms, cmd);
	ms_exit_ms(ms, res);
	return (res);
}
