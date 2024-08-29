/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:35:33 by younajja          #+#    #+#             */
/*   Updated: 2024/07/23 21:45:38 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_token	*skip_to_last_pipe(t_token *curr, int nb_pipes)
{
	int	count;

	count = 0;
	if (nb_pipes == 0)
		return (curr);
	while (curr->next)
	{
		if (curr->type == TOKEN_PIPE)
			count++;
		if (count == nb_pipes)
			break ;
		curr = curr->next;
	}
	return (curr);
}

void	insert_list(t_tree **node, t_token *token)
{
	t_tree	*new;
	t_tree	*curr;

	new = safe_malloc(sizeof(t_tree));
	new->right = NULL;
	new->left = NULL;
	new->type = token->type;
	new->value = token->value;
	new->next = NULL;
	if (!(*node))
	{
		*node = new;
		return ;
	}
	curr = *node;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	add_list_to_tree(t_tree **tree, t_token *token)
{
	while (token && token->type != TOKEN_PIPE)
	{
		insert_list(tree, token);
		token = token->next;
	}
}

t_tree	*process_tree(t_tree *tree, t_token **tokens, int nb_pipes)
{
	t_token	*curr;

	curr = NULL;
	if (nb_pipes < 0)
		return (NULL);
	curr = *tokens;
	if (*tokens == NULL)
		return (NULL);
	curr = skip_to_last_pipe(curr, nb_pipes);
	tree = create_tree(curr->value, curr->type);
	if (curr->next && nb_pipes > 0)
	{
		if (curr->next->type != TOKEN_PIPE)
			tree->right = create_tree(curr->next->value, curr->next->type);
		if (tree->right)
		{
			add_list_to_tree(&tree->right, curr->next->next);
			handle_flags(&tree->right);
		}
	}
	tree->left = process_tree(tree->left, tokens, nb_pipes - 1);
	task_khfifa(nb_pipes, tree, curr);
	return (tree);
}

t_tree	*build_tree(t_token **tokens, int nb_pipes)
{
	t_tree	*tree;

	tree = NULL;
	tree = process_tree(tree, tokens, nb_pipes);
	return (tree);
}
