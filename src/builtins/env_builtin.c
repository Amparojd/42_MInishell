/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:00 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/03 19:48:45 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_env_builtin(t_mshl *ms, char **args)
{
	int	i;

	if (args && args[1])
		return (ms_msg_err("env", NULL, ERR_CD_ARG, 2));
	i = 0;
	if (!ms->env)
		return (EXIT_FAILURE);
	while (ms->env[i])
		ft_putendl_fd(ms->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
