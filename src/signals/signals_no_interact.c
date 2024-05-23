/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_no_interact.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:35:31 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/28 19:39:25 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sigquit_handler_no_interact(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_on_new_line();
}

void	ms_ctrl_backslash_ignore_no_interact(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &ms_sigquit_handler_no_interact;
	sigaction(SIGQUIT, &action, NULL);
}

void	ms_ctrl_c_newline_no_interact(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
	rl_on_new_line();
}

void	ms_listening_no_interact_sig(void)
{
	struct sigaction	action;

	ms_ctrl_backslash_ignore_no_interact();
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &ms_ctrl_c_newline_no_interact;
	sigaction(SIGINT, &action, NULL);
}
