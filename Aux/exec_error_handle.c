/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/01 12:36:55 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	error_handle(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[i] || !cmd)
	{
		write(2, "Permission denied\n", 18);
		return ;
	}
	else if (access(cmd, X_OK) == 0)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": is a directory\n", 17);
		g_data.status = 126;
		return ;
	}
	else
	{
		write(2, "command not found: ", 19);
		while (cmd[i])
		{
			write(2, &(cmd[i]), 1);
			i++;
		}
		write(2, "\n", 1);
		g_data.status = 127;
		return ;
	}
	perror("");
	g_data.status = errno;
}
