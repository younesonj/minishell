/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:37:53 by alamaoui          #+#    #+#             */
/*   Updated: 2024/05/23 18:49:09 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_printable(int i)
{
	return ((i > 32 && i < 127) && i != '"' && i != '\'' && i != '>' && i != '<'
		&& i != '|');
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)safe_malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = safe_malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

void	bye_bye1(char *str)
{
	if (!ft_strcmp(str, "minishell: ambiguous redirect\n"))
		g_global.status = 1;
	write(2, str, ft_strlen(str));
}

void	double_quote_condition(t_lexer *lexer, t_env *env)
{
	if (lexer->c == '"')
	{
		g_global.if_single = 0;
		lexer_advance(lexer);
		double_quote(lexer, env);
		lexer->remember = lexer->i;
	}
}
