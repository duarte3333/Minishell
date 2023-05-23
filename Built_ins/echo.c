#include "../minishell.h"

void	print_matrix(char **str)
{
	int i;

	i = 0;
	while (str[++i])
		printf("%s", str[i]);
}

void	__exec_echo(char **env, t_list **lst)
{
	int 	i;
	char	*temp; 

	i = -1;
	(void)env; 
	if ((*lst)->content[1][0] == '-')
	{
		temp = ((*lst)->content[1]);
		((*lst)->content[1])++;
		printf("[oi] %s\n", (*lst)->content[1]);
		while ((*lst)->content[1][++i] && (*lst)->content[1][++i] != '\n')
		{
			if ((*lst)->content[1][i] == 'n')
				i++;
			else
			{
				break ;
			}
		}
		print_matrix((*lst)->content);
	}
	else
		print_matrix((*lst)->content);
	printf("\n");
}
