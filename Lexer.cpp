/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 16:37:37 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void) {
}

Lexer::Lexer(Lexer const & cpy) {
	*this = cpy;
}

Lexer::~Lexer(void) {
}

Lexer &		Lexer::operator=(Lexer const & rhs) {
	return *this;
}

int		Lexer::_fsm[9][9]= {
				{ERROR, ALPHA, IALPH, PAROP, SIGNS, VALUE, PARCL, SPACE, UNKNO},
/* State 1 */	{ALPHA,  },
/* State 2 */	{IALPH,  },
/* State 3 */	{PAROP, },
/* State 4 */	{SIGNS, },
/* State 5 */	{VALUE, },
/* State 6 */	{PARCL, },
/* State 7 */	{SPACE, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR},
/* State 8 */	{UNKNO, }
};
