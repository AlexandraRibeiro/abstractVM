/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:31:02 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:33:15 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : _lexer(NULL) {
	std::cout << "constructor Parser called" << std::endl;
	this->_lexer = new Lexer();
}

Parser::Parser(Parser const & cpy) : _lexer(NULL) {
	*this = cpy;
}

Parser::~Parser(void) {
	if (this->_lexer)
		delete(this->_lexer);
	std::cout << "destructor Parser called" << std::endl;
}

Parser &	Parser::operator=(Parser const & ) {
	return *this;
}

std::string	Parser::get_errors(void) const {
		return (this->_errors);
}

void		Parser::set_errors(std::string str) {
		this->_errors.append(str);
		this->_errors.push_back('\n');
}

Lexer &		Parser::get_lexer(void) {
	return *this->_lexer;
}
