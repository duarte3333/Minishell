/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:34:53 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 18:23:09 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_default(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

void	signals_here_doc(int sign)
{
	write(2, " ", 1);
	if (sign == SIGQUIT)
		SIG_IGN;
	else if (sign == SIGINT)
		exit(1);
}

void	handle_quit(int sign)
{
	pid_t	pid;
	int		status;

	(void)sign;
	pid = waitpid(-1, &status, 0);
	if (pid == -1)
		SIG_IGN ;
	else if (!g_data.hd)
	{
		write(1, "Quit (core dumped)\n", 20);
		return ;
	}
}

void	handle_sign(int sign)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (sign == SIGINT)
	{
		write(2, "^C", 2);
		write(2, "\n", 1);
		g_data.status = 130;
		if (g_data.hd)
		{
			g_data.interrupted = 1;
			return ;
		}
		if (pid == -1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
