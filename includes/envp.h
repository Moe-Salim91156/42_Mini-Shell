/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:33:34 by yokitane          #+#    #+#             */
/*   Updated: 2025/02/17 17:07:37 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

typedef struct s_envp
{
	char	*content;
	struct s_envp	*next;
}	t_envp;

t_envp	*init_envp(char **envp);


#endif