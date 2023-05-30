#include "../minishell.h"

char	*search_env(char **env, char *str)
{
	int	i;
	char	*temp;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], str, ft_strlen(str)))
		i++;
	if (!env[i] || !str || !*str)
		return ("");
	temp = (env[i] + ft_strlen(str));
	if (*temp == '=')
		temp++;
	return (temp);
}

int	ft_env_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}