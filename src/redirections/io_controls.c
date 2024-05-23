/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:25:54 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/22 19:25:54 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_reset_io(t_fds *io)
{
	int	res;

	res = true;
	if (!io)
		return (res);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			res = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			res = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (res);
}

bool	ms_config_io(t_fds *io)
{
	int	res;

	res = true;
	if (!io)
		return (res);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		res = ms_msg_err("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		res = ms_msg_err("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			res = ms_msg_err("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			res = ms_msg_err("dup2", io->outfile, \
			strerror(errno), false);
	return (res);
}

bool	ms_check_io(t_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}
