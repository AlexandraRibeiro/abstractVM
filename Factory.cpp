/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:52:19 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/14 23:09:56 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand_temp.hpp"

Factory::Factory(void) {
	if (verbose_option == true)
		std::cout << BLUE << "\t -> " << NORMAL << "Factory's constructor called" << std::endl;
	this->_arrayPtr.push_back( & Factory::createInt8 );
	this->_arrayPtr.push_back( & Factory::createInt16 );
	this->_arrayPtr.push_back( & Factory::createInt32 );
	this->_arrayPtr.push_back( & Factory::createFloat );
	this->_arrayPtr.push_back( & Factory::createDouble );
}

Factory::Factory(Factory const & cpy) {
	*this = cpy;
}

Factory::~Factory(void) {
	if (verbose_option == true)
		std::cout << BLUE << "\t\t -> " << NORMAL << "Factory's destructor called" << std::endl;
}

Factory &			Factory::operator=(Factory const &) {
	return *this;
}


IOperand const *	Factory::createOperand(eOperandType type, std::string const & value) const {
	return	(this->*_arrayPtr[type]) (value);
}

//______________________________________________________________________________
IOperand const *	Factory::createInt8(std::string const & value) const {
	return	new Operand<char>(INT8, value, 3, *this);			//int8 precision -> max 3 digits
}

IOperand const *	Factory::createInt16(std::string const & value) const {
	return	new Operand<short int>(INT16, value, 5, *this);		//int16 precision -> max 5 digits
}

IOperand const *	Factory::createInt32(std::string const & value) const {
	return	new Operand<int>(INT32, value, 10, *this);			//int32 precision -> max 10 digits
}

IOperand const *	Factory::createFloat(std::string const & value) const {
	return	new Operand<float>(FLOAT, value, FL_PRECIS, *this);
}

IOperand const *	Factory::createDouble(std::string const & value) const {
	return	new Operand<double>(DOUBLE, value, DB_PRECIS, *this);
}
