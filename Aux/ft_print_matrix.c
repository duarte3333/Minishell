/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:58:34 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 20:19:19 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao da print de uma matriz */
void	ft_print_matrix(char **array)
{
	if (array == NULL)
		return ;
	while (*array != NULL)
	{
		printf("%s\n", *array);
		array++;
	}
}
