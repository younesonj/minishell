/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:23:56 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/22 23:09:14 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_sstrjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;

	if (!(s1 || s2))
		return (NULL);
	res = safe_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

char	*joiner(char *full_path, char *cmd)
{
	char	*path_with_slash;
	char	*res;

	path_with_slash = ft_sstrjoin(full_path, "/");
	res = ft_sstrjoin(path_with_slash, cmd);
	return (res);
}

char	*get_cmd_with_path(char *cmd, t_data *data)
{
	char	*full_cmd_path;

	data->i = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	if (cmd[0] == '.' || cmd[0] == '/')
		return (NULL);
	data->i = 0;
	if (!data->paths)
		return (NULL);
	while (data->paths[data->i] != NULL)
	{
		full_cmd_path = joiner(data->paths[data->i], cmd);
		if (access(full_cmd_path, X_OK) == 0)
			return (full_cmd_path);
		data->i++;
	}
	return (NULL);
}

void	initialize_variables(t_env *envp, t_data *data, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	data->cmd = ft_split(str, ' ');
	data->command = data->cmd[0];
	data->envp = env_to_array(envp);
	data->envp_paths = get_paths(envp);
	if (data->envp_paths)
		data->paths = ft_split(data->envp_paths + 5, ':');
	data->cmd_path = get_cmd_with_path(data->cmd[0], data);
}

void	fork_pid(t_data *data)
{
	int	status;

	if (g_global.ambiguous == 1 || g_global.redirect == 1)
		return ;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, ctr_back_slash);
	data->pid = fork();
	if (!ft_strncmp(data->command, "./", 2))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_mini);
	}
	if (data->pid == -1)
		return (bye_bye1("fork didn't work\n"));
	if (data->pid == 0)
		forker(data);
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.status = WTERMSIG(status) + 128;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
}
