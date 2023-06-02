/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/02 15:37:05 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	error_handle(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_strchr(cmd, '/'))
	{	
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found: ", 19);
		g_data.status = 127;
		return ;
	}
	else if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 17);
		g_data.status = 126;
		return ;
	}
	else if (access(cmd, F_OK) != 0)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		g_data.status = 127;
		return ;
	}
	else if (access(cmd, X_OK))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 20);
		g_data.status = 126;
		return ;
	}
	perror("");
	g_data.status = errno;
}
