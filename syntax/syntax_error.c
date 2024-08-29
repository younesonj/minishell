/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:29:40 by younajja          #+#    #+#             */
/*   Updated: 2024/07/19 10:43:02 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	check_pipe(t_token **token)
{
	t_token	*curr;

	curr = *token;
	if (curr->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	while (curr->next)
	{
		if (curr->type == TOKEN_PIPE && curr->next->type == TOKEN_PIPE)
		{
			printf("minishell: syntax error\n");
			return (1);
		}
		curr = curr->next;
	}
	if (curr->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}

int	check_redirections(t_token **token)
{
	t_token	*curr;

	curr = *token;
	while (curr->next)
	{
		if (curr->type != TOKEN_WORD && curr->type != TOKEN_PIPE
			&& curr->next->type != TOKEN_WORD)
		{
			printf("minishell: syntax error\n");
			return (1);
		}
		curr = curr->next;
	}
	if (curr->type != TOKEN_WORD)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}

int	check_syntax_errors(t_token **token)
{
	if (*token && (check_redirections(token) || check_pipe(token)))
	{
		g_global.status = 2;
		return (0);
	}
	return (1);
}
