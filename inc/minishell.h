/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:39:39 by ampjimen          #+#    #+#             */
/*   Updated: 2024/04/15 20:16:05 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Libraries
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "structs.h"
# include "macros.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"

//---MAIN---------------------------------------------------
// minishell.c
bool		ms_is_line_empty(char *line);

//---SIGNALS------------------------------------------------
// signals_interact.c 
void		ms_ctrl_backslash_ignore(void);
void		ms_ctrl_c_newline_hdoc(int signal);
void		ms_listening_hdoc_input_sig(void);
void		ms_ctrl_c_newline(int signal);
void		ms_listening_interact_sig(void);
// signals_no_interact.c
void		ms_sigquit_handler_no_interact(int signal);
void		ms_ctrl_backslash_ignore_no_interact(void);
void		ms_ctrl_c_newline_no_interact(int signal);
void		ms_listening_no_interact_sig(void);

//---LEXER--------------------------------------------------
//lexer_main.c
void		ms_main_loop(t_mshl *ms);
bool		ms_lexer_main(t_mshl *ms);
// quot_stx_errors.c
int			ms_quote_stat(int quote_stat, char *line, int scan);
bool		ms_quotes_err_n_read(t_mshl *ms, char *str);
// chunk_reader.c
bool		ms_oprtr_to_tkn(t_token **tkns, \
			char *line, int scan, int oprtr_type);
bool		ms_word_to_tkn(t_token **tkns, char *line, int scan, int start);
int			ms_chck_oprtr_type(char *line, int scan);
int			ms_chunk_reader(int *scan, char *line, int start_word, t_mshl *ms);
// manage_token_list.c
t_token		*ms_tkn_creat(char *content, \
			char *cntnt_cpy, int type, int qs);
void		ms_del_one_node_tkn(t_token *lst, void (*del)(void *));
void		ms_del_all_nodes_tkn(t_token **lst, void (*del)(void *));
void		ms_token_indx(t_mshl *ms);
void		ms_add_tkn_lst(t_token **lst, t_token *new_node);
// stx_errors.c 
bool		ms_stx_error_cases(t_token *token);
bool		ms_stx_err_iterator(t_token **token_list);
bool		ms_stx_err(t_token **token_list);

//---EXPANDER------------------------------------------------
//expander_main.c
void		ms_mark_variables(t_mshl *ms);
void		ms_expander_main(t_mshl *ms);
//scan.c
bool		ms_is_between_d_quot(char *content, int i);
bool		ms_is_bad_char_next(char next);
bool		ms_dollar_error(char *content, int scan);
void		ms_quote_stat_expndr(t_token **node, char scan);
void		ms_scan_variables(t_mshl *ms);
//process_quotes.c 
bool		ms_quote_detector(char *str);
int			ms_process_quotes(t_mshl *ms);
//quote_eraser.c
bool		ms_skip_quot_n_close(t_token **aux, int *pos);
void		ms_skip_quot_n_open(t_token **aux, int *pos);
bool		ms_is_quote_here(t_token **aux, int pos);
int			ms_len_wthout_quot(char *content, int len);
void		ms_quote_eraser(t_token **aux);
//process_variables.c
char		*replace_str_heredoc(char *str, char *var_value, int index);
char		*ms_replace_for_xpanded(t_token **aux, char *content,
				char *value, int pos);
bool		ms_xpand_if_null(t_token **aux, char *scontent, int pos);
void		ms_process_variables(char *value, t_token **aux, \
			int pos, t_mshl *ms);
//extract_var_value.c
char		*ms_dup_env_var_value(t_mshl *ms, char *var);
bool		ms_is_env_var(t_mshl *ms, char *var_nme);
char		*ms_xtract_var_value(t_token *token, char *str, t_mshl *ms);
//extract_var_name.c 
bool		ms_isalphanum_or__(char c);
int			ms_var_name_len(char *str);
char		*ms_xtract_var_name(t_mshl *ms, char *str);
//get_variable_str.c 
void		ms_val_cpy(char *new, char *value, int *j);
char		*ms_get_var_str(char *content, char *value, \
				int trim_len, int scan);
//heredoc_expander.c 
char		*ms_addspace_btwn_words(char **tab);
char		*ms_heredoc_var_xpndr(t_mshl *ms, char *str);
char		*ms_heredoc_xpndr_main(t_mshl *ms, char *line);

//---PARSER--------------------------------------------------
// parser_main.c
void		ms_cmd_no_arg_prccs(t_mshl *ms);
void		ms_parser_main(t_mshl *ms);
// cmd_container_creat.c 
t_command	*ms_new_cmd_lst(void);
void		ms_addlst_cmd_container(t_mshl *ms, t_command **cmd_list);
// parser_words.c 
bool		ms_is_there_space(char *str);
void		ms_split_in_args(t_command *aux_c, char *tkn_cntnt, t_mshl *ms);
void		ms_word_n_var_parser(t_mshl *ms, t_token **tkn_list);
// cmd_arg_filler.c 
bool		ms_cmd_arg_only_fill(t_token **arg_list, \
			t_command *cmd, bool is_echo);
bool		ms_cmd_arg_creat_n_fill(t_token **arg_list, \
			t_command *cmd, bool is_echo);
bool		ms_cmd_arg_filler(t_token **arg_list, t_command *cmd);
void		ms_rm_echo_empty_words(t_token **arg_list);
// parser_input.c
void		ms_infile_open(t_fds *fds, char *content, char *cc);
void		ms_infile_parser(t_mshl *ms, t_token **token_lst);
// heredoc.c
bool		ms_heredoc_loop(t_mshl *ms, t_fds *fds, int fd);
bool		ms_create_tmp(t_mshl *ms, t_fds *fds);
char		*ms_quit_heredoc_quot(char *delim, bool *quotes);
char		*ms_put_name_tmp(void);
void		ms_heredoc_main(t_mshl *ms, t_token **aux);
// parser_trunc.c  
void		ms_create_trunc(t_fds *fds, char *content, char *cc);
void		ms_trunc_parser(t_mshl *ms, t_token **tkn_list);
// parser_append.c
void		ms_append_file(t_fds *fds, char *content, char *cc);
void		ms_append_parser(t_mshl *ms, t_token **tkn_list);
// parser_pipe.c
void		ms_pipe_parser(t_mshl *ms, t_token **tkn_list);
	//---PARSER/PARSER_UTILS-----------------------------------
// cmd_arg_filler_utils.c
int			ms_word_n_var_counter(t_token *temp);
char		**ms_create_table(
				int len, char **args_table, t_command *cmd,
				t_token **arg_list);
// heredoc_utils.c
bool		ms_g_status_handler(char **line, t_mshl *ms);
bool		ms_loop_breaker(t_mshl *ms, \
			char **line, t_fds *fds, bool *stop);
void		ms_quit_newline_char(char *line);
// parser_general_utils.c 
bool		ms_fds_error(t_fds *fds);
bool		ms_fds_error2(t_fds *fds);
t_command	*ms_scroll_lstcmd(t_command *aux);
void		ms_skip_next_token(t_token **aux);
// cmd_list_cleaner.c
void		ms_del_one_node_cmd(t_command *lst, void (*del)(void *));
void		ms_del_all_nodes_cmd(t_command **lst, void (*del)(void *));

//--UTILS---------------------------------------------------------------
// errors.c
char		*ms_strjoin(char *str1, char *str2);
bool		ms_is_export_or_unset(char *command);
int			ms_msg_err(char *cc, char *info, char *msg, int error_code);
void		ms_exit_msg(t_mshl *ms, char *msg, int exit_code);
void		ms_err_stx_out(char *message, char *quote, int is_quote);
// exit.c
void		ms_exit_ms(t_mshl *ms, int exno);
// ms_set_main_struct.c
bool		ms_set_pwd_and_oldpwd(t_mshl *ms);
bool		ms_generate_env(t_mshl *ms);
bool		ms_set_env_var(t_mshl *ms, char **env);
bool		ms_set_main_struct(t_mshl *ms, char **env);
bool		ms_set_fd_struct(t_command *cmd);
// free_data.c
void		ms_data_free(t_mshl *ms, bool clear_history);
void		ms_close_fds(t_command *cmds, bool close_backups);
void		ms_io_free(t_fds *fds);
void		ms_ptr_free_arr(char **tab);
void		ms_ptr_free(void *ptr);

// mslvl.c
void		ms_modify_mslvl(t_mshl *ms);
char		**ms_append_to_matrix(char **old_matrix, char *line);
char		*ms_search_env(t_mshl *ms, char *env_key);

// env.c
void		ms_refresh_pwd_env(t_mshl *ms);
void		ms_modify_or_add_env(t_mshl *ms, char *line);
bool		ms_copy_environment(t_mshl *ms, char **envp);

// env_built.c
int			ms_count_env_variable(char **env);
int			ms_search_env_index(char **env, char *var);
char		*ms_get_env_var_value(char **env, char *var);
bool		ms_check_valid_env_key(char *var);

// env_handlers.c
char		**ms_update_env_vars(t_mshl *ms, int size);
bool		ms_update_or_add_env_var(t_mshl *ms, char *key, char *value);
bool		ms_delete_env_var_pos(t_mshl *ms, int idx);

// builtins
//cd_builtin
void		ms_update_pwd_oldpwd(t_mshl *ms, char *wd);
bool		ms_cd(t_mshl *ms, char *path);
int			ms_exec_cd_builtin(t_mshl *ms, char **args);

//echo_builtin
bool		ms_is_n(char *arg);
void		ms_print_echo(char **args, bool n_flag, int i, t_mshl *ms);
int			ms_exec_echo_builtin(t_mshl *ms, char **args);
bool		ms_quote_check(char *s);
void		ms_count_no_ws(const char *s, int i, int *len_new, int len);
bool		ms_is_var_no_quotes(t_token *tkns, int index);
char		*ms_rm_extra_spaces(const char *s);

//env_builtin
int			ms_exec_env_builtin(t_mshl *ms, char **args);

//exit_builtin
int			ms_exec_exit_builtin(t_mshl *ms, char **args);
bool		ms_check_long_range(int neg, unsigned long long num, bool *error);
int			ft_atoi_long(const char *str, bool *error);
int			ms_get_exit_code(char *arg, bool *error);

//export_builtin
void		ms_qsort_env(char **env, int n);
int			ms_exec_export_builtin(t_mshl *ms, char **args);

//pwd_builtin
int			ms_exec_pwd_builtin(t_mshl *ms, char **args);

//unset_builtin
int			ms_exec_unset_builtin(t_mshl *ms, char **args);

// ms_execute.c
int			ms_execute_main(t_mshl *ms);
int			ms_child_status(t_mshl *ms);
int			ms_create_children(t_mshl *ms);
int			ms_prep_command(t_mshl *ms);

// ms_command_exec.c
int			ms_exec_sys_binary(t_mshl *ms, t_command *cmd);
int			ms_exec_local_binary(t_mshl *ms, t_command *cmd);
int			ms_command_exec(t_mshl *ms, t_command *cmd);
int			ms_exec_builtin_cmd(t_mshl *ms, t_command *cmd);

// execute_utils.c
bool		ms_is_directory(char *cmd);
int			ms_check_cmd_validity(t_mshl *ms, t_command *cmd);

// parse_path.c
char		*ms_get_cmd_path(t_mshl *ms, char *cmd);
char		*ms_find_valid_cmd_path(char *cmd, char **paths);
char		**ms_get_env_paths(t_mshl *ms);

// pipe.c
bool		ms_create_pipes(t_mshl *ms);
bool		ms_config_pipes_fd(t_command *cmds, t_command *curr_cmd);
void		ms_close_un_pipes_fd(t_command *cmds, t_command *skip_cmd);

// file_io.c
bool		ms_check_io(t_fds *fds);
bool		ms_config_io(t_fds *fds);
bool		ms_reset_io(t_fds *fds);

// utils and others
void		rl_replace_line(const char *text, int clear_undo);

#endif