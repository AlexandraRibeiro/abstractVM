/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/12 15:05:01 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMP_H
# define OPERAND_TEMP_H

#include "IOperand.hpp"
#include "Factory.hpp"


template<typename T>

class Operand : public IOperand {
	public:
		Operand(eOperandType type, std::string const & value, int precision, Factory const & factory) : _factory(factory)
		{
			long double ld;
			std::cout << "Operand's constructor called\n";
			this->_type = type;
			this->_valueStr = value;
			this->_precision = precision;
			ld = string2num(this->_valueStr);
			this->_valueTyped = static_cast<T>(ld);
		}

		Operand (Operand const & cpy) {*this = cpy;}

		~Operand (void)
		{
			std::cout << "Operand's destructor called\n";
		}

		Operand 	& operator=(Operand const & rhs)
		{
			this->_type = rhs.getType();
			this->_valueStr = rhs.toString();
			this->_precision = rhs.getPrecision();
			this->_factory = rhs.getFactory();
			this->_valueTyped = rhs.getValueTyped();
			return *this;
		}

		// GETTER ______________________________________________________________
		int					getPrecision( void ) const { return this->_precision; }

		eOperandType		getType( void ) const { return this->_type; }

		std::string const & toString( void ) const { return this->_valueStr; }

		Factory const &		getFactory(void) const { return this->_factory; }

		T					getValueTyped(void) const {	return this->_valueTyped; }



		// SUM _________________________________________________________________
		IOperand const * operator+( IOperand const & rhs ) const
		{
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
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
		}

		// DIFFERENCE __________________________________________________________
		IOperand const * operator-( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			int precision = (this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision());
			if (type < FLOAT)
			{
				llresult = _valueTyped;
				llresult -= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = _valueTyped;
				ldresult -= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
		}

		// PRODUCT _____________________________________________________________
		IOperand const * operator*( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			int precision = (this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision());
			if (type < FLOAT)
			{
				llresult = _valueTyped;
				llresult *= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = _valueTyped;
				ldresult *= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
		}

		// QUOTIENT ____________________________________________________________
		IOperand const * operator/( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			int precision = (this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision());
			if (string2num(rhs.toString()) == 0)
			{
				valueStr = "ZERODIV";
				return (this->_factory.createOperand(type, valueStr));
			}
			if (type < FLOAT)
			{
				llresult = _valueTyped;
				llresult /= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = _valueTyped;
				ldresult /= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
		}

		//MODULO ______________________________________________________________
		IOperand const * operator%( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult1;
			long long llresult2;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			int precision = (this->_precision >= rhs.getPrecision() ? this->_precision : rhs.getPrecision());
			if (string2num(rhs.toString()) == 0)
			{
				valueStr = "ZEROMOD";
				return (this->_factory.createOperand(type, valueStr));
			}
			if (type < FLOAT)
			{
				llresult1 = _valueTyped;
				llresult2 = string2num(rhs.toString());
				llresult1 = llresult1 % llresult2;
				ldresult = llresult1;
			}
			else
			{
				ldresult = _valueTyped;
				ldresult = fmod(ldresult, string2num(rhs.toString()));
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string(ldresult, precision);
			return (this->_factory.createOperand(type, valueStr));
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
