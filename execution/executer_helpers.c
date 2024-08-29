/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:15:22 by alamaoui          #+#    #+#             */
/*   Updated: 2024/08/20 02:12:03 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_lstsize(t_env *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char	**env_to_array(t_env *envp)
{
	char	**env;
	int		i;

	i = 0;
	env = safe_malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	if (!env)
	{
		bye_bye1("Malloc didn't work\n");
		return (NULL);
	}
	while (envp)
	{
		if (envp->env_line)
			env[i++] = envp->env_line;
		envp = envp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*get_paths(t_env *envp)
{
	char	*curr_env;

	g_global.flag4 = 0;
	if (!envp->env_line)
		g_global.flag4 = 1;
	while (envp)
	{
		curr_env = envp->env_line;
		if (ft_strncmp(envp->env_line, "PATH=", 5) == 0)
			return (curr_env);
		envp = envp->next;
	}
	return (NULL);
}

void	save_stdin_stdout(int *std_in, int *std_out)
{
	*std_in = dup(0);
	*std_out = dup(1);
}

void	restore_stdin_stdout(int std_in, int std_out)
{
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
}
