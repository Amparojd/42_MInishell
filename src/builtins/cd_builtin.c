/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:52:33 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/12 20:41:27 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_update_pwd_oldpwd(t_mshl *ms, char *wd)
{
	ms_update_or_add_env_var(ms, "OLDPWD", \
	ms_get_env_var_value(ms->env, "PWD"));
	ms_update_or_add_env_var(ms, "PWD", wd);
	if (ms->old_pwd)
	{
		ms_ptr_free(ms->old_pwd);
		ms->old_pwd = ft_strdup(ms->pwd);
	}
	if (ms->pwd)
	{
		ms_ptr_free(ms->pwd);
		ms->pwd = ft_strdup(wd);
	}
	ms_ptr_free(wd);
}

bool	ms_cd(t_mshl *ms, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
	{
		ms_msg_err("cd", path, ERR_CD_PATH, 2);
		return (false);
	}
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		ms_msg_err(ERR_CD_GET, ERR_CD_GETCWD, strerror(errno), errno);
		ret = ft_strjoin(ms->pwd, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		ms_ptr_free(tmp);
	}
	else
		ret = ft_strdup(cwd);
	ms_update_pwd_oldpwd(ms, ret);
	return (true);
}

int	ms_exec_cd_builtin(t_mshl *ms, char **args)
{
	char	*path;

	if (!args[1] || ft_ispace(args[1][0]) || args[1][0] == '\0')
	{
		path = ms_get_env_var_value(ms->env, "HOME");
		if (!path || *path == '\0' || ft_is_space(*path))
			return (ms_msg_err("cd", NULL, ERR_CD_HOME, \
			EXIT_FAILURE));
		return (!ms_cd(ms, path));
	}
	if (args[2])
		return (ms_msg_err("cd", NULL, ERR_CD_ARG, 1));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ms_get_env_var_value(ms->env, "OLDPWD");
		if (!path)
			return (ms_msg_err("cd", NULL, ERR_OLPWD_NOT, \
			EXIT_FAILURE));
		ft_putendl_fd(path, 2);
		return (!ms_cd(ms, path));
	}
	return (!ms_cd(ms, args[1]));
}
