/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:18:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/14 13:58:27 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "core_data.h"

// Parser Error

# define ERR_ARGC "Error: Wrong number of arguments\n"
# define EARGC 1
# define ERR_ARGV "Error: Wrong argument\n"
# define EARGTYPE 2

// Parser Functions

int		parser(int ac, char **av, t_arg *arg);

#endif //PARSER_H