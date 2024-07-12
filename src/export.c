/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/12 15:41:01 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**sortexport(char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
	return (arr);
}

int	printmyexport(t_env *list)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = linked_list_to_array(list);
	while (ptr[i])
		i++;
	sortexport(ptr, i);
	i = 0;
	while (ptr[i])
	{
		if (ptr[i][0] == '_' && ptr[i][1] == '=')
			i++;
		else
		{
			printf("declare -x ");
			print_value(ptr[i]);
			i++;
		}
	}
	free_array(ptr);
	return (0);
}

int	ft_all_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) == 1 || str[i] == '_'
			|| str[i] == '+' || str[i] == '	'))
	{
		if (str[i] == '	')
			str[i] = '	';
		i++;
	}
	if ((str[i] == '=' && i != 0) || str[i] == '\0')
		return (0);
	return (1);
}

char	*fill_var(char *var, char *c)
{
	char	*str;
	int		j;

	*c = '+';
	str = malloc(sizeof(char) * ft_strlen(var));
	j = -1;
	while (++j >= 0 && var[j] != '+')
		str[j] = var[j];
	str[j] = '\0';
	free(var);
	return (str);
}

void	export(t_env *list, char **com, char c, int i)
{
	char	**export;
	bool	export_flag;

	if (com[1] == NULL && printmyexport(list) == 0)
		return ;
	while (com[i])
	{
		c = '-';
		export_flag = false;
		if (ft_all_isalpha(com[i]) == 1)
			printf("export: '%s' :not a valid identifier\n", com[i]);
		else
		{
			if (com[i][ft_strlen(com[i]) - 1] == '=')
				export_flag = true;
			export = get_key_and_value(com[i], NULL, 0, 0);
			if (export[0][ft_strlen(export[0]) - 1] == '+')
				export[0] = fill_var(export[0], &c);
			set_env_after_export(list, export, c, export_flag);
			free_array(export);
		}
		i++;
	}
}
