/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:09 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/07 22:59:26 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_check_long_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_ispace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (ms_check_long_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

int	ms_get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_status);
	i = 0;
	while (ft_ispace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_ispace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

int	ms_exec_exit_builtin(t_mshl *ms, char **args)
{
	int		exit_code;
	bool	error;

	error = false;
	if (!args || !args[1])
		exit_code = g_status;
	else
	{
		exit_code = ms_get_exit_code(args[1], &error);
		if (error)
			exit_code = ms_msg_err("exit", args[1],
					"numeric argument required", ERR_NUM_ARR);
		else if (args[2])
			return (ms_err_stx_out(ERR_CD_ARG, "exit", true), 1);
	}
	ms_exit_ms(ms, exit_code);
	return (2);
}
