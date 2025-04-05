/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:29:25 by msalim            #+#    #+#             */
/*   Updated: 2025/04/05 19:07:23 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"


/*
 * lookup payloads array of args for (<<)
 * if found execute the heredoc function
 *  ::: heredoc function: 
 *      1. iterate through each payload args; 
 *      2. look for (<<) for heredoc;
 *      3. fill the buffer for heredoc for each payload, to be read by anything afterwards;
 *      4. thats it;
 *
 * */

