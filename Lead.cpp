/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 20:26:39 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

Lead::Lead(void) : _lexer(NULL) {
	std::cout << "test lead class" << std::endl;
	this->_lexer = new Lexer();
}

Lead::Lead(Lead const & cpy) : _lexer(NULL) {
	*this = cpy;
}

Lead::~Lead(void) {
	if (this->_lexer)
		delete(this->_lexer);
}

Lead &		Lead::operator=(Lead const &) {
	return *this;
}
