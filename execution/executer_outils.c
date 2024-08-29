/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:21:08 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/21 03:22:08 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	checkers(t_tree *tree, t_env *env)
{
	if (!ft_strcmp(tree->value, "export"))
		return (ft_export(&env, tree), 1);
	else if (!ft_strcmp(tree->value, "echo"))
		return (ft_echo(tree), 1);
	else if (!ft_strcmp(tree->value, "exit"))
		return (ft_exit_b(tree), 1);
	else if (!ft_strcmp(tree->value, "cd"))
		return (ft_cd(tree, env), 1);
	else if (!ft_strcmp(tree->value, "unset"))
		return (ft_unset(&env, tree), 1);
	else if (!ft_strcmp(tree->value, "pwd"))
		return (ft_pwd(), 1);
	else if (!ft_strcmp(tree->value, "env"))
		return (ft_env(env), 1);
	else if ((ft_strchr(tree->value, ' ') || ft_strchr(tree->value, '\t'))
		&& g_global.flag == 1 && g_global.flag3 == 1)
		return (bye_bye1(tree->value), bye_bye1(": command not found\n"), 1);
	return (0);
}

void	cmd_exit_126(char *cmd)
{
	struct stat	info;

	stat(cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		bye_bye1(": Is a directory\n");
		free_garbage(&g_global.garbage_list);
		exit(126);
	}
	if (access(cmd, R_OK | X_OK) == -1)
	{
		bye_bye1(" Permission denied\n");
		free_garbage(&g_global.garbage_list);
		exit(126);
	}
	else
		bye_bye1(": command not found\n");
	free_garbage(&g_global.garbage_list);
	exit(127);
}

void	cmd_not_found(char *cmd)
{
	int	i;
	int	backslash;

	if (ft_strncmp(cmd, "'''", 3))
		bye_bye1(cmd);
	if (access(cmd, F_OK) == -1)
	{
		i = 0;
		backslash = 0;
		while (cmd[i])
			if (cmd[i++] == '/')
				backslash = 1;
		if (backslash)
			bye_bye1(": No such file or directory\n");
		else
			bye_bye1(": command not found\n");
		free_garbage(&g_global.garbage_list);
		exit(127);
	}
	return (cmd_exit_126(cmd));
}

void	forker(t_data *data)
{
	if (data->cmd_path)
		execve(data->cmd_path, data->cmd, data->envp);
	if (access(data->cmd[0], X_OK) == 0 && g_global.flag4 == 0)
		execve(data->cmd[0], data->cmd, data->envp);
	cmd_not_found(data->cmd[0]);
}

void	check1(t_tree *tree, t_data data)
{
	if (tree && tree->type == TOKEN_REDINPUT)
	{
		redinput(tree, NULL, data);
		tree = tree->next->next;
	}
	if (tree && tree->type == TOKEN_APPEND)
		append(tree, data);
}
