/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:31:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/06/06 18:30:41 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Esta funcao cria a linked list do tipo t_env
com todas as variaveis ambiente*/
t_env	*get_env(char **env)
{
	int		i;
	t_env	*res;

	i = -1;
	res = NULL;
	while (env[++i])
		ft_envadd_back(&res, ft_envnew(ft_strdup(env[i])));
	return (res);
}

/* Esta funcao replica o comando env do bash, 
dando print a todas as variaveis de ambiente*/
void	__exec_env(t_list **lst)
{
	(void)lst;
	if (lst && (*lst)->content[1])
	{
		write(2, "env: '", 6);
		write(2, (*lst)->content[1], ft_strlen((*lst)->content[1]));
		write(2, "': No such file or directory\n", 29);
		g_data.status = 127;
		return ;
	}
	while (g_data.env && g_data.env->content)
	{
		if (ft_strchr(g_data.env->content, '='))
			printf("%s\n", g_data.env->content);
		if (!g_data.env->next)
			break ;
		g_data.env = g_data.env->next;
	}
	env_go_head(&g_data.env);
	g_data.status = 0;
}
