/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:52:43 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/07 23:02:28 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_is_n(char *arg)
{
	int		i;
	bool	flag_n;

	flag_n = false;
	i = 0;
	if (arg[i] != '-' || (arg[i] == '-' && arg[i + 1] != 'n'))
		return (flag_n);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		flag_n = true;
	return (flag_n);
}

void	ms_print_echo(char **args, bool n_flag, int i, t_mshl *ms)
{
	char	*prep_arg;

	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		if (ms_is_var_no_quotes(ms->token, i))
		{
			prep_arg = ms_rm_extra_spaces(args[i]);
			ft_putstr_fd(prep_arg, STDOUT_FILENO);
			free(prep_arg);
		}
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	ms_exec_echo_builtin(t_mshl *ms, char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	while (args[i] && ms_is_n(args[i]))
	{
		n_flag = true;
		i++;
	}
	ms_print_echo(args, n_flag, i, ms);
	return (EXIT_SUCCESS);
}
