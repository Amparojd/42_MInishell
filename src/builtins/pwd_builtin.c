/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:24 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/18 19:03:41 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_pwd_builtin(t_mshl *ms, char **args)
{
	char	buffer[PATH_MAX];
	char	*working_dir;

	(void)args;
	if (ms->pwd)
	{
		ft_putendl_fd(ms->pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	working_dir = getcwd(buffer, PATH_MAX);
	if (working_dir)
	{
		ft_putendl_fd(working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ms_msg_err("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
