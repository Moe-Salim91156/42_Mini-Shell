/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:28:35 by yokitane          #+#    #+#             */
/*   Updated: 2025/03/05 17:55:58 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_sorted_array(t_envp **arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (arr[i]->key[j] != '=' && arr[i]->key[j])
		{
			ft_putchar_fd(arr[i]->key[j], STDOUT_FILENO);
			j++;
		}
		if (arr[i]->value)
		{ // can use a single print statment,was causing me problems,need to test on cluster device.ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

static void	sort_env_array(t_envp **arr, int size)
{
	int		i;
	int		j;
	t_envp	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static t_envp	**create_env_array(t_envp *list, int size)
{
	t_envp	**arr;
	t_envp	*current;
	int		i;

	arr = malloc(sizeof(t_envp *) * size);
	if (!arr)
		return (NULL);
	current = list;
	i = 0;
	while (current && i < size)
	{
		arr[i] = current;
		current = current->next;
		i++;
	}
	return (arr);
}
/* counts all keys, regardless of values. */
static int	envp_count_all(t_envp *list)
{
	int		count;
	t_envp	*traverse;

	count = 0;
	traverse = list;
	while (traverse)
	{
		count++;
		traverse = traverse->next;
	}
	return (count);
}

int	print_env_sorted(t_envp *list)
{
	t_envp	**sorted_arr;
	int		total_env;

	if (!list)
		return (1);
	total_env = envp_count_all(list);
	sorted_arr = create_env_array(list, total_env);
	if (!sorted_arr)
		return (1);
	sort_env_array(sorted_arr, total_env);
	print_sorted_array(sorted_arr, total_env);
	free(sorted_arr);
	return (0);
}
