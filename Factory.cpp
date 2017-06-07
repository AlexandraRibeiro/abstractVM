/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:52:19 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/07 21:12:55 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"


Factory::Factory(void) : _op(NULL) {
	std::cout << "constructor Factory called" << std::endl;
}

Factory::Factory(Factory const & cpy) : _op(NULL) {
	*this = cpy;
}

Factory::~Factory(void) {
	if (this->_op != NULL)
		delete this->_op;
	std::cout << "destructor Factory called" << std::endl;
}

Factory &			Factory::operator=(Factory const &) {
	return *this;
}

IOperand const *	Factory::createOperand(eOperandType type, std::string const & value) const {
	if (type == INT8)
		createInt8(value);
	else if (type == INT16)
		createIn16(value);
	else if (type == INT32)
		createInt32(value);
	else if (type == FLOAT)
		createFloat(value);
	else if (type == DOUBLE)
		createDouble(value);
}

IOperand const *	Factory::createInt8(std::string const & value) const {
	this->_op = new Operand<char>(value);
	return (this->_op);
}

IOperand const *	Factory::createInt16(std::string const & value) const {
	this->_op = new Operand<short>(value);
	return (this->_op);
}

IOperand const *	Factory::createInt32(std::string const & value) const {
	this->_op = new Operand<std::string>(value);
	return (this->_op);
}

IOperand const *	Factory::createFloat(std::string const & value) const {
	this->_op = new Operand<float>(value);
	return (this->_op);
}

IOperand const *	Factory::createDouble(std::string const & value) const {
	this->_op = new Operand<double>(value);
	return (this->_op);
}
