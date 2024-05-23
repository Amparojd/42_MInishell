/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:47:19 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/08 21:32:12 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

extern int	g_status;

typedef struct s_fds
{
	char				*infile;
	char				*outfile;
	char				*heredoc_del;
	bool				heredoc_quotes;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
	bool				error_msg;
}	t_fds;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_fds				*fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{
	char				*content;
	char				*cc;
	bool				is_env_var;
	int					type;
	int					var_q_stat;
	int					index;
	bool				has_quotes;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_mshl
{
	char				**env;
	char				*pwd;
	char				*old_pwd;
	char				*line;
	bool				ctrlcheredoc;
	t_token				*token;
	t_command			*cmd;
	pid_t				pid;
}	t_mshl;

#endif
