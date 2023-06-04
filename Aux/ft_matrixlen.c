/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:57:57 by duarte33          #+#    #+#             */
/*   Updated: 2023/06/04 20:19:05 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Calcula o size de uma variavel do tipo char** */
int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix[i][0] != 3)
		i++;
	return (i);
}
