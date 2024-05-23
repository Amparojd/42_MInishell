/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:51:52 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/08 17:45:33 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_directory(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	ms_check_cmd_validity(t_mshl *ms, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& ms_search_env_index(ms->env, "PATH") != -1)
		return (ms_msg_err(cmd->command, NULL, "command not found",
				CMD_UNKNOWN));
	if (access(cmd->command, F_OK) != 0)
		return (ms_msg_err(cmd->command, NULL, strerror(errno), \
		CMD_UNKNOWN));
	else if (ms_is_directory(cmd->command))
		return (ms_msg_err(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (ms_msg_err(cmd->command, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
