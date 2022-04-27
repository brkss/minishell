/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:26:37 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/27 21:15:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void destroy_token_list(t_token_list *tokens)
{
	t_token *curr;
	t_token *tmp;

	curr = tokens->all;
	while (curr)
	{
		free(curr->data);
		tmp = curr;
		curr = curr->next_token;
		free(tmp);
	}
	free(tokens);
}

void	destroy_command(t_cmd * cmd)
{
	int	i;

	i = 0;
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	while (cmd->command && (cmd->command)[i])
		free((cmd->command)[i++]);
	free(cmd->command);
}

