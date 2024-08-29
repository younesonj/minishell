/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:05:12 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/21 03:31:06 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	simple_random(void)
{
	static unsigned int	seed = 1;

	seed = (seed * 1103515245 + 12345);
	return ((int)seed);
}

int	simple_random_range(int min, int max)
{
	return (min + (simple_random() % (max - min + 1)));
}

void	norminette(t_tree *tree, t_env *env, t_data *data, char *str)
{
	g_global.ambiguous = 0;
	while (tree && tree->type == TOKEN_REDINPUT)
	{
		if (tree->type != TOKEN_REDINPUT)
			break ;
		redinput(tree, env, *data);
		tree = tree->next->next;
	}
	if (g_global.redirect != 1)
	{
		if (tree && tree->type == TOKEN_REDOUTPUT)
			redoutput(tree, *data);
		if (tree && tree->type == TOKEN_APPEND)
			append(tree, *data);
	}
	initialize_variables(env, data, str);
}

void	words_handler(t_tree *tree, t_env *env, t_data *data)
{
	t_tree	*tmp;

	tmp = tree;
	data->joiner = NULL;
	g_global.redirect = 0;
	while (tree)
	{
		g_global.check = tree->value;
		if (tree->type != TOKEN_WORD)
			break ;
		data->joiner = ft_strjoin(data->joiner, tree->value);
		data->str = data->joiner;
		while (tree->next && tree->next->type == TOKEN_WORD)
		{
			if (tree->next->value == NULL)
				tree->next->value = "''";
			data->joiner = ft_strjoin(data->joiner, " ");
			if (ft_strcmp(tree->next->value, "'''"))
				data->joiner = ft_strjoin(data->joiner, tree->next->value);
			tree = tree->next;
		}
		tree = tree->next;
	}
	norm3(tree, env, data, tmp);
}

void	redinput(t_tree *tree, t_env *env, t_data data)
{
	while (tree && tree->next && tree->next->type == TOKEN_WORD)
	{
		if (tree->next && tree->next->value == NULL && g_global.heredoc == 0)
			return (bye_bye1(" : No such file or directory\n"));
		if (tree && tree->type != TOKEN_REDINPUT)
			break ;
		data.fd = open(tree->next->value, O_RDONLY);
		if (data.fd == -1)
		{
			g_global.redirect = 1;
			g_global.status = 1;
			return (perror(tree->next->value));
		}
		dup2(data.fd, STDIN_FILENO);
		close(data.fd);
		tree = tree->next->next;
	}
	if (tree)
		tree_execution(tree, env, data);
}
