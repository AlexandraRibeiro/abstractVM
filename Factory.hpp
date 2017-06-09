/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 19:22:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/09 15:31:33 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

#include "Operand_temp.hpp"

class Factory  {
	public:
		//create a type for the vector (pointers on member functions)
		typedef IOperand const * (Factory::*createOp)(std::string const &) const;

		Factory(void);
		Factory(Factory const & cpy);
		~Factory(void);
		Factory & operator=(Factory const &);
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	private:
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		//an array of pointers on member functions with enum values as index.
		std::vector<createOp>		_arrayPtr;
};

#endif
