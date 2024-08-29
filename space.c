/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:55:25 by younajja          #+#    #+#             */
/*   Updated: 2024/08/23 00:56:34 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c || c == '\0')
		return ((char *)s);
	else
		return (NULL);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = lenght(nbr);
	str = safe_malloc(len + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

char	*norm2(t_lexer *lexer, char *str)
{
	while (ft_printable(lexer->c) && lexer->c != '$' && lexer->c != '?')
	{
		if (lexer->c == '=')
		{
			if (!ft_strcmp(g_global.check, "export"))
				break ;
		}
		str = ft_strjoin(str, lexer_get_current_char_as_string(lexer));
		lexer_advance(lexer);
	}
	return (str);
}

void	norm3(t_tree *tree, t_env *env, t_data *data, t_tree *tmp)
{
	norminette(tree, env, data, data->joiner);
	if (checkers(tmp, env) == 1)
		return ;
	if (g_global.heredoc == 1 && g_global.status == 130)
		return ;
	fork_pid(data);
}

int	ambiguous(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (1);
	return (0);
}
