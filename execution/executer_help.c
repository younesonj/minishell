/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:26:30 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/23 00:53:32 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	first_redoutput(t_tree *tree, t_env *env, t_data data)
{
	while (tree != NULL && tree->type == TOKEN_REDOUTPUT)
	{
		if (tree->next && tree->next->type == TOKEN_WORD)
		{
			if (!ft_strcmp(tree->next->value, "'''")
				|| ambiguous(tree->next->value) == 1)
				return (bye_bye1("minishell: ambiguous redirect\n"));
			data.fd = open(tree->next->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (data.fd == -1)
			{
				g_global.status = 1;
				return (bye_bye1("No such file or directory\n"));
			}
			dup2(data.fd, STDOUT_FILENO);
			close(data.fd);
		}
		else
			break ;
		tree = tree->next->next;
	}
	if (tree)
		tree_execution(tree, env, data);
}

void	first_append(t_tree *tree, t_env *env, t_data data)
{
	while (tree != NULL && tree->type == TOKEN_APPEND)
	{
		if (tree->next && tree->next->type == TOKEN_WORD)
		{
			if (!ft_strcmp(tree->next->value, "'''")
				|| ambiguous(tree->next->value) == 1)
				return (bye_bye1("minishell: ambiguous redirect\n"));
			data.fd = open(tree->next->value, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (data.fd == -1)
			{
				g_global.status = 1;
				return (bye_bye1("No such file or directory\n"));
			}
			dup2(data.fd, STDOUT_FILENO);
			close(data.fd);
		}
		else
			break ;
		tree = tree->next->next;
	}
	if (tree)
		tree_execution(tree, env, data);
}

void	redoutput(t_tree *tree, t_data data)
{
	while (tree != NULL && tree->type == TOKEN_REDOUTPUT)
	{
		if (tree->next && tree->next->type == TOKEN_WORD)
		{
			if (!ft_strcmp(tree->next->value, "'''")
				|| ambiguous(tree->next->value) == 1)
			{
				g_global.ambiguous = 1;
				return (bye_bye1("minishell: ambiguous redirect\n"));
			}
			data.fd = open(tree->next->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (data.fd == -1)
			{
				g_global.status = 1;
				g_global.ambiguous = 1;
				return (bye_bye1("No such file or directory\n"));
			}
			dup2(data.fd, STDOUT_FILENO);
			close(data.fd);
		}
		tree = tree->next->next;
	}
	check1(tree, data);
}

void	append(t_tree *tree, t_data data)
{
	while (tree != NULL && tree->type == TOKEN_APPEND)
	{
		if (tree->next && tree->next->type == TOKEN_WORD)
		{
			if (!ft_strcmp(tree->next->value, "'''")
				|| ambiguous(tree->next->value) == 1)
			{
				g_global.ambiguous = 1;
				return (bye_bye1("minishell: ambiguous redirect\n"));
			}
			data.fd = open(tree->next->value, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (data.fd == -1)
			{
				g_global.ambiguous = 1;
				g_global.status = 1;
				return (bye_bye1("No such file or directory\n"));
			}
			dup2(data.fd, STDOUT_FILENO);
			close(data.fd);
		}
		tree = tree->next->next;
	}
	check2(tree, data);
}

int	lenght(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
