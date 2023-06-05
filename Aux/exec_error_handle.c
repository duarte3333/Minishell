/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:51:24 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/05 17:28:19 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao indica erro caso o comando seja um
diretorio e atualiza o respetivo exit code */
void	command_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	g_data.status = 127;
	return ;
}

/* Esta funcao indica erro caso o comando seja um
diretorio e atualiza o respetivo exit code */
void	is_a_directory(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	g_data.status = 126;
	return ;
}

/* Esta funcao esta a ser chamada caso o exeve falhe,
para definir qual o erro que fez o comando falhar. */
void	error_handle(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		command_not_found(cmd);
	else if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		is_a_directory(cmd);
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
	else
	{
		perror("");
		g_data.status = errno;
	}
}
