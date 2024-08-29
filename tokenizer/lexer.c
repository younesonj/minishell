/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:55:47 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/04 23:29:12 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_isalnum(int i)
{
	return ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0'
			&& i <= '9'));
}

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)safe_malloc(sizeof(t_lexer));
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	for_expand(t_lexer *lexer, t_env *env)
{
	char	*str;

	if (lexer->c == '$' && ft_printable(lexer->content[lexer->i + 1]))
	{
		str = if_dollar(lexer, env, lexer->value);
		if (str)
			lexer->value = ft_strjoin(NULL, str);
	}
}

void	back_slash(t_lexer *lexer, t_env *env)
{
	lexer_advance(lexer);
	while (lexer->c && lexer->c != '\'')
	{
		if (lexer->c)
			lexer->value = ft_strjoin(lexer->value,
					lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	if (lexer->c == '$')
		for_expand(lexer, env);
	if (lexer->c == '\'')
		back_slash(lexer, env);
}
