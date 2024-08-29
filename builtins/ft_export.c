/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:30:37 by younajja          #+#    #+#             */
/*   Updated: 2024/08/17 23:28:11 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key)
			write_export_line(env->env_line);
		env = env->next;
	}
}

int	check_key(char *s)
{
	int	i;

	i = 1;
	if (!(s[0] >= 'a' && s[0] <= 'z') && !(s[0] >= 'A' && s[0] <= 'Z')
		&& s[0] != '_')
		return (0);
	if (s[i] == '=')
		return (1);
	while (i + 1 < ft_strlen(s) && s[i + 1] != '=')
	{
		if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= '0' && s[i] <= '9')
			&& !(s[i] >= 'A' && s[i] <= 'Z') && s[i] != '_')
			return (0);
		i++;
	}
	if (i + 1 < ft_strlen(s) && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= '0'
			&& s[i] <= '9') && !(s[i] >= 'A' && s[i] <= 'Z') && s[i] != '+'
		&& s[i] != '_' && s[i + 1] == '=')
		return (0);
	else if (i + 1 < ft_strlen(s) && s[i] == '+')
		return (2);
	else if (i + 1 == ft_strlen(s) && !(s[i] >= 'a' && s[i] <= 'z')
		&& !(s[i] >= 'A' && s[i] <= 'Z') && s[i] != '_')
		return (0);
	return (1);
}

int	check_if_key_repeated(char *s, t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, s))
			return (0);
		curr = curr->next;
	}
	return (1);
}

void	handle_regular(t_env **env, t_tree *tree)
{
	char	*s;
	int		i;
	t_env	*curr;

	s = tree->value;
	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	if (check_if_key_repeated(ft_substr(s, 0, i), env))
		insert_env(env, ft_strjoin(ft_substr(s, 0, i), ft_substr(s, i,
					ft_strlen(s))), ft_substr(s, 0, i));
	else
	{
		curr = *env;
		while (curr)
		{
			if (!ft_strcmp(ft_substr(s, 0, i), curr->key))
			{
				if (equal_detected(s))
					curr->env_line = s;
				return ;
			}
			curr = curr->next;
		}
	}
}

void	ft_export(t_env **env, t_tree *tree)
{
	t_tree	*curr;

	if (!tree->next)
		return (print_export(*env));
	curr = tree->next;
	while (curr)
	{
		if (!check_key(curr->value))
		{
			g_global.status = 1;
			printf("minishell: export: '%s': not a valid identifier\n",
				curr->value);
		}
		else if (check_key(curr->value) == 2)
			handle_addition(env, curr);
		else if (check_key(curr->value) == 1)
			handle_regular(env, curr);
		curr = curr->next;
	}
}
