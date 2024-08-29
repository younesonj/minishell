/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:40:26 by younajja          #+#    #+#             */
/*   Updated: 2024/07/20 21:24:07 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	equal_detected(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	handle_addition_found(t_env **env, char *s, int i)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(ft_substr(s, 0, i), curr->key))
		{
			if (equal_detected(curr->env_line) == 0)
				curr->env_line = ft_strjoin(curr->env_line, ft_substr(s, i + 1,
							ft_strlen(s)));
			else
				curr->env_line = ft_strjoin(curr->env_line, ft_substr(s, i + 2,
							ft_strlen(s)));
			return ;
		}
		curr = curr->next;
	}
}

void	handle_addition(t_env **env, t_tree *tree)
{
	char	*s;
	int		i;

	s = tree->value;
	i = 0;
	while (s[i] != '+' && s[i])
		i++;
	if (check_if_key_repeated(ft_substr(s, 0, i), env))
	{
		insert_env(env, ft_strjoin(ft_substr(s, 0, i), ft_substr(s, i + 1,
					ft_strlen(s))), ft_substr(s, 0, i));
	}
	else
		handle_addition_found(env, s, i);
}

void	write_export_line(char *s)
{
	int	i;
	int	flg;

	write(1, "declare -x ", 11);
	i = 0;
	flg = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		if (s[i] == '=' && !flg)
		{
			write(1, "\"", 1);
			flg = 1;
		}
		i++;
	}
	if (equal_detected(s))
		write(1, "\"", 1);
	write(1, "\n", 1);
}
