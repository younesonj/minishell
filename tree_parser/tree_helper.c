/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:50:44 by younajja          #+#    #+#             */
/*   Updated: 2024/07/23 21:45:46 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_tree	*create_tree(char *s, t_token_type type)
{
	t_tree	*new;

	new = safe_malloc(sizeof(t_tree));
	new->type = type;
	new->value = s;
	new->right = NULL;
	new->left = NULL;
	new->next = NULL;
	return (new);
}

void	task_khfifa(int nb_pipes, t_tree *tree, t_token *curr)
{
	if (nb_pipes == 0)
	{
		add_list_to_tree(&tree, curr->next);
		handle_flags(&tree);
	}
}
