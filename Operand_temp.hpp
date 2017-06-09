/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/09 16:35:50 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMP_H
# define OPERAND_TEMP_H

#include "IOperand.hpp"
#include "Factory.hpp"

template<typename T>

class Operand : public IOperand {
	public:
		Operand(eOperandType type, std::string const & value, int precision, Factory const & factory) : _factory(factory) {
			this->_type = type;
			this->_valueStr = value;
			this->_precision = precision;
		}
		Operand (Operand const & cpy) {*this = cpy;}
		~Operand (void) {}
		// ~IOperand(void) {}

		Operand 	& operator=(Operand const & rhs) { 								//remplir la copie ________________________________________
			this->_type = rhs.getType();
			this->_valueStr = rhs.toString();
			this->_precision = rhs.getPrecision();
			this->_factory = rhs.getFactory();
			return *this;
		}

		int getPrecision( void ) const {
			return this->_precision;
		}		//Precision of the type of the instance

		eOperandType getType( void ) const {
			return this->_type;
		}	// Type of the instance

		IOperand const * operator+( IOperand const & rhs ) const {					//Sum
			eOperandType type;
			std::string value;
			long double val1 = string2num(this->_valueStr);
			long double val2 = string2num(rhs.toString());
			if (rhs.getType() >= this->getType())
				type = rhs.getType();
			else
				type = this->getType();
			val1 += val2;
			// if (verif_value(type, val1) == 14)
			// 	this->_errorExe = UNDER;	//code error
			// else if (verif_value(type, val1) == 15)
			// 	this->_errorExe = OVER;	//code error
			value = num2string(val1);
			return (this->_factory.createOperand( type, value ));
		}

		// IOperand const * operator-( IOperand const & rhs ) const;	//Difference
		// IOperand const * operator*( IOperand const & rhs ) const;	//Product
		// IOperand const * operator/( IOperand const & rhs ) const;	//Quotient
		// IOperand const * operator%( IOperand const & rhs ) const;	//Modulo

		std::string const & toString( void ) const {
			return this->_valueStr;
		} 														// String representation of the instance

		Factory const &		getFactory(void) const {
			return this->_factory;
		}


	private:
		Operand(void) {}
		eOperandType				_type;
		std::string					_valueStr;
		int							_precision;
		Factory const	&			_factory;
};

#endif
