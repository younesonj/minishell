/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:31:44 by younajja          #+#    #+#             */
/*   Updated: 2024/08/20 23:22:42 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	calcul_height_three(t_tree *tree)
{
	int	i;

	if (!tree)
		return (0);
	i = 1;
	while (tree->left)
	{
		tree = tree->left;
		i++;
	}
	return (i);
}

int	check_new_line(char *s)
{
	int	i;

	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

void	print_arg_echo_helper(t_tree *tree)
{
	while (tree && tree->type == TOKEN_WORD)
	{
		if (!ft_strcmp(tree->value, "''"))
		{
			if (g_global.flag3 == 1)
				write(1, "''", 2);
			return ;
		}
		if (!ft_strcmp(tree->value, "'''"))
		{
			if (g_global.flag == 1)
				write(1, "'''", 3);
			return ;
		}
		write(1, tree->value, ft_strlen(tree->value));
		if (tree->next && tree->next->type == TOKEN_WORD)
			write(1, " ", 1);
		tree = tree->next;
	}
}

void	ft_echo(t_tree *tree)
{
	int	flg;

	if (!tree->next)
	{
		write(1, "\n", 1);
		return ;
	}
	tree = tree->next;
	flg = 0;
	while (tree->value && tree->value[0] == '-')
	{
		if (!check_new_line(tree->value))
			break ;
		tree = tree->next;
		flg = 1;
		if (!tree)
			break ;
	}
	print_arg_echo_helper(tree);
	if (!flg)
		write(1, "\n", 1);
	g_global.status = 0;
}

void	ft_pwd(void)
{
	char	s[1024];

	if (getcwd(s, sizeof(s)))
		printf("%s\n", s);
	else
		printf("%s\n", g_global.path);
}
