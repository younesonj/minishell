/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_things.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:49:53 by younajja          #+#    #+#             */
/*   Updated: 2024/08/16 18:38:58 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	change_token_tmp(t_tree **tree)
{
	t_tree	*curr;

	curr = *tree;
	while (curr)
	{
		if (curr->type != TOKEN_WORD && curr->type != TMP)
			curr->next->type = TMP;
		curr = curr->next;
	}
}

void	swap_data(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	change_token_regular(t_tree **tree)
{
	t_tree	*curr;

	curr = *tree;
	while (curr)
	{
		if (curr->type == TMP)
			curr->type = TOKEN_WORD;
		curr = curr->next;
	}
}

void	handle_flags(t_tree **tree)
{
	t_tree	*curr;
	t_tree	*beg;

	change_token_tmp(tree);
	curr = *tree;
	while (curr && curr->type != TOKEN_WORD)
		curr = curr->next;
	beg = curr;
	if (!curr)
	{
		change_token_regular(tree);
		return ;
	}
	while (curr->next)
	{
		if (curr->type != TOKEN_WORD && curr->next->type == TOKEN_WORD)
		{
			swap_data((int *)&curr->type, (int *)&curr->next->type);
			swap_strings(&curr->value, &curr->next->value);
			curr = beg;
		}
		else
			curr = curr->next;
	}
	change_token_regular(tree);
}
