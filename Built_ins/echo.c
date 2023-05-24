#include "../minishell.h"

void	print_matrix(char **str)
{
	int i;

	i = 0;
	while (str[++i])
		printf("%s", str[i]);
}

int	is_a_n(char letter)
{
	if (letter == 'n')
		return (1);
	return (0);
}

void	__exec_echo(char **env, t_list **lst)
{
	int 	i;
	int		flag;

	flag = 0;
	i = -1;
	(void)env; 
	if ((*lst)->content[1][0] == '-')
	{
		while ((*lst)->content[1][++i])
		{
			if (is_a_n((*lst)->content[1][i]))
				i++;
			else
			{
				flag++;
				break;
			}
		}
		flag = 2;
	}
	if (flag == 1)
		print_matrix((*lst)->content);
	else if (flag == 2)
		print_matrix(++((*lst)->content));
	if (!flag || flag == 2)
		printf("\n");
}
