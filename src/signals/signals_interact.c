/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interact.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:56:56 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/28 17:41:19 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_ctrl_backslash_ignore(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	ms_ctrl_c_newline_hdoc(int signal)
{
	if (signal != SIGINT)
		return ;
	g_status = 130;
	ft_putstr_fd("\1\n", STDIN_FILENO);
}

void	ms_listening_hdoc_input_sig(void)
{
	struct sigaction	action;

	ms_ctrl_backslash_ignore();
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &ms_ctrl_c_newline_hdoc;
	sigaction(SIGINT, &action, NULL);
}

void	ms_ctrl_c_newline(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void	ms_listening_interact_sig(void)
{
	struct sigaction	action;

	ms_ctrl_backslash_ignore();
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &ms_ctrl_c_newline;
	sigaction(SIGINT, &action, NULL);
}
