/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mossa3id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:19:26 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/20 03:54:27 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	insert(t_token **list, t_token *token)
{
	t_token	*curr;

	curr = *list;
	if (!(*list))
	{
		*list = token;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = token;
}

int	count_pipe(t_token *res)
{
	int	count;

	count = 0;
	while (res)
	{
		if (res->type == TOKEN_PIPE)
			count++;
		res = res->next;
	}
	return (count);
}

int	check_syntax_error_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				return (0);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}

void	path_test_lhbal(void)
{
	char	s[1024];

	if (getcwd(s, sizeof(s)))
		g_global.path = ft_strdup(s);
}

char	*check(char *value)
{
	if (!value)
		return ("'''");
	return (value);
}
