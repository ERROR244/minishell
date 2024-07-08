/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:38:01 by ksohail-          #+#    #+#             */
/*   Updated: 2024/07/08 19:04:45 by ksohail-         ###   ########.fr       */
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

char	**linked_list_to_array(t_env *list)
{
	char	**array;
	t_env	*current;
	int		count;
	int		i;

	i = 0;
	count = count_nodes(list);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		exit(EXIT_FAILURE);
	current = list;
	while (i < count)
	{
		array[i] = ft_strdup(current->var_name);
		if (array[i] == NULL)
		{
			perror("strdup");
			free_array(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
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
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(ptr[i], 1);
			ft_putchar_fd('\n', 1);
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
			|| str[i] == '+'))
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (0);
	return (1);
}

char	*fill_var(char *var, char *c)
{
	int j;
	char *str;

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
			export = ft_split(com[i], '=');
			if (export[0][ft_strlen(export[0]) - 1] == '+')
				export[0] = fill_var(export[0], &c);
			set_env_after_export(list, export, c, export_flag);
			free_array(export);
		}
		i++;
	}
}
