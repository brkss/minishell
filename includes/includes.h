/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:13:57 by adriouic          #+#    #+#             */
/*   Updated: 2022/04/05 15:11:06 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdbool.h> 

#define QUOTE 1
#define DQUOTE 2
#define NONE 0


char	*append(char *prefix, const char *sufix);
void	free_befor_end(char **lst, int end);
bool	is_even(int x);
int		get_pipe_fileds(char ***argv);


typedef struct s_command
{
	char 	**cmd;
	int		in_file;
	int		out_file;
	int		nb_pipes;
	int		append;

}t_command;


int	ft_strcmp(const char *s1, const char *s2);
char	**my_ft_split(const char *str, char c);
char *polish(const char *s, char *charset);
bool get_data_from_subfield(int ac, char **fields, t_command ***all_commands);
t_command *parser(char *field);
#endif
