/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FLAGS_H
# define PARSE_FLAGS_H

typedef struct	s_mod
{
	t_buffer	buf;
	t_modifier	modifier;
}				t_mod;

# define STR_TO_BUF(str) { (uint8_t *)(str), (sizeof (str) - 1) }

#endif
