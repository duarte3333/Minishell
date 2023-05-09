/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:31:12 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/09 19:42:12 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env && ft_strncmp(env[i], "PATH", 4))
		i++;
	return (env[i]);
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
	matrix = ft_split(get_path(env), ':');
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

/* int main(int ac, char **av, char **env)
{
	char *big_path;
	(void)ac;

	big_path = get_path(env);
	int i = 1;
	while (av[i])
	{
		printf("cmd: %s\n", av[i]);
		printf("path do cmd: %s\n", get_cmd_path(big_path, &av[i]));
		i++;
	}
} */
