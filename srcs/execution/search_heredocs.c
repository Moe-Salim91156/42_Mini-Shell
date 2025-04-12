/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/04/09 16:09:20 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

/*
 * lookup payloads array of args for (<<)
 * if found execute the heredoc function
 *  ::: heredoc function:
 *      1. iterate through each payload args;
 *      2. look for (<<) for heredoc;
 *      3. fill the buffer for heredoc for each payload,
	to be read by anything afterwards;
 *      4. thats it;
 *
 * */

int	search_in_args(t_cmd *payload)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (payload->payload_array[i])
	{
		if (!ft_strcmp(payload->payload_array[i], "<<"))
		{
			printf("here doc found in argv of %d\n", i);
			payload->here_doc_counts++;
			found = 1;
		}
		i++;
	}
	return (found);
}

int	locate_heredoc(t_cmd_list *cmd_list)
{
	t_cmd	*payload;

	payload = cmd_list->head;
	while (payload != NULL)
	{
		if (search_in_args(payload))
		{
			printf("here doc counts %d\n", payload->here_doc_counts);
			cmd_list->total_heredocs += payload->here_doc_counts;
		}
		payload = payload->next;
	}
	printf("total heredocs in all payloads %d\n", cmd_list->total_heredocs);
	return (0);

}
/*
 * filling the heredoc in each payload last one wins
 * if has quotes, no expansion inside and quotes removed from delimiter
 * if no quotes	, expanding content but not the delimiter
 * see_if_heredoc_quoted will be executed before expander, good fix 
 * a flag (quoted) will determine if we will expand content or nah
 * locate, fill, expand?, get executed if command
 *
 *
 *
 */

