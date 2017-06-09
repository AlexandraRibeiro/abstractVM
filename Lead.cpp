/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/09 16:36:58 by aribeiro         ###   ########.fr       */
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

Parser							& Lead::get_parser(void) {
	return *this->_parser;
}


bool							Lead::execute(void) {
	size_t i;
	size_t c = 0;
	// char ascii;
	std::vector<s_scanner2> scan2 = this->_parser->get_parsing();
	Factory factory;
	// IOperand const * v1;
	// IOperand const * v2;
	if (c == scan2.size())
	{
		std::cout << "error empty input" << std::endl;
		return false;
	}
	while(c < scan2.size())
	{
		if (scan2[c].error == true)
			return false;
		if (scan2[c].instruction == PUSH)
			this->_stack.push_back(factory.createOperand(static_cast<eOperandType> (scan2[c].type), num2string(scan2[c].value)));
		// else if (scan2[c].instruction == POP)
		// {
		// 	if (this->_stack.empty() == true)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) pop | empty stack");
		// 		return false;
		// 	}
		// 	this->_stack.pop_back();
		// }
		else if (scan2[c].instruction == DUMP)
		{
			if (this->_stack.empty() == true)
				std::cout << "Warning : (execute) dump | empty stack\n";
			i = this->_stack.size();
			while (i-- > 0)
				std::cout << this->_stack[i]->toString() << std::endl;
		}
		// else if (scan2[c].instruction == ASSERT)
		// {
		// 	if (this->_stack.empty() == true)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) assert | empty stack");
		// 		return false;
		// 	}
		// 	if (this->_stack.back()->toString() != num2string(scan2[c].value))
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) assert | value error");
		// 		return false;
		// 	}
		// 	if (this->_stack.back()->getType() != static_cast<eOperandType> scan2[c].type)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) assert | type error");
		// 		return false;
		// 	}
		// }
		// else if (scan2[c].instruction >= ADD && scan2[c].instruction <= MOD)
		// {
		// 	if (this->_stack.empty() == true)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) operand | empty stack");
		// 		return false;
		// 	}
		// 	if (this->_stack.size() < 2)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) operand | only one value in the stack");
		// 		return false;
		// 	}
		// 	//stock IOperand const *
		// 	v1 = this->_stack.back();
		// 	this->_stack.pop_back();
		// 	v2 = this->_stack.back();
		// 	this->_stack.pop_back();
		// 	//
		// 	if (scan2[c].instruction == ADD)
		// 		this->_stack.push_back(*v2 + *v1);
		// 	else if (scan2[c].instruction == SUB)
		// 		this->_stack.push_back(*v2 - *v1);
		// 	else if (scan2[c].instruction == MUL)
		// 		this->_stack.push_back(*v2 * *v1);
		// 	else if (scan2[c].instruction == DIV)
		// 		this->_stack.push_back(*v2 / *v1);
		// 	else if (scan2[c].instruction == MOD)
		// 		this->_stack.push_back(*v2 % *v1);
		// 	delete v1;
		// 	delete v2;
		// 	//verif error
		// }
		// else if (scan2[c].instruction == PRINT)
		// {
		// 	if (this->_stack.empty() == true)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) print | empty stack");
		// 		return false;
		// 	}
		// 	if (this->_stack.back()->getType() != INT8)
		// 	{
		// 		scan2[c].error_verbose.append(" : (execute) print | type error");
		// 		return false;
		// 	}
		// 	if ((ascii = string2num(this->_stack.back()->toString())) < 0)
		// 		std::cout << "Warning : (execute) print | not printable value < 0\n";
		// 	else if ((ascii == 127)
		// 		std::cout << "Warning : (execute) print | not printable value = 127\n";
		// 	else if (ascii < 32)
		// 		std::cout << "Warning : (execute) print | not printable value < 32\n";
		// 	std::cout << ascii << std::endl;
		// }
		else if (scan2[c].instruction == EXIT)
			return true;
		c++;
	}
	return true;

}
