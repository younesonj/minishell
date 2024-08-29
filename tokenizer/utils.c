/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:42:52 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/16 19:59:06 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_next_word(const char **s, char c)
{
	const char	*start;
	const char	*end;
	char		*wd;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	end = *s;
	wd = ft_substr(start, 0, end - start);
	return (wd);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	res = (char **)safe_malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = get_next_word(&s, c);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_normin(t_lexer *lexer, t_env *env)
{
	if (lexer->c == '"' && g_global.if_single == 0)
		lexer_advance(lexer);
	if (lexer->c == '$')
	{
		g_global.if_single = 1;
		double_quote(lexer, env);
	}
	if (lexer->c == '"')
		double_quote_condition(lexer, env);
}

void	double_quote(t_lexer *lexer, t_env *env)
{
	char	*str;

	while (lexer->c && lexer->c != '"')
	{
		g_global.flag3 = 1;
		if (g_global.checker == 1)
		{
			if (lexer->c == '$' && ft_printable(lexer->content[lexer->i + 1]))
			{
				str = if_dollar(lexer, env, lexer->value);
				if (str)
					lexer->value = ft_strjoin(NULL, str);
				continue ;
			}
		}
		if (lexer->c)
			lexer->value = ft_strjoin(lexer->value,
					lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	ft_normin(lexer, env);
}
