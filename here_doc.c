/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:58:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/16 11:41:42 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (s1 && s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_here_doc(t_list *lst, int i)
{
	char		*in;
	int			fd_in;

	fd_in = open(".temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_in == -1)
	{
		perror("");
		exit(0);
	}
	write(0, ">", 1);
	in = get_next_line(0);
	while (1)
	{
		if ((ft_strncmp(in, lst->content[i + 1], ft_strlen(lst->content[i + 1])) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(lst->content[i + 1])))
			break ;
		write(0, ">", 1);
		write(fd_in, in, ft_strlen(in));
		free(in);
		in = get_next_line(0);
	}
	free(in);
	return (fd_in);
}