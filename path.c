/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:31:12 by mtiago-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/30 15:48:19 by mtiago-s         ###   ########.fr       */
=======
/*   Updated: 2023/05/25 17:10:10 by mtiago-s         ###   ########.fr       */
>>>>>>> 1d81de9 (handle of dollar signs starts)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(char **env, char *str)
{
	int	i;
	char	*temp;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], str, ft_strlen(str)))
		i++;
	if (!env[i] || !str || !*str)
		return ("");
	temp = (env[i] + ft_strlen(str));
	if (*temp == '=')
		temp++;
	return (temp);
}

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
