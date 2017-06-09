/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:55:48 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/09 16:33:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_H
# define IOPERAND_H

#include "Parser.hpp"

class IOperand {
	public:
		virtual int getPrecision( void ) const = 0;		//Precision of the type of the instance
		virtual eOperandType getType( void ) const = 0;	// Type of the instance

		virtual IOperand const * operator+( IOperand const & rhs ) const = 0;	//Sum
		// virtual IOperand const * operator-( IOperand const & rhs ) const = 0;	//Difference
		// virtual IOperand const * operator*( IOperand const & rhs ) const = 0;	//Product
		// virtual IOperand const * operator/( IOperand const & rhs ) const = 0;	//Quotient
		// virtual IOperand const * operator%( IOperand const & rhs ) const = 0;	//Modulo

		virtual std::string const & toString( void ) const = 0; // String representation of the instance

		virtual ~IOperand( void ) {}
};

#endif
