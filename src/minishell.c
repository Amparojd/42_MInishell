/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:37:53 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/11 19:21:13 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_main_loop(t_mshl *ms)
{
	while (1)
	{
		ms_listening_interact_sig();
		ms->line = readline(PROMPT);
		ms_listening_no_interact_sig();
		if (ms_lexer_main(ms))
			g_status = ms_execute_main(ms);
		ms_data_free(ms, false);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mshl	ms;

	(void) argv;
	if (argc != 1)
		ms_exit_msg(NULL, ERR_ARG, EXIT_FAILURE);
	if (!ms_set_main_struct(&ms, env))
		ms_exit_ms(NULL, EXIT_FAILURE);
	ms_main_loop(&ms);
	return (0);
}
