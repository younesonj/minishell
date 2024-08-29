/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:53:49 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/04 23:41:19 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	for_norm(t_data *data)
{
	int	num;

	g_global.heredoc = 1;
	g_global.expander = 1;
	num = simple_random_range(0, 100);
	g_global.file = ft_strjoin(NULL, "/tmp/.heredoc");
	g_global.file = ft_strjoin(g_global.file, ft_itoa(num));
	data->fd = open(g_global.file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd == -1)
	{
		g_global.status = 1;
		return (bye_bye1("Error opening heredoc file"), -1);
	}
	return (num);
}

char	*receiver(t_env *env, char *line)
{
	char	*value;
	t_lexer	*lexer;

	if (g_global.flag == 1)
		g_global.checker = 0;
	else
		g_global.checker = 1;
	lexer = init_lexer(line);
	value = NULL;
	while (lexer->c)
	{
		if (g_global.flag != 1)
			if (lexer->c == '$')
				value = if_dollar(lexer, env, value);
		value = ft_strjoin(value, lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (value);
}

void	helper(t_token *tmp, t_data data, t_env *env)
{
	char	*value;
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (tmp->next->value == NULL)
			if (!ft_strcmp(line, "\0"))
				break ;
		if (!ft_strcmp(line, tmp->next->value))
			break ;
		value = receiver(env, line);
		write(data.fd, value, ft_strlen(value));
		write(data.fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (!line && *return_value() == -1)
	{
		printf("!: here-document delimited by end-of-file (wanted `%s')\n",
			tmp->next->value);
		return ;
	}
	free(line);
}

void	heredoc_runner(t_token *tmp, t_data data, t_env *env)
{
	int	num;

	while (tmp && tmp->next)
	{
		if (tmp->type == TOKEN_HERDOC && tmp->next->type == TOKEN_WORD)
		{
			signal(SIGINT, signal_herdoc);
			num = for_norm(&data);
			if (num == -1)
				return ;
			helper(tmp, data, env);
			tmp->value = "<";
			tmp->type = TOKEN_REDINPUT;
			tmp->next->value = g_global.file;
			tmp->next->type = TOKEN_WORD;
			close(data.fd);
			if (*return_value() != -1)
			{
				check_signal_heredoc();
				return ;
			}
		}
		tmp = tmp->next;
	}
	signal(SIGINT, ctrl_c_handler);
}

void	check2(t_tree *tree, t_data data)
{
	if (tree && tree->type == TOKEN_REDINPUT)
	{
		redinput(tree, NULL, data);
		tree = tree->next->next;
	}
	if (tree && tree->type == TOKEN_REDOUTPUT)
		redoutput(tree, data);
}
