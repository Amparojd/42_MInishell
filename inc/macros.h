/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:34:03 by mlezcano          #+#    #+#             */
/*   Updated: 2024/04/12 19:05:52 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "minishell.h"

//main errors
# define ERR_ARG		"Argument input Error!\nPlease, introduce:\n./minishell"
# define ERR_ALLOC		"Memory allocation error"

//syntax errors
# define ERR_SYNTX_QUO	"syntax error: unclosed quote:"
# define ERR_SYNTX_TKN	"syntax error near unexpected token"

//builtin errors 
# define ERR_OLPWD_NOT	"Error: OLDPWD not set"
# define ERR_UNSET		"Error: not a valid identifier"
# define ERR_CD_PATH	"Error: No such file or directory"
# define ERR_CD_GET		"cd: error retrieving current directory"
# define ERR_CD_GETCWD	"getcwd: cannot access parent directories"
# define ERR_CD_HOME	"Error: HOME not set"
# define ERR_CD_ARG		"Error: too many arguments"

//return values
# define CMD_UNKNOWN		127
# define CMD_NOT_EXECUTABLE	126
# define ERR_NUM_ARR		255
# define ERR_PIPE_STX		258

//heredoc loop
# define BREAK	1
# define GO		0

//shell prompt
# define PROMPT			"AnShellmo$ "

//other shell values
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

//enums
enum e_token_types
{
	SPACES = 1,
	HEREDOC,
	VAR,
	INPUT,
	WORD,
	PIPE,
	TRUNC,
	APPEND,
	FAILURE,
	END
};

enum e_quotes
{
	OPN_SQ,
	OPN_DQ,
	OK_Q
};

#endif