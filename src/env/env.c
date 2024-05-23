/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:39 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/08 19:53:47 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_copy_environment(t_mshl *ms, char **envp)
{
	int		i;

	if (*envp)
		ms->env = matrixdup(envp);
	ms_modify_mslvl(ms);
	ms_refresh_pwd_env(ms);
	if (!ms->env)
		return (false);
	i = 0;
	while (ms->env[i])
	{
		if (!ms->env[i])
			return (false);
		i++;
	}
	return (true);
}

void	ms_modify_or_add_env(t_mshl *ms, char *line)
{
	int		i;
	char	**split_line;
	char	**split_env;

	split_line = ft_split(line, '=');
	i = 0;
	while (ms->env[i])
	{
		split_env = ft_split(ms->env[i], '=');
		if (strcmp(split_line[0], split_env[0]) == 0)
		{
			free_arr(split_env);
			free_arr(split_line);
			free(ms->env[i]);
			ms->env[i] = ft_strdup(line);
			return ;
		}
		i++;
		free_arr(split_env);
	}
	free_arr(split_line);
	ms->env[i] = ft_strdup(line);
}

void	ms_refresh_pwd_env(t_mshl *ms)
{
	char	*pwd;
	char	*str;

	pwd = ms_search_env(ms, "PWD");
	if (!pwd)
	{
		str = getcwd(NULL, 0);
		ms->env = ms_append_to_matrix(ms->env, str);
		free(str);
		return ;
	}
}
