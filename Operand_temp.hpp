/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/16 17:17:08 by aribeiro         ###   ########.fr       */
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
			if (verbose_option == true)
				std::cout << BLUE << "\t -> " << NORMAL << "Operand's constructor called\n";
			this->_type = type;
			this->_valueStr = value;
			this->_precision = precision;
		}

		Operand (Operand const & cpy) {*this = cpy;}

		~Operand (void)
		{
			if (verbose_option == true)
				std::cout << BLUE << "\t\t -> " << NORMAL << "Operand's destructor called\n";
		}

		Operand 	& operator=(Operand const & rhs)
		{
			this->_type = rhs.getType();
			this->_valueStr = rhs.toString();
			this->_precision = rhs.getPrecision();
			this->_factory = rhs.getFactory();
			return *this;
		}

		// GETTER ______________________________________________________________
		int					getPrecision( void ) const { return this->_precision; }

		eOperandType		getType( void ) const { return this->_type; }

		std::string const & toString( void ) const { return this->_valueStr; }

		Factory const &		getFactory(void) const { return this->_factory; }


		// SUM _________________________________________________________________
		IOperand const * operator+( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			if (type < FLOAT)
			{
				llresult = string2num(this->toString());
				llresult += string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = string2num(this->toString());
				ldresult += string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string_trunc(ldresult, type);
			return (this->_factory.createOperand(type, valueStr));
		}

		// DIFFERENCE __________________________________________________________
		IOperand const * operator-( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			if (type < FLOAT)
			{
				llresult = string2num(this->toString());
				llresult -= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = string2num(this->toString());
				ldresult -= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string_trunc(ldresult, type);
			return (this->_factory.createOperand(type, valueStr));
		}

		// PRODUCT _____________________________________________________________
		IOperand const * operator*( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			if (type < FLOAT)
			{
				llresult = string2num(this->toString());
				llresult *= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = string2num(this->toString());
				ldresult *= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string_trunc(ldresult, type);
			return (this->_factory.createOperand(type, valueStr));
		}

		// QUOTIENT ____________________________________________________________
		IOperand const * operator/( IOperand const & rhs ) const
		{
			std::string valueStr = "";
			long double ldresult;
			long long llresult;
			eOperandType type = (this->_type >= rhs.getType() ? this->_type : rhs.getType());
			if (string2num(rhs.toString()) == 0)
			{
				valueStr = "ZERODIV";
				return (this->_factory.createOperand(type, valueStr));
			}
			if (type < FLOAT)
			{
				llresult = string2num(this->toString());
				llresult /= string2num(rhs.toString());
				ldresult = llresult;
			}
			else
			{
				ldresult = string2num(this->toString());
				ldresult /= string2num(rhs.toString());
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string_trunc(ldresult, type);
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
			if (string2num(rhs.toString()) == 0)
			{
				valueStr = "ZEROMOD";
				return (this->_factory.createOperand(type, valueStr));
			}
			if (type < FLOAT)
			{
				llresult1 = string2num(this->toString());
				llresult2 = string2num(rhs.toString());
				llresult1 = llresult1 % llresult2;
				ldresult = llresult1;
			}
			else
			{
				ldresult = string2num(this->toString());
				ldresult = fmod(ldresult, string2num(rhs.toString()));
			}
			if (verif_value(type, ldresult) == 15)
				valueStr = "OVER";
			else if (verif_value(type, ldresult) == 14)
				valueStr = "UNDER";
			else
				valueStr = num2string_trunc(ldresult, type);
			return (this->_factory.createOperand(type, valueStr));
		}



	private:
		Operand(void) {}
		eOperandType				_type;
		std::string					_valueStr;
		int							_precision;
		Factory const	&			_factory;
};

#endif
