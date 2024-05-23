/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:03 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/26 17:38:03 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_set_pwd_and_oldpwd(t_mshl *ms)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	ms->pwd = ft_strdup(wd);
	if (!ms->pwd)
		return (false);
	if (ms_search_env_index(ms->env, "OLDPWD") != -1)
	{
		ms->old_pwd = ft_strdup(ms_get_env_var_value(ms->env,
					"OLDPWD"));
		if (!ms->old_pwd)
			return (false);
	}
	else
	{
		ms->old_pwd = ft_strdup(wd);
		if (!ms->old_pwd)
			return (false);
	}
	return (true);
}

bool	ms_generate_env(t_mshl *ms)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(pwd);
		return (false);
	}
	ms->env = malloc(sizeof(char *) * 4);
	if (!ms->env)
		return (false);
	ms->env[0] = ft_strjoin("PWD=", pwd);
	ms->env[1] = ft_strdup("SHLVL=1");
	ms->env[2] = ft_strdup("_=/usr/bin/env");
	if (!ms->env[0] || !ms->env[1] || !ms->env[2])
		return (false);
	ms->env[3] = NULL;
	free(pwd);
	return (true);
}

bool	ms_set_env_var(t_mshl *ms, char **env)
{
	if (!*env)
	{
		if (!ms_generate_env(ms))
			return (false);
	}
	else
	{
		if (!ms_copy_environment(ms, env))
			return (false);
	}
	return (true);
}

bool	ms_set_main_struct(t_mshl *ms, char **env)
{
	if (!ms_set_env_var(ms, env))
	{
		ms_msg_err("Error", NULL, \
		"Failed to initialize environment variables", errno);
		return (false);
	}
	if (!ms_set_pwd_and_oldpwd(ms))
	{
		ms_msg_err("Error", NULL, \
		"Failed to initialize working directories", errno);
		return (false);
	}
	ms->line = NULL;
	ms->ctrlcheredoc = false;
	ms->token = NULL;
	ms->cmd = NULL;
	ms->pid = -1;
	g_status = 0;
	return (true);
}

bool	ms_set_fd_struct(t_command *cmd)
{
	if (!cmd->fds)
	{
		cmd->fds = malloc(sizeof * cmd->fds);
		if (!cmd->fds)
			return (false);
		cmd->fds->infile = NULL;
		cmd->fds->outfile = NULL;
		cmd->fds->heredoc_del = NULL;
		cmd->fds->heredoc_quotes = false;
		cmd->fds->fd_in = -1;
		cmd->fds->fd_out = -1;
		cmd->fds->stdin_backup = -1;
		cmd->fds->stdout_backup = -1;
		cmd->fds->error_msg = false;
	}
	return (true);
}
