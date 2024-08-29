/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:00 by younajja          #+#    #+#             */
/*   Updated: 2024/08/23 00:42:39 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_exit_b(t_tree *tree)
{
	int	nb;

	if (!tree->next)
		ft_exit_helper1();
	tree = tree->next;
	if (tree->type != TOKEN_WORD)
		return ;
	if (!check_digit(tree->value))
		ft_exit_helper2(tree->value);
	if (tree->next)
		return (ft_exit_helper_5());
	nb = ft_atoi(tree->value);
	if (nb >= 0 && nb <= 255)
		ft_exit_helper3(nb);
	else if (nb > 255)
		ft_exit_helper4(nb);
	else
	{
		g_global.status = (256 + nb) % 256;
		free_garbage(&g_global.garbage_list);
		printf("exit\n");
		exit((256 + nb) % 256);
	}
}

char	*cd_serch_home(t_env *envp, char *str)
{
	char	*curr_env;

	str = ft_strjoin(str, "=");
	while (envp)
	{
		curr_env = envp->env_line;
		if (ft_strncmp(envp->env_line, str, ft_strlen(str)) == 0)
			return (ft_substr(curr_env, 5, ft_strlen(curr_env)));
		envp = envp->next;
	}
	return (NULL);
}

void	ft_cd(t_tree *tree, t_env *env)
{
	if (!tree->next || !ft_strcmp(tree->next->value, "~"))
	{
		if (check_if_key_repeated("HOME", &env))
			return (bye_bye1("HOME NOT SET\n"));
		if (chdir(cd_serch_home(env, "HOME")))
			return (perror("minishell 	:cd "));
		ft_change_old_path(env);
		return ;
	}
	tree = tree->next;
	if (tree->next)
	{
		g_global.status = 1;
		return (bye_bye1("minishell: cd: too many arguments\n"));
	}
	if (chdir(tree->value))
	{
		g_global.status = 1;
		printf("minishell: cd: %s: No such file or directory\n", tree->value);
	}
	else
		ft_change_old_path(env);
}
