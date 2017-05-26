/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:26:03 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void) {
	std::cout << "constructor Lexer called" << std::endl;
}

Lexer::Lexer(Lexer const & cpy) {
	*this = cpy;
}

Lexer::~Lexer(void) {
	std::cout << "destructor Lexer called" << std::endl;
}

Lexer &		Lexer::operator=(Lexer const & ) {
	return *this;
}

void							Lexer::stock_input(std::string line) {
	this->_input.push_back(line);
}

std::vector<std::string> &		Lexer::get_input(void) {
	return (this->_input);
}

void							Lexer::read_input(void) {
	for (std::vector<std::string>::const_iterator i = this->_input.begin(); i != this->_input.end(); i++)
		std::cout << *i << std::endl;
}


const int	Lexer::_fsm[9][9]= {
				// INPUT
{0,				ALPHA,	INUM,	RNUM,	SIGN,	OPEN,	CLOS,	SPACE,	ERROR},
// STATE
{ALPHA,			ALPHA,	ALPHA,	ERROR,	ERROR,	END,	ERROR,	END,	ERROR},
{INUM,			ERROR,	INUM,	RNUM,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{RNUM,			ERROR,	RNUM,	ERROR,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{SIGN,			ERROR,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{OPEN,			ERROR,	END,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR},
{CLOS,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR},
{SPACE,			END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{ERROR,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR}
};
