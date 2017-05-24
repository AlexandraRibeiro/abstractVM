/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 17:51:14 by aribeiro         ###   ########.fr       */
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
	{END,	ALPHA,	INUM,	RNUM,	SIGN,	OPEN,	CLOS,	SPACE,	ERROR},
	{ALPHA,	ALPHA,	ALPHA,	ERROR,	ERROR,	END,	ERROR,	END,	ERROR},
	{INUM,  ERROR,	INUM,	RNUM,	ERROR,	ERROR,	END,	ERROR,	ERROR},
	{RNUM,	ERROR,	RNUM,	ERROR,	ERROR,	ERROR,	END,	ERROR,	ERROR},
	{SIGN,	ERROR,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
	{OPEN,	ERROR,	END,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR},
	{CLOS,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR},
	{SPACE,	END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
	{ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR}
};
