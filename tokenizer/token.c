/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:13:50 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/21 03:01:46 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_token	*lexer_collect_word(t_lexer *lexer, t_env *env)
{
	char	*value;

	value = NULL;
	while (ft_printable(lexer->c) || lexer->c == '"' || lexer->c == '\'')
	{
		if (g_global.checker == 1)
		{
			g_global.flag2 = 1;
			if (lexer->c == '$' && ft_printable(lexer->content[lexer->i + 1]))
				value = if_dollar(lexer, env, value);
		}
		if (lexer->c == ' ' || lexer->c == '\t')
			break ;
		if (ft_printable(lexer->c))
			value = ft_strjoin(value, lexer_get_current_char_as_string(lexer));
		if (lexer->c == '"')
			value = check_for_dquote(lexer, env, value);
		if (lexer->c == '\'')
			value = check_for_squote(lexer, value);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_WORD, value));
}

t_token	*lexer_collect_string(t_lexer *lexer, t_env *env)
{
	lexer->value = NULL;
	while (ft_printable(lexer->c) || lexer->c == '"' || lexer->c == '\'')
	{
		if (ft_printable(lexer->c))
		{
			while (lexer->c && ft_printable(lexer->c))
			{
				lexer->value = ft_strjoin(lexer->value,
						lexer_get_current_char_as_string(lexer));
				lexer_advance(lexer);
				lexer->remember = lexer->i;
			}
		}
		double_quote_condition(lexer, env);
		if (lexer->c == '\'')
		{
			back_slash(lexer, env);
			lexer->remember = lexer->i;
		}
		if (lexer->c == ' ' || lexer->c == '\t')
			return (init_token(TOKEN_WORD, lexer->value));
	}
	lexer->i = lexer->remember;
	return (init_token(TOKEN_WORD, lexer->value));
}

t_token	*lexer_collect_squote(t_lexer *lexer, t_env *env)
{
	lexer->value = NULL;
	while (ft_printable(lexer->c) || lexer->c == '"' || lexer->c == '\'')
	{
		if (ft_printable(lexer->c))
		{
			while (ft_printable(lexer->c))
			{
				lexer->value = ft_strjoin(lexer->value,
						lexer_get_current_char_as_string(lexer));
				lexer_advance(lexer);
				lexer->remember = lexer->i;
			}
		}
		if (lexer->c == '\'')
		{
			back_slash(lexer, env);
			lexer->remember = lexer->i;
		}
		if (lexer->c == ' ' || lexer->c == '\t')
			return (init_token(TOKEN_WORD, lexer->value));
		double_quote_condition(lexer, env);
	}
	lexer->i = lexer->remember;
	return (init_token(TOKEN_WORD, lexer->value));
}

t_token	*others(t_lexer *lexer, t_env *env)
{
	if (lexer->c == '"')
	{
		if (g_global.expander == 0)
			g_global.flag = 1;
		return (lexer_collect_string(lexer, env));
	}
	if (lexer->c == '\'')
	{
		if (g_global.expander == 0)
			g_global.flag = 1;
		return (lexer_collect_squote(lexer, env));
	}
	if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer, init_token(TOKEN_HERDOC,
					"<<")));
	}
	if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer, init_token(TOKEN_APPEND,
					">>")));
	}
	return (NULL);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_env *env)
{
	t_token	*token;

	g_global.flag2 = 0;
	while (lexer->c)
	{
		token = others(lexer, env);
		if (token)
			return (token);
		if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
						"|")));
		if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDOUTPUT,
						">")));
		if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_REDINPUT,
						"<")));
		if (ft_printable(lexer->c))
			return (lexer_collect_word(lexer, env));
		lexer_advance(lexer);
	}
	return (NULL);
}
