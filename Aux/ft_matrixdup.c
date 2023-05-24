/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:56:18 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/24 16:08:23 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_matrixdup(char **matrix)
{
	char	**res;
	int		i;

	i = -1;
	while (matrix[++i])
		;
	res = ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	while (matrix[++i])
		res[i] = ft_strdup(matrix[i]);
	return (res);
}

/* int	main()
{
	char *str = "ola eu sou o tiago";
	char **matrix = ft_split(str, ' ');
	char **res = NULL;

	res = ft_matrixdup(matrix);
	int i = -1;
	while (res[++i])
		printf("%s\n", res[i]);
} */