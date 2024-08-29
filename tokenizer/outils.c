/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:11:51 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/02 00:50:37 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*check_for_dquote(t_lexer *lexer, t_env *env, char *value)
{
	if (g_global.expander == 0)
		g_global.flag = 1;
	lexer_advance(lexer);
	while (lexer->c && lexer->c != '"')
	{
		if (lexer->c == '$')
			value = if_dollar(lexer, env, value);
		value = ft_strjoin(value, lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (value);
}

char	*check_for_squote(t_lexer *lexer, char *value)
{
	if (g_global.expander == 0)
		g_global.flag = 1;
	lexer_advance(lexer);
	while (lexer->c && lexer->c != '\'')
	{
		value = ft_strjoin(value, lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (value);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)safe_malloc(2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
