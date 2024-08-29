/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:30:03 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/23 00:53:24 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum t_token_type
{
	TOKEN_WORD,
	TOKEN_REDINPUT,
	TOKEN_REDOUTPUT,
	TOKEN_PIPE,
	TOKEN_APPEND,
	TOKEN_HERDOC,
	TMP
}						t_token_type;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_global
{
	int					status;
	int					if_single;
	int					flag;
	int					flag2;
	int					flag3;
	int					flag4;
	int					checker;
	int					heredoc;
	int					expander;
	int					redirect;
	int					ambiguous;
	char				*file;
	char				*check;
	char				*path;
	t_garbage			*garbage_list;
}						t_global;

extern t_global			g_global;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	char				*content;
	char				c;
	int					i;
	char				*value;
	char				*str;
	char				*string;
	char				*tmp;
	int					remember;
}						t_lexer;

typedef struct s_data
{
	char				*str;
	char				*joiner;
	char				*command;
	char				**paths;
	char				**cmd;
	char				**envp;
	char				*cmd_path;
	char				*envp_paths;
	int					pipefd[2];
	int					i;
	int					fd;
	int					std_in;
	int					std_out;
	pid_t				pid;
	pid_t				pid2;
	pid_t				pid3;
}						t_data;

typedef struct s_tree
{
	t_token_type		type;
	char				*value;
	struct s_tree		*next;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

typedef struct s_env
{
	char				*env_line;
	char				*key;
	struct s_env		*next;
}						t_env;

# define COUNT 10
# define COLOR_RESET "\x1b[0m"
# define COLOR_YELLOW "\x1b[32m"

/*helpers*/
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strlen(const char *str);
int						ft_isalnum(int i);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s1);
int						ft_printable(int i);
char					*ft_strjoin(char *s1, char *s2);
void					bye_bye1(char *str);
int						lenght(int n);
char					*ft_itoa(int n);
int						ft_atoi(const char *str);
int						check_digit(char *s);
void					insert(t_token **list, t_token *token);
int						count_pipe(t_token *res);
int						check_syntax_error_quotes(char *str);
char					*if_dollar(t_lexer *lexer, t_env *env, char *value);
int						simple_random_range(int min, int max);
void					path_test_lhbal(void);
void					*safe_malloc(size_t size);
t_garbage				*new_garbage_node(void *ptr);
void					add_garbage_node(t_garbage **list, t_garbage *new_node);
void					free_garbage(t_garbage **list);

/*tokenizer*/
t_lexer					*init_lexer(char *content);
void					lexer_advance(t_lexer *lexer);
void					insert(t_token **list, t_token *token);
char					*check_for_dquote(t_lexer *lexer, t_env *env,
							char *value);
char					*check_for_squote(t_lexer *lexer, char *value);
char					*lexer_get_current_char_as_string(t_lexer *lexer);
void					double_quote(t_lexer *lexer, t_env *env);
void					back_slash(t_lexer *lexer, t_env *env);
char					*norm2(t_lexer *lexer, char *str);
char					*check(char *value);
void					double_quote_condition(t_lexer *lexer, t_env *env);
t_token					*init_token(int type, char *value);
t_token					*lexer_advance_with_token(t_lexer *lexer,
							t_token *token);
t_token					*lexer_get_next_token(t_lexer *lexer, t_env *env);

/*tree*/
t_tree					*build_tree(t_token **tokens, int nb_pipes);
t_tree					*create_tree(char *s, t_token_type type);
void					handle_flags(t_tree **tree);
void					swap_data(int *a, int *b);
void					swap_strings(char **a, char **b);
int						check_syntax_errors(t_token **token);
void					task_khfifa(int nb_pipes, t_tree *tree, t_token *curr);
void					add_list_to_tree(t_tree **tree, t_token *token);

/*signals*/
void					ctrl_c_handler(int signum);
void					ctr_back_slash(int signum);
void					sig_hand(int sig);
int						*return_value(void);
void					signal_herdoc(int sig);
void					ctrl_c_handler2(int sig);
void					signal_mini(int signal);
void					check_signal_heredoc(void);

/*builtins*/
void					ft_echo(t_tree *tree);
void					ft_pwd(void);
void					ft_exit_b(t_tree *tree);
void					ft_cd(t_tree *tree, t_env *env);
void					ft_env(t_env *env);
t_env					*env_to_list(char **env);
void					ft_unset(t_env **env, t_tree *tree);
void					ft_export(t_env **env, t_tree *tree);
void					insert_env(t_env **list, char *s, char *key);
char					*extract_key(char *env);
int						equal_detected(char *s);
void					handle_addition(t_env **env, t_tree *tree);
int						check_if_key_repeated(char *s, t_env **env);
void					write_export_line(char *s);
void					ft_exit_helper1(void);
void					ft_exit_helper2(char *s);
void					ft_exit_helper3(int nb);
void					ft_exit_helper4(int nb);
void					path_test_lhbal(void);
void					ft_change_old_path(t_env *env);
void					ft_exit_helper_5(void);

/*execution*/
void					initialize_variables(t_env *envp, t_data *data,
							char *str);
void					fork_pid(t_data *data);
char					**env_to_array(t_env *envp);
char					*get_paths(t_env *envp);
void					check1(t_tree *tree, t_data data);
void					check2(t_tree *tree, t_data data);
int						ambiguous(char *str);
void					redoutput(t_tree *tree, t_data data);
void					redinput(t_tree *tree, t_env *env, t_data data);
void					append(t_tree *tree, t_data data);
void					forker(t_data *data);
void					heredoc_runner(t_token *tmp, t_data data, t_env *env);
void					words_handler(t_tree *tree, t_env *env, t_data *data);
int						checkers(t_tree *tree, t_env *env);
void					norminette(t_tree *tree, t_env *env, t_data *data,
							char *str);
void					norm3(t_tree *tree, t_env *env, t_data *data,
							t_tree *tmp);
void					first_redoutput(t_tree *tree, t_env *env, t_data data);
void					first_append(t_tree *tree, t_env *env, t_data data);
void					save_stdin_stdout(int *std_in, int *std_out);
void					restore_stdin_stdout(int std_in, int std_out);
void					tree_execution(t_tree *tree, t_env *env, t_data data);

#endif