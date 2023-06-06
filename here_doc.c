/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/06/06 15:46:45 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	our_env = ft_env_lst_to_arr(g_data.env);
	if (pipe(fd) == -1)
		perror("");
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
	free(in);
	close(fd[1]);
	return (fd[0]);
}
