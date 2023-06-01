/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/31 18:04:40 by dsa-mora         ###   ########.fr       */
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
