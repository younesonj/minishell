/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:50:36 by younajja          #+#    #+#             */
/*   Updated: 2024/08/21 01:00:12 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		g_global.status = 130;
	}
}

void	ctr_back_slash(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
}

void	sig_hand(int sig)
{
	(void)sig;
	printf("\n");
}

int	*return_value(void)
{
	static int	i = -1;

	return (&i);
}

void	signal_mini(int signal)
{
	(void)signal;
}
