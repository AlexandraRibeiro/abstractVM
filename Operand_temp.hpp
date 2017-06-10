/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/10 16:46:44 by aribeiro         ###   ########.fr       */
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
			long double ld;
			std::cout << "Operand's constructor called\n";
			this->_type = type;
			this->_valueStr = value;
			this->_precision = precision;
			ld = string2num(this->_valueStr);
			this->_valueTyped = static_cast<T>(ld);
		}
		Operand (Operand const & cpy) {*this = cpy;}
		~Operand (void) {
				std::cout << "Operand's destructor called\n";
		}

		Operand 	& operator=(Operand const & rhs) { 								//remplir la copie ________________________________________
			this->_type = rhs.getType();
			this->_valueStr = rhs.toString();
			this->_precision = rhs.getPrecision();
			this->_factory = rhs.getFactory();
			this->_valueTyped = rhs.getValueTyped();
			return *this;
		}

		int getPrecision( void ) const {
			return this->_precision;
		}

		eOperandType getType( void ) const {
			return this->_type;
		}

		IOperand const * operator+( IOperand const & rhs ) const {					//Sum
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			int precision = (this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision());
			if (type < FLOAT)
			{
				llresult = _valueTyped;
				llresult += string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = _valueTyped;
				ldresult += string2num(rhs.toString());
			}
			// std::cout << "type = " << type;
			// if (verif_value(type, ldresult) == 15)
			// 	std::cout << "overflow\n";
			// else if (verif_value(type, ldresult) == 14)
			// 	std::cout << "underflow\n";
			valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
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

		T					getValueTyped(void) const {
			return this->_valueTyped;
		}


	private:
		Operand(void) {}
		T							_valueTyped;
		eOperandType				_type;
		std::string					_valueStr;
		int							_precision;
		Factory const	&			_factory;
};

#endif
