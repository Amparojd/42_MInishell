/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:36:59 by mlezcano          #+#    #+#             */
/*   Updated: 2024/05/09 12:36:59 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_heredoc_loop(t_mshl *ms, t_fds *fds, int tmp_fd)
{
	char	*line;
	bool	success;

	success = false;
	line = NULL;
	while (1)
	{
		ms_listening_hdoc_input_sig();
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		ms_listening_no_interact_sig();
		if (line)
			ms_quit_newline_char(line);
		if (ms_loop_breaker(ms, &line, fds, &success))
			break ;
		ft_putendl_fd(line, tmp_fd);
		ms_ptr_free(line);
	}
	ms_ptr_free(line);
	return (success);
}

bool	ms_create_tmp(t_mshl *ms, t_fds *fds)
{
	int		tmp_fd;
	bool	success;

	success = true;
	tmp_fd = open(fds->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		success = false;
	else
	{
		success = ms_heredoc_loop(ms, fds, tmp_fd);
		close(tmp_fd);
	}
	return (success);
}

char	*ms_quit_heredoc_quot(char *delim, bool *heredoc_quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*heredoc_quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

char	*ms_put_name_tmp(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin("/tmp/.anshellmo_heredoc", number);
	free(number);
	i++;
	return (name);
}

void	ms_heredoc_main(t_mshl *ms, t_token **aux)
{
	t_token		*pre_delim;
	t_command	*last_cmd;
	t_fds		*fds;

	pre_delim = *aux;
	last_cmd = ms_scroll_lstcmd(ms->cmd);
	if (!ms_set_fd_struct(last_cmd))
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	fds = last_cmd->fds;
	if (ms_fds_error(fds))
		return ;
	fds->infile = ms_put_name_tmp();
	if (!fds->infile)
		ms_exit_msg(ms, ERR_ALLOC, EXIT_FAILURE);
	fds->heredoc_del = ms_quit_heredoc_quot(pre_delim->next->content, \
	& (fds->heredoc_quotes));
	if (ms_create_tmp(ms, fds))
		fds->fd_in = open(fds->infile, O_RDONLY);
	else
	{
		fds->fd_in = -1;
	}
	ms_skip_next_token(aux);
}
