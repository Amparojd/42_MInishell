/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:32 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/11 19:04:51 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_unset_builtin(t_mshl *ms, char **args)
{
	int	i;
	int	pos;
	int	res;

	res = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!ms_check_valid_env_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			ms_msg_err("unset", args[i], "not a valid identifier", \
			false);
			res = EXIT_FAILURE;
		}
		else
		{
			pos = ms_search_env_index(ms->env, args[i]);
			if (pos != -1)
				ms_delete_env_var_pos(ms, pos);
		}
		i++;
	}
	return (res);
}
