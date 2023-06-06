/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:06:56 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/06 14:26:39 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_matrix(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (str[j])
		j++;
	while (str[i])
	{
		if ((i + 1) != j)
			printf("%s ", str[i]);
		else
			printf("%s", str[i]);
		i++;
	}
}

int	is_a_n(char letter)
{
	if (letter == 'n')
		return (1);
	return (0);
}

/* Esta funcao realiza a opcao -n */
void	option_in_echo(t_list **lst, int *flag)
{
	int	i;

	i = 1;
	while ((*lst)->content[1][i])
	{
		if (!(is_a_n((*lst)->content[1][i])))
		{
			(*flag)++;
			break ;
		}
		i++;
	}
	if (!(*flag))
		(*flag) = 2;
}

/* Esta funcao replica o comando echo do bash,
incluindo a opcao -n que remova a quebra de linha*/
void	__exec_echo(t_list **lst)
{
	int	flag;

	flag = 0;
	close_fds(lst, 1);
	if ((*lst)->content[1] && (*lst)->content[1][0] \
		== '-' && (*lst)->content[1][1])
		option_in_echo(lst, &flag);
	if (flag == 1 || !flag)
	{
		print_matrix((*lst)->content, 1);
		printf("\n");
	}
	else if (flag == 2)
		print_matrix((*lst)->content, 2);
	g_data.status = 0;
}
