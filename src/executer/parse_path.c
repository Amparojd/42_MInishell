/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:52:06 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/08 20:04:48 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			ms_msg_err("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ms_ptr_free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**ms_get_env_paths(t_mshl *ms)
{
	char	**env_paths;

	if (ms_search_env_index(ms->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(ms_get_env_var_value(ms->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

char	*ms_get_cmd_path(t_mshl *ms, char *str)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!str)
		return (NULL);
	env_paths = ms_get_env_paths(ms);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", str);
	if (!cmd)
	{
		ms_ptr_free_arr(env_paths);
		return (NULL);
	}
	cmd_path = ms_find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		ms_ptr_free(cmd);
		ms_ptr_free_arr(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
