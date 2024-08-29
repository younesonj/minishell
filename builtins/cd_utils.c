/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:54:10 by younajja          #+#    #+#             */
/*   Updated: 2024/07/22 21:41:51 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*current_pwd_env(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
			return (env->env_line);
		env = env->next;
	}
	return (NULL);
}

void	curr_to_old(t_env *env, char *curr)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			env->env_line = ft_strjoin("OLDPWD=", curr);
			break ;
		}
		env = env->next;
	}
}

void	curr_to_new(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			path_test_lhbal();
			env->env_line = ft_strjoin("PWD=", g_global.path);
		}
		env = env->next;
	}
}

void	ft_change_old_path(t_env *env)
{
	char	*s;
	int		i;
	char	*curr;

	s = current_pwd_env(env);
	if (!s)
		return ;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	curr = ft_substr(s, i + 1, ft_strlen(s));
	curr_to_old(env, curr);
	curr_to_new(env);
}
