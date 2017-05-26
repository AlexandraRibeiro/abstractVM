/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:12:10 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

Lead::Lead(void) : _parser(NULL) {
	std::cout << "constructor Lead called" << std::endl;
	this->_parser = new Parser();
}

Lead::Lead(Lead const & cpy) : _parser(NULL) {
	*this = cpy;
}

Lead::~Lead(void) {
	if (this->_parser)
		delete(this->_parser);
	std::cout << "destructor Lead called" << std::endl;
}

Lead &							Lead::operator=(Lead const &) {
	return *this;
}

void							Lead::stock_input(std::string line) {
	this->_input.push_back(line);
}

std::vector<std::string> &		Lead::get_input(void) {
	return (this->_input);
}

void							Lead::read_input(void) {
	for (std::vector<std::string>::const_iterator i = this->_input.begin(); i != this->_input.end(); i++)
		std::cout << *i << std::endl;
}

Parser							& Lead::get_parser(void) {
	return *this->_parser;
}

std::string						Lead::get_errors(void) const {
		return (this->_errors);
}

void							Lead::set_errors(std::string str) {
		this->_errors.append(str);
		this->_errors.push_back('\n');
}
