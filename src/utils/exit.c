/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:27:26 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/24 18:27:26 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_ms(t_mshl *ms, int exit_code)
{
	if (ms)
	{
		if (ms->cmd && ms->cmd->fds)
			ms_close_fds(ms->cmd, true);
		ms_data_free(ms, true);
	}
	exit(exit_code);
}
