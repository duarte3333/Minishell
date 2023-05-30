/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:31:12 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/24 17:24:59 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **env, char **cmd)
{
	char	**matrix;
	char	*temp;
	char	*res;
	int		i;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	matrix = ft_split(search_env(env, "PATH"), ':');
	res = ft_strjoin("/", cmd[0]);
	while (matrix[i])
	{
		temp = ft_strjoin(matrix[i], res);
		if (access(temp, X_OK) == 0)
		{
			free(res);
			res = temp;
			break ;
		}
		free(temp);
		i++;
	}
	ft_free_matrix(&matrix);
	return (res);
}
