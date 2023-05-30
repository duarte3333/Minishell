#include "../minishell.h"

void env_delete_element(t_env **lst)
{
	t_env *temp;

	temp = (*lst);
    if (lst && *lst)
    {
		if (!(*lst)->prev && !(*lst)->next)
			*lst = NULL;
		else if (!(*lst)->prev && (*lst)->next)
		{
			(*lst)->next->prev = NULL;
			*lst = (*lst)->next;
		}
		else if ((*lst)->prev && !(*lst)->next)
		{
			(*lst)->prev->next = NULL;
			*lst = (*lst)->prev;
		}
		else if ((*lst)->prev && (*lst)->next)
		{
			(*lst)->prev->next = (*lst)->next;
			(*lst)->next->prev = (*lst)->prev;
			*lst = (*lst)->prev;
		}
		if (temp->content)
			free(temp->content);
		free(temp);
    }
}

void	__exec_unset(char **env, t_list **lst)
{
	t_env	*lst_env_export;
	int		i;
	
	(void)env;
	i = 0;
	if (!(*lst)->content[1])
		return ;
	while ((*lst)->content[i])
	{
		lst_env_export = env_lst_search((*lst)->content[i]);
		printf("%s", lst_env_export->content);
		if (lst_env_export)
			env_delete_element(&lst_env_export);
		i++;
	}
}