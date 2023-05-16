/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:42 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/16 15:42:18 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (1);
	else if(!ft_strcmp(str, ">>"))
		return (2);
	else if(!ft_strcmp(str, "<"))
		return (3);
	else if(!ft_strcmp(str, ">"))
		return (4);
	return (0);
}

int	redirect(char **division, int *i, t_list *pre_list)
{
	if (!ft_strcmp(division[*i], ">>"))
	{
		if (pre_list->fd_master[1] > 2)
			close(pre_list->fd_master[1]);
		free(division[*i]);
		pre_list->fd_master[1] = open(division[++(*i)], O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (!ft_strcmp(division[*i], "<<"))
	{
		if (pre_list->fd_master[0] > 2)
			close(pre_list->fd_master[0]);
		free(division[*i]);
		pre_list->fd_master[0] = ft_here_doc(division[++(*i)]);
	}
	else if (!ft_strcmp(division[*i], "<"))
	{
		if (pre_list->fd_master[0] > 2)
			close(pre_list->fd_master[0]);
		free(division[*i]);
		pre_list->fd_master[0] = open(division[++(*i)], O_RDONLY, 0644);
	}
	else if (!ft_strcmp(division[*i], ">"))
	{
		if (pre_list->fd_master[1] > 2)
			close(pre_list->fd_master[1]);
		free(division[*i]);
		pre_list->fd_master[1] = open(division[++(*i)], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	// if (pre_list->fd_master[0] == -1 || pre_list->fd_master[1] == -1 )
	// 	perror("");
}

int	redirection(t_list	*pre_list, char **division, char **env)
{
	int		i;
	int		j;
	t_list	*temp;

	i = -1;
	j = 0;
	temp = pre_list;
	while (division && division[++i])
	{
		if (division[i][0] == 3)
		{
			ft_lstadd_back(&pre_list, ft_lstnew(ft_matrixlen(&division[i + 1]), env));
			if (temp->next)
				temp = temp->next;
			j = 0;
		}
		else if (check_token(division[i]))
			redirect(division, &i, temp);
		else
		{
			temp->content[j] = ft_strdup(division[i]);
			j++;
		}
		free(division[i]);
	}
}

