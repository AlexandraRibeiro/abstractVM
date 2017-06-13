/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/13 22:00:05 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

Lead::Lead(void) : _parser(NULL), _factory(NULL) {
	if (DEBUG == 1)
		std::cout << "Lead's constructor called" << std::endl;
	this->_parser = new Parser();
}

Lead::Lead(Lead const & cpy) {
	*this = cpy;
}

Lead::~Lead(void) {
	size_t c = 0;
	if (c < this->_stack.size())
	{
		while (c < this->_stack.size())
		{
			delete this->_stack[c];
			c++;
		}
	}
	if (this->_factory)
		delete(this->_factory);
	if (this->_parser)
		delete(this->_parser);
	if (DEBUG == 1)
		std::cout << "Lead's destructor called" << std::endl;
}

Lead &							Lead::operator=(Lead const &) {
	return *this;
}

Parser							& Lead::get_parser(void) {
	return *this->_parser;
}

Factory							& Lead::get_factory(void) {
	return *this->_factory;
}

void							Lead::execute(void) {
	this->_factory = new Factory();
	size_t i;
	size_t c = 0;
	char ascii;
	std::vector<s_scanner2> scan2 = this->_parser->get_parsing();
	IOperand const * v1;
	IOperand const * v2;
	if (c == scan2.size()) //empty input
		throw BaseException("\t(parser) Empty input!");
	while(c < scan2.size())
	{
		if (scan2[c].error == true)
			throw BaseException("ERROR(S) DETECTED");
		if (scan2[c].instruction == PUSH)
			this->_stack.push_back(this->_factory->createOperand(static_cast<eOperandType>(scan2[c].type), num2string_trunc(scan2[c].value, scan2[c].type)));
		else if (scan2[c].instruction == POP)
		{
			if (this->_stack.empty() == true)
			{
				this->_parser->set_error_verbose(c, " : (execute) error pop | empty stack", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			v1 = this->_stack.back();
			this->_stack.pop_back();
			delete v1;
		}
		else if (scan2[c].instruction == DUMP)
		{
			if (this->_stack.empty() == true)
				std::cout << YELLOW << "* Warning : (execute) error dump | empty stack\n" << NORMAL;
			i = this->_stack.size();
			while (i-- > 0)
				std::cout << this->_stack[i]->toString() << std::endl;
		}
		else if (scan2[c].instruction == ASSERT)
		{
			if (this->_stack.empty() == true)
			{
				this->_parser->set_error_verbose(c, " : (execute) error assert | empty stack", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			if (this->_stack.back()->toString() != num2string_trunc(scan2[c].value, scan2[c].type))
			{
				this->_parser->set_error_verbose(c, " : (execute) error assert | value error", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			if (this->_stack.back()->getType() != static_cast<eOperandType> (scan2[c].type))
			{
				this->_parser->set_error_verbose(c, " : (execute) error assert | type error", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
		}
		else if (scan2[c].instruction >= ADD && scan2[c].instruction <= MOD)
		{
			if (this->_stack.empty() == true)
			{
				this->_parser->set_error_verbose(c, " : (execute) error operand | empty stack", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			if (this->_stack.size() < 2)
			{
				this->_parser->set_error_verbose(c, " : (execute) error operand | only one value in the stack", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			v1 = this->_stack.back();
			this->_stack.pop_back();
			v2 = this->_stack.back();
			this->_stack.pop_back();
			if (scan2[c].instruction == ADD)
				this->_stack.push_back(*v2 + *v1);
			else if (scan2[c].instruction == SUB)
				this->_stack.push_back(*v2 - *v1);
			else if (scan2[c].instruction == MUL)
				this->_stack.push_back(*v2 * *v1);
			else if (scan2[c].instruction == DIV)
				this->_stack.push_back(*v2 / *v1);
			else if (scan2[c].instruction == MOD)
				this->_stack.push_back(*v2 % *v1);
			delete v1;
			delete v2;
			if (verif_error_operand(c) == false)
				throw BaseException("ERROR(S) DETECTED");
		}
		else if (scan2[c].instruction == PRINT)
		{
			if (this->_stack.empty() == true)
			{
				this->_parser->set_error_verbose(c, " : (execute) error print | empty stack", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			if (this->_stack.back()->getType() != INT8)
			{
				this->_parser->set_error_verbose(c, " : (execute) error print | type error", -1);
				throw BaseException("ERROR(S) DETECTED");
			}
			if ((ascii = string2num(this->_stack.back()->toString())) < 0)
				std::cout << YELLOW << "* Warning : (execute) error print | not printable value < 0\n" << NORMAL;
			else if (ascii == 127)
				std::cout << YELLOW << "* Warning : (execute) error print | not printable value = 127\n" << NORMAL;
			else if (ascii < 32)
				std::cout << YELLOW << "* Warning : (execute) error print | not printable value < 32\n" << NORMAL;
			std::cout << ascii << std::endl;
		}
		else if (scan2[c].instruction == EXIT)
			return ;
		c++;
	}
}

bool		Lead::verif_error_operand(size_t c)
{
	if (this->_stack.empty() == true)
		return true;
	if (this->_stack.back()->toString().compare("OVER") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | overflow" , -1);
		return false;
	}
	else if (this->_stack.back()->toString().compare("UNDER") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | underflow" , -1);
		return false;
	}
	else if (this->_stack.back()->toString().compare("ZERODIV") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand 'div' | division with 0" , -1);
		return false;
	}
	else if (this->_stack.back()->toString().compare("ZEROMOD") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand 'mod' | modulo with 0" , -1);
		return false;
	}
	return true;
}

void		Lead::print_all_errors(void)
{
	size_t c = 0;
	std::vector<s_scanner2> scan2 = this->_parser->get_parsing();
	while (c < scan2.size())
	{
		if (scan2[c].error_verbose.compare("") != 0)
			std::cout << scan2[c].error_verbose << std::endl;
		c++;
	}
}
