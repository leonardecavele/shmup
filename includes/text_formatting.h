/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formatting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:16:29 by abetemps          #+#    #+#             */
/*   Updated: 2025/11/29 15:35:53 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		__TEXT_FORMATTING_H__
# define	__TEXT_FORMATTING_H__

// FOREGROUND COLORS
# define BLACK "\001\033[30m\002"
# define RED "\001\033[31m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define BLUE "\001\033[34m\002"
# define MAGENTA "\001\033[35m\002"
# define CYAN "\001\033[36m\002"
# define WHITE "\001\033[97m\002"

// BACKGROUND COLORS
# define BG_BLACK "\001\033[40m\002"
# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"

// FORMAT
# define BOLD "\001\033[1m\002"
# define DIM "\001\033[2m\002"
# define UNDL "\001\033[4m\002"

// RESET
# define RST "\001\033[0m\002"
# define R_BOLD "\001\033[21m\002"
# define R_DIM "\001\033[22m\002"
# define R_UL "\001\033[24m\002"
# define R_FG "\001\033[39m\002"

#endif
