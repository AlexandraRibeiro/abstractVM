/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/07 21:06:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMP_H
# define OPERAND_TEMP_H

#include "IOperand.hpp"

template<typename T>

class Operand : public IOperand {
	public:
		Operand(eOperandType type, std::string const & value, int precision, Factory const & factory) {
			this->_type = type;
			this->_valueStr = value;
			this->_precision = precision;
			this->_factory = factory;
		}
		Operand (Operand const & cpy) {*this = cpy;}
		~Operand (void) {}
		~IOperand(void) {}
		
		Operand 	& operator=(Operand const &) { 								//remplir la copie ________________________________________
			return *this;
		}

		int getPrecision( void ) const;		//Precision of the type of the instance
		eOperandType getType( void ) const;	// Type of the instance

		IOperand const * operator+( IOperand const & rhs ) const;	//Sum
		IOperand const * operator-( IOperand const & rhs ) const;	//Difference
		IOperand const * operator*( IOperand const & rhs ) const;	//Product
		IOperand const * operator/( IOperand const & rhs ) const;	//Quotient
		IOperand const * operator%( IOperand const & rhs ) const;	//Modulo

		std::string const & toString( void ) const; // String representation of the instance


	private:
		Operand(void) {}
		eOperandType		_type;
		std::string			_valueStr;
		int					_precision;
		Factory const	&	_factory;
};

#endif
