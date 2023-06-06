/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 18:59:00 by mtiago-s         ###   ########.fr       */
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

/* Esta realiza o comportamento do comando << no bash */
int	ft_here_doc(char *str)
{
	char		*in;
	int			fd[2];
	char		**our_env;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_here_doc);
	g_data.hd = 1;
	if (pipe(fd) == -1)
		perror("");
	if (fork() == 0)
	{
		term_change();
		our_env = ft_env_lst_to_arr(g_data.env);
		while (1)
		{
			write(0, ">", 1);
			in = get_next_line(0);
			in = chg_dollar(in, our_env);
			if (!in && error_here_doc(str))
				break ;
			if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
				(ft_strlen(in) - 1 == ft_strlen(str)))
				break ;
			write(fd[1], in, ft_strlen(in));
			free(in);
		}
		ft_free_matrix(&our_env);
		ft_free_env(&g_data.env);
		free(in);
		close(fd[1]);
		close(fd[0]);
		exit(0);
	}
	signals_default();
	close(fd[1]);
	int status = 0;
	waitpid(0, &status, 0);
	g_data.hd = 0;
	return (fd[0]);
}
