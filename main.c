/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:30:06 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/22 23:57:38 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_global	g_global;

void	initialize(void)
{
	g_global.checker = 0;
	g_global.heredoc = 0;
	g_global.flag = 0;
	g_global.expander = 0;
	g_global.flag3 = 0;
}

t_token	*ft_norm(char *line, t_env *env, t_data data)
{
	t_lexer	*lexer;
	t_token	*token;
	t_token	*res;

	initialize();
	lexer = init_lexer(line);
	token = NULL;
	res = NULL;
	if (!check_syntax_error_quotes(line))
	{
		printf("minishell: syntax error\n");
		g_global.status = 2;
		return (NULL);
	}
	token = lexer_get_next_token(lexer, env);
	while (token)
	{
		token->next = NULL;
		insert(&res, token);
		token = lexer_get_next_token(lexer, env);
	}
	if (!check_syntax_errors(&res))
		res = NULL;
	heredoc_runner(res, data, env);
	return (res);
}

t_tree	*ft_tokenization(t_tree *tree, char *line, t_env *env, t_data data)
{
	t_lexer	*lexer;
	t_token	*token;
	t_token	*res;

	res = ft_norm(line, env, data);
	if (res == NULL)
		return (NULL);
	g_global.checker = 0;
	if (g_global.heredoc == 0)
	{
		g_global.checker = 1;
		lexer = init_lexer(line);
		res = NULL;
		token = lexer_get_next_token(lexer, env);
		while (token)
		{
			token->next = NULL;
			insert(&res, token);
			token = lexer_get_next_token(lexer, env);
		}
	}
	tree = build_tree(&res, count_pipe(res));
	return (tree);
}

void	simulation(t_tree *tree, t_data data, char **env)
{
	char	*line;
	char	*prompt;
	t_env	*env_l;

	env_l = env_to_list(env);
	if (!env_l)
		insert_env(&env_l, NULL, NULL);
	prompt = COLOR_YELLOW "minishell$ " COLOR_RESET;
	line = readline(prompt);
	while (line)
	{
		tree = ft_tokenization(tree, line, env_l, data);
		path_test_lhbal();
		if (tree)
			tree_execution(tree, env_l, data);
		if (line[0] != '\0')
			add_history(line);
		free(line);
		line = readline(prompt);
	}
	if (!line)
	{
		printf("exit\n");
		free_garbage(&g_global.garbage_list);
	}
}

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	t_data	data;

	(void)av;
	g_global.garbage_list = NULL;
	g_global.status = 0;
	tree = NULL;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctr_back_slash);
	signal(SIGQUIT, SIG_IGN);
	if (ac > 1)
	{
		bye_bye1("Usage: ./minishell\n");
		return (1);
	}
	data.paths = NULL;
	simulation(tree, data, env);
	return (0);
}
