/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:31:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/24 16:40:56 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	__exec_env(char **env, t_list **lst)
{
	int	i;
	
	i = -1;
	close(lst->fd[0]);
	close((*lst)->fd[1]);
	if ((*lst)->fd_master[1] > 2)
		close((*lst)->fd_master[1]);
	if ((*lst)->fd_master[0] > 2)
		close((*lst)->fd_master[0]);
	while (g_data.env[++i])
		printf("%s\n", g_data.env[i]);
	go_head((*lst));
	ft_free_list((*lst));
	exit(0);
}
