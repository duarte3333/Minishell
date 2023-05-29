/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:31:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/29 19:33:53 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_envlast(*lst);
			ft_envlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*ft_envnew(char *str)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = str;
	return (new);
}

void	ft_free_env(t_env **lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*res;

	i = -1;
	res = NULL;
	while(env[++i])
		ft_envadd_back(&res, ft_envnew(ft_strdup(env[i])));
	return (res);
}

void	__exec_env(char **env, t_list **lst)
{
	(void)env;
	(void)lst;
	while (g_data.env && g_data.env->content)
	{
		printf("%s\n", g_data.env->content);
		if (!g_data.env->next)
			break ;
		g_data.env = g_data.env->next;
	}
	//go_head(lst);
	//ft_free_list(lst);
	env_go_head(&g_data.env);
}
