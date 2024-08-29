/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:56:16 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/20 03:54:21 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*expand(t_env *envp, char *str)
{
	char	*curr_env;

	if (!envp)
	{
		bye_bye1("PATH environment is not found\n");
		return (NULL);
	}
	str = ft_strjoin(str, "=");
	while (envp)
	{
		curr_env = envp->env_line;
		if (ft_strncmp(envp->env_line, str, ft_strlen(str)) == 0)
			return (curr_env);
		envp = envp->next;
	}
	return (NULL);
}

char	*norm(t_lexer *lexer, char *str)
{
	while (lexer->c && ft_printable(lexer->c))
	{
		if ((lexer->c == '$' && lexer->content[lexer->i + 1])
			|| (lexer->c == '$' && lexer->content[lexer->i + 1] != '"'))
			break ;
		str = ft_strjoin(str, lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (str);
}

char	*expander(t_lexer *lexer, char *value)
{
	char	*string;

	string = NULL;
	g_global.flag3 = 0;
	lexer_advance(lexer);
	if (lexer->c == '?')
	{
		value = ft_strjoin(value, ft_itoa(g_global.status));
		lexer_advance(lexer);
		if (lexer->c)
		{
			string = norm2(lexer, string);
			if (string)
				value = ft_strjoin(value, string);
		}
	}
	return (value);
}

char	*test_echo(char *value, int i)
{
	char	**resl;

	if (g_global.flag2 == 1)
	{
		if (!value)
			return (check(value));
		while (value[i])
		{
			if (value[i] == '\t')
				value[i] = ' ';
			i++;
		}
		resl = ft_split(value, ' ');
		i = 0;
		value = NULL;
		while (resl[i])
		{
			value = ft_strjoin(value, resl[i]);
			i++;
			if (resl[i])
				value = ft_strjoin(value, " ");
		}
	}
	return (value);
}

char	*if_dollar(t_lexer *lexer, t_env *env, char *value)
{
	char	**res;

	if ((lexer->c == '$' && lexer->content[lexer->i + 1] == '\0')
		|| (lexer->c == '$' && lexer->content[lexer->i + 1] == '"'))
		value = ft_strjoin(value, "$");
	lexer->str = NULL;
	lexer->string = NULL;
	value = expander(lexer, value);
	if (lexer->c == '$' && lexer->content[lexer->i + 1] == '?')
		value = expander(lexer, value);
	lexer->str = norm2(lexer, lexer->str);
	lexer->tmp = expand(env, lexer->str);
	if (lexer->tmp)
	{
		res = ft_split(lexer->tmp + ft_strlen(lexer->str) + 1, '\0');
		value = ft_strjoin(value, res[0]);
	}
	if (lexer->c == '$')
	{
		lexer->string = if_dollar(lexer, env, NULL);
		if (lexer->string)
			value = ft_strjoin(value, lexer->string);
	}
	value = test_echo(value, 0);
	return (value);
}
