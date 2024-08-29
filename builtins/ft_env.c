/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:32:59 by younajja          #+#    #+#             */
/*   Updated: 2024/07/19 09:40:27 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	insert_env(t_env **list, char *s, char *key)
{
	t_env	*new;
	t_env	*curr;

	new = safe_malloc(sizeof(t_env));
	new->env_line = s;
	new->key = key;
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

char	*extract_key(char *env)
{
	int		i;
	char	*res;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	res = safe_malloc(i + 1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		res[i] = env[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_env	*env_to_list(char **env)
{
	int		i;
	t_env	*list;
	char	*key;

	i = 0;
	list = NULL;
	while (env[i])
	{
		key = extract_key(env[i]);
		insert_env(&list, env[i], key);
		i++;
	}
	return (list);
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->key && equal_detected(env->env_line))
			printf("%s\n", env->env_line);
		env = env->next;
	}
}

void	ft_unset(t_env **env, t_tree *tree)
{
	t_env	*curr;

	if (!tree->next)
		return ;
	tree = tree->next;
	while (tree)
	{
		curr = *env;
		while (curr)
		{
			if (tree->value && curr->key && !ft_strcmp(tree->value, curr->key))
			{
				curr->key = NULL;
				curr->env_line = NULL;
			}
			curr = curr->next;
		}
		tree = tree->next;
	}
}
