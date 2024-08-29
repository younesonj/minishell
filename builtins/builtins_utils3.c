/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:49:29 by younajja          #+#    #+#             */
/*   Updated: 2024/08/17 22:24:34 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_exit_helper1(void)
{
	free_garbage(&g_global.garbage_list);
	printf("exit\n");
	exit(g_global.status);
}

void	ft_exit_helper2(char *s)
{
	int	i;

	i = 0;
	write(2, "exit\nminishell: exit: ", 22);
	while (s[i])
		write(2, &s[i++], 1);
	write(2, ": numeric argument required\n", 28);
	g_global.status = 2;
	free_garbage(&g_global.garbage_list);
	exit(2);
}

void	ft_exit_helper3(int nb)
{
	g_global.status = nb;
	free_garbage(&g_global.garbage_list);
	printf("exit\n");
	exit(nb);
}

void	ft_exit_helper4(int nb)
{
	g_global.status = nb % 256;
	free_garbage(&g_global.garbage_list);
	printf("exit\n");
	exit(nb % 256);
}

void	ft_exit_helper_5(void)
{
	g_global.status = 1;
	bye_bye1("exit\nminishell: exit: too many arguments\n");
}
