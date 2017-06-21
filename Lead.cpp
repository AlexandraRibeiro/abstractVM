/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/17 15:28:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

Lead::Lead(void) : _parser(NULL), _factory(NULL)
{
	if (verbose_option == true)
		std::cout << BLUE << "\t -> " << NORMAL << "Lead's constructor called" << std::endl;
	this->_parser = new Parser();
}

Lead::Lead(Lead const & cpy) { *this = cpy; }

Lead::~Lead(void)
{
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
	if (verbose_option == true)
		std::cout << BLUE << "\t\t -> " << NORMAL << "Lead's destructor called" << std::endl;
}

Lead &		Lead::operator=(Lead const &) {	return *this; }

Parser		& Lead::get_parser(void) { return *this->_parser; }

Factory		& Lead::get_factory(void) { return *this->_factory; }


void		Lead::execute(void)
{
	this->_factory = new Factory();
	size_t c = 0;
	std::vector<s_scanner2> scan2 = this->_parser->get_parsing();
	if (c == scan2.size()) //empty input
		throw BaseException("\t(parser) Empty input!");
	while(c < scan2.size())
	{
		if (scan2[c].error == true)
			throw BaseException("\nERROR(S) DETECTED");
		if (scan2[c].instruction == PUSH)
			this->_stack.push_back(this->_factory->createOperand(static_cast<eOperandType>(scan2[c].type), num2string_trunc(scan2[c].value, scan2[c].type)));
		else if (scan2[c].instruction == POP)
			exe_pop(c);
		else if (scan2[c].instruction == DUMP)
			exe_dump();
		else if (scan2[c].instruction == ASSERT)
			exe_assert(c, scan2[c].type, scan2[c].value);
		else if (scan2[c].instruction >= ADD && scan2[c].instruction <= MOD)
			exe_operands(c, scan2[c].instruction);
		else if (scan2[c].instruction == PRINT)
			exe_print(c);
		else if (scan2[c].instruction == EXIT && (c + 1) == scan2.size())
			return ;
		else if (scan2[c].instruction == SHOW)
			exe_show();
		else if (scan2[c].instruction == SWAP)
			exe_swap(c);
		else if (scan2[c].instruction == REVERSE)
			exe_reverse(c);
		c++;
	}
}

/* EXE POP ///////////////////////////////////////////////////////////////////*/
void		Lead::exe_pop(size_t c)
{
	IOperand const * v1;
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error pop | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	v1 = this->_stack.back();
	this->_stack.pop_back();
	delete v1;
}

/* EXE DUMP //////////////////////////////////////////////////////////////////*/
void		Lead::exe_dump(void)
{
	size_t i;
	if (this->_stack.empty() == true)
		std::cout << YELLOW << "\n* Warning : (execute) error dump | empty stack\n\n" << NORMAL;
	i = this->_stack.size();
	while (i-- > 0)
		std::cout << this->_stack[i]->toString() << std::endl;
}

/* EXE ASSERT ////////////////////////////////////////////////////////////////*/
void		Lead::exe_assert(size_t c, int type, long double value)
{
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error assert | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.back()->toString() != num2string_trunc(value, type))
	{
		this->_parser->set_error_verbose(c, " : (execute) error assert | value error", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.back()->getType() != static_cast<eOperandType> (type))
	{
		this->_parser->set_error_verbose(c, " : (execute) error assert | type error", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
}

/* EXE OPERANDS //////////////////////////////////////////////////////////////*/
void		Lead::exe_operands(size_t c, int instruction)
{
	IOperand const * v1;
	IOperand const * v2;
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.size() < 2)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | only one value in the stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	v1 = this->_stack.back();
	this->_stack.pop_back();
	v2 = this->_stack.back();
	this->_stack.pop_back();
	if (instruction == ADD)
		this->_stack.push_back(*v2 + *v1);
	else if (instruction == SUB)
		this->_stack.push_back(*v2 - *v1);
	else if (instruction == MUL)
		this->_stack.push_back(*v2 * *v1);
	else if (instruction == DIV)
		this->_stack.push_back(*v2 / *v1);
	else if (instruction == MOD)
		this->_stack.push_back(*v2 % *v1);
	delete v1;
	delete v2;
	verif_error_operand(c);
}

void		Lead::verif_error_operand(size_t c)
{
	if (this->_stack.empty() == true)
		return;
	if (this->_stack.back()->toString().compare("OVER") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | overflow" , -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	else if (this->_stack.back()->toString().compare("UNDER") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand | underflow" , -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	else if (this->_stack.back()->toString().compare("ZERODIV") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand 'div' | division with 0" , -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	else if (this->_stack.back()->toString().compare("ZEROMOD") == 0)
	{
		this->_parser->set_error_verbose(c, " : (execute) error operand 'mod' | modulo with 0" , -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
}


/* EXE PRINT /////////////////////////////////////////////////////////////////*/
void		Lead::exe_print(size_t c)
{
	char ascii;
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error print | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.back()->getType() != INT8)
	{
		this->_parser->set_error_verbose(c, " : (execute) error print | type error", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if ((ascii = string2num(this->_stack.back()->toString())) < 0)
		std::cout << YELLOW << "* Warning : (execute) error print | negative not printable value = " << this->_stack.back()->toString() << "\n" << NORMAL;
	else if ( (ascii > -1 && ascii < 9) || (ascii > 10 && ascii < 32) || (ascii == 127))
		std::cout << YELLOW << "* Warning : (execute) error print | special character not printable value = " << this->_stack.back()->toString() << "\n" << NORMAL;
	else
		std::cout << ascii << std::endl;
}


/* EXE SHOW (BONUS) //////////////////////////////////////////////////////////*/
void		Lead::exe_show(void)
{
	size_t i;
	if (this->_stack.empty() == true)
		std::cout << YELLOW << "\n* Warning : (execute) error show | empty stack\n\n" << NORMAL;
	i = this->_stack.size();
	while (i-- > 0)
		std::cout << "type " << this->_parser->_type[this->_stack[i]->getType()] << "\t| value = " << this->_stack[i]->toString() << std::endl;
}

/* EXE SWAP (BONUS) //////////////////////////////////////////////////////////*/
void		Lead::exe_swap(size_t c)
{
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error swap | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.size() < 2)
	{
		this->_parser->set_error_verbose(c, " : (execute) error swap | only one value in the stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	std::iter_swap(this->_stack.end() - 1, this->_stack.end() - 2);
}

/* EXE REVERSE (BONUS) ///////////////////////////////////////////////////////*/
void		Lead::exe_reverse(size_t c)
{
	if (this->_stack.empty() == true)
	{
		this->_parser->set_error_verbose(c, " : (execute) error reverse | empty stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	if (this->_stack.size() < 2)
	{
		this->_parser->set_error_verbose(c, " : (execute) error reverse | only one value in the stack", -1);
		throw BaseException("\nERROR(S) DETECTED");
	}
	std::iter_swap(this->_stack.begin(), this->_stack.end() -1);
}

/*	PRINT ERRORS /////////////////////////////////////////////////////////////*/
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
