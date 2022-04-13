/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:07:55 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/13 03:30:56 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/includes.h"

void	__init_cmd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->error_free = 1;
	cmd->command = NULL;
}
/*
void	heredoc(char *eof, t_list *env, int quote)
{
	t_list	*str_lst;
	char	*buffer;
	int		length;
	int		fd;

	str_lst = NULL;
	fd = open("/tmp/minishell-dumy_file-0ew3d",
			O_CREAT | O_APPEND | O_WRONLY, 0600);
	while (1)
	{
		length = 0;
		buffer = readline("\033[0;31mheredoc> ");
		if (!ft_strcmp(buffer, eof))
			break ;
		if (quote != S_QUOTE && ft_strchr(buffer, '$'))
			write(fd, get_expanded_values(buffer, &str_lst, env, &length), length);
		else
			write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	printf("\e\033[0;37m");
	free(buffer);
	close(fd);
	//unlink("/tmp/minishell-dumy_file-0ew3d");
}

int	close_old_open_new(t_cmd *cmd, char *file_name, int mode, int old_fd)
{
	int	fd;

	if (old_fd > 2)
		close(old_fd);
	if (mode == O_RDONLY)
	{
		if (access(file_name, F_OK) != 0)
		{
			cmd->error_free = 0;
			return (printf("Error : No such file '%s'\n", file_name) * 0);
		}
		fd = open(file_name, O_RDONLY);
	}
	else
		fd = open(file_name, O_CREAT | O_WRONLY | mode, 06644);
	if (fd < 0)
	{
		cmd->error_free = 0;
		return (printf("Permission Denied. %s \n", file_name) * 0);
	}
	return (fd);
}

void	open_file(t_cmd *cmd, t_token *t, char *file_name)
{
	if (t->type == R_ARROW)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_WRONLY, cmd->fd_out);
	else if (t->type == DR_ARROW)
		cmd->fd_out = close_old_open_new(cmd, file_name, O_APPEND, cmd->fd_out);
	else if (t->type == L_ARROW)
		cmd->fd_in = close_old_open_new(cmd, file_name, O_RDONLY, cmd->fd_in);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->fd_in > 3)
		close(cmd->fd_in);
	if (cmd->fd_out > 3)
		close(cmd->fd_out);
}

void	append_to_lst(char ***vector, char *elem, size_t *vector_size)
{
	char	**tmp;

	if (*vector == NULL)
	{
		*vector = (char **)malloc(sizeof(char *) * 2);
		(*vector)[0] = elem;
		*vector_size += 1;
	}
	else
	{
		tmp = *vector;
		*vector = (char **)malloc(sizeof(char *) * (*vector_size + 2));
		ft_memmove(*vector, tmp, sizeof(char *) * *vector_size);
		(*vector)[*vector_size] = elem;
		free(tmp);
		*vector_size += 1;
	}
	(*vector)[*vector_size] = NULL;
}
*/
void	wrape_command(t_list **cmd_lst, t_cmd **cmd, size_t *vector_size)
{
	int	fd;

	fd = (*cmd)->fd_out;
	ft_lstadd_back(cmd_lst, ft_lstnew(*cmd));
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	__init_cmd(*cmd);
	(*cmd)->fd_in = fd;
	*vector_size = 0;
}

void	__init_parser_vars(size_t *size, t_list **cmd_lst, t_cmd **cmd)
{
	*size = 0;
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*cmd_lst = NULL;
	__init_cmd(*cmd);
}

t_list	*parser_one(t_token_list *lst, t_list *env)
{
	size_t	vector_size;
	t_list	*cmd_lst;
	t_token	*t;
	t_cmd	*cmd;

	__init_parser_vars(&vector_size, &cmd_lst, &cmd);
	t = lst->all;
	while (t)
	{
		if (t->type == PIPE)
			wrape_command(&cmd_lst, &cmd, &vector_size);
		else if ((t->is_key && t->type == DL_ARROW))
		{
			heredoc(t->next_token->data, env, t->quoted);
			t = t->next_token;
		}
		if (t->is_key)
		{
			open_file(cmd, t, t->next_token->data);
			t = t->next_token;
		}
		else
			append_to_lst(&(cmd->command), t->data, &vector_size);
		if (!cmd->error_free)
			close_files(cmd);
		t = t->next_token;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	return (cmd_lst);
}
