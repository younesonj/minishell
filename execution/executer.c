/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:55:29 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/21 01:06:47 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	child1(t_tree *tree, t_env *env, t_data data)
{
	close(data.pipefd[0]);
	dup2(data.pipefd[1], STDOUT_FILENO);
	close(data.pipefd[1]);
	tree_execution(tree->left, env, data);
	free_garbage(&g_global.garbage_list);
	exit(g_global.status);
}

void	child2(t_tree *tree, t_env *env, t_data data)
{
	close(data.pipefd[1]);
	dup2(data.pipefd[0], STDIN_FILENO);
	close(data.pipefd[0]);
	tree_execution(tree->right, env, data);
	free_garbage(&g_global.garbage_list);
	exit(0);
}

void	pipe_handler(t_tree *tree, t_env *env, t_data data)
{
	int	status;

	if (pipe(data.pipefd) == -1)
		return (bye_bye1("pipe didn't work\n"));
	data.pid2 = fork();
	if (data.pid2 == -1)
		return (bye_bye1("fork didn't work\n"));
	if (data.pid2 == 0)
		child1(tree, env, data);
	else
	{
		data.pid3 = fork();
		if (data.pid3 == -1)
			return (bye_bye1("fork didn't work\n"));
		if (data.pid3 == 0)
			child2(tree, env, data);
	}
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	waitpid(data.pid2, &status, 0);
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	if (g_global.status == 141)
		g_global.status = 127;
	waitpid(data.pid3, NULL, 0);
}

void	lkmala(t_tree *tree, t_env *env, t_data data)
{
	if (tree->type == TOKEN_APPEND)
	{
		first_append(tree, env, data);
		restore_stdin_stdout(data.std_in, data.std_out);
	}
	if (tree->type == TOKEN_PIPE)
	{
		signal(SIGINT, sig_hand);
		pipe_handler(tree, env, data);
		signal(SIGINT, ctrl_c_handler);
		restore_stdin_stdout(data.std_in, data.std_out);
	}
}

void	tree_execution(t_tree *tree, t_env *env, t_data data)
{
	if (!ft_strcmp(tree->value, "'''"))
		return ;
	if (!tree->value)
		return (bye_bye1("Command not found\n"));
	save_stdin_stdout(&data.std_in, &data.std_out);
	if (tree->type == TOKEN_WORD)
	{
		words_handler(tree, env, &data);
		restore_stdin_stdout(data.std_in, data.std_out);
	}
	if (tree->type == TOKEN_REDINPUT)
	{
		redinput(tree, env, data);
		restore_stdin_stdout(data.std_in, data.std_out);
	}
	if (tree->type == TOKEN_REDOUTPUT)
	{
		first_redoutput(tree, env, data);
		restore_stdin_stdout(data.std_in, data.std_out);
	}
	lkmala(tree, env, data);
}
