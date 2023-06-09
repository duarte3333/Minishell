/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 21:45:09 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_change(void)
{
	int				rc;
	struct termios	termios_new;

	rc = tcgetattr(0, &g_data.termios_save);
	if (rc)
	{
		perror("");
		return ;
	}
	termios_new = g_data.termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("");
		return ;
	}
}

int	error_here_doc(char *str)
{
	write(2, "warning: here-document at line 1 \
	delimited by end-of-file (wanted `", 67);
	write(2, str, ft_strlen(str));
	write(2, "')\n", 3);
	return (1);
}

void	ft_hd_child(char *str, int *fd)
{
	term_change();
	g_data.vars->env = ft_env_lst_to_arr(g_data.env);
	while (1)
	{
		write(0, ">", 1);
		g_data.vars->str = get_next_line(0);
		g_data.vars->str = chg_dollar(g_data.vars->str, g_data.vars->env);
		if (!g_data.vars->str && error_here_doc(str))
			break ;
		if ((ft_strncmp(g_data.vars->str, str, ft_strlen(str)) == 0) && \
			(ft_strlen(g_data.vars->str) - 1 == ft_strlen(str)))
			break ;
		write(fd[1], g_data.vars->str, ft_strlen(g_data.vars->str));
		free(g_data.vars->str);
		g_data.vars->str = NULL;
	}
	ft_free_env(&g_data.env);
	free_vars();
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

/* Esta realiza o comportamento do comando << no bash */
int	ft_here_doc(char *str)
{
	int	fd[2];
	int	status;

	status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_here_doc);
	g_data.hd = 1;
	if (pipe(fd) == -1)
		perror("");
	if (fork() == 0)
		ft_hd_child(str, fd);
	signals_default();
	close(fd[1]);
	waitpid(0, &status, 0);
	g_data.hd = 0;
	return (fd[0]);
}
