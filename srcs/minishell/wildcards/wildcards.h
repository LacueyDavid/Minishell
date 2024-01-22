/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jdenis <jdenis@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/01/15 18:34:31 by jdenis            #+#    #+#             */
/*   Updated: 2024/01/15 18:34:31 by jdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "colors.h"
# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

void	wildcards(char ***values);
char	*ft_strchr_with_quote(const char *s, int c);
int		match_end(char *file);
int		wildcard_match(const char *dir_file, char *wildcarded_file);
void	add_file(char ***values, char *file);
char	*name_file_or_dir(struct dirent *entry, char *wildcarded_file);
size_t	count_files(char **values, char *file);

#endif