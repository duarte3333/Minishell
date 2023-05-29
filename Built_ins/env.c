/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:31:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/05/30 15:44:57 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
