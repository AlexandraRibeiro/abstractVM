/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:31 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/07 15:01:29 by aribeiro         ###   ########.fr       */
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


// struct s_scanner2 {
// 	int				line_nb;
// 	int				instruction;
// 	int				type;
// 	long double		value;
// 	std::string		original_line;
// 	bool			error;
// 	int				error_position_lexer;
// 	std::string		error_verbose;
// };

// enum instructions {

// 	ADD,		// 4
// 	SUB,		// 5
// 	MUL,		// 6
// 	DIV,		// 7
// 	MOD,		// 8

// };

bool							Lead::execute(void) {
	size_t i;
	size_t c = 0;
	char ascii;
	std::ostringstream oss;
	std::vector<s_scanner2> scan2 = this->_parser.get_parsing();
	if (c == scan2.size())
	{
		std::cout << "error empty input" << std::endl;
		return false;
	}
	while(c < scan2.size())
	{
		oss.str("");
		if (scan2[c].error == true)
			return false;
		if (scan2[c].instruction == PUSH)
			this->_stack.push_back(createOperand(static_cast<eOperandType> scan2[c].type, scan2[c].value.append(oss.str())));
		else if (scan2[c].instruction == POP)
		{
			if (this->_stack.empty() == true)
			{
				scan2[c].error_verbose.append(" : (execute) pop | empty stack");
				return false;
			}
			this->_stack.pop_back();
		}
		else if (scan2[c].instruction == DUMP)
		{
			if (this->_stack.empty() == true)
				std::cout << "Warning : (execute) dump | empty stack\n";
			i = this->_stack.size();
			while (i-- > 0)
				std::cout << this->_stack[i]->toString() << std::endl;
		}
		else if (scan2[c].instruction == ASSERT)
		{
			if (this->_stack.empty() == true)
			{
				scan2[c].error_verbose.append(" : (execute) assert | empty stack");
				return false;
			}
			if (this->_stack.back()->toString() != scan2[c].value.append(oss.str()))
			{
				scan2[c].error_verbose.append(" : (execute) assert | value error");
				return false;
			}
			if (this->_stack.back()->getType() != static_cast<eOperandType> scan2[c].type)
			{
				scan2[c].error_verbose.append(" : (execute) assert | type error");
				return false;
			}
		}
		else if (scan2[c].instruction >= ADD && scan2[c].instruction <= MOD)
		{
			if (this->_stack.empty() == true)
			{
				scan2[c].error_verbose.append(" : (execute) operand | empty stack");
				return false;
			}
			if (this->_stack.size() < 2)
			{
				scan2[c].error_verbose.append(" : (execute) operand | only one value in the stack");
				return false;
			}
			
		}
		else if (scan2[c].instruction == PRINT)
		{
			if (this->_stack.empty() == true)
			{
				scan2[c].error_verbose.append(" : (execute) print | empty stack");
				return false;
			}
			if (this->_stack.back()->getType() != INT8)
			{
				scan2[c].error_verbose.append(" : (execute) print | type error");
				return false;
			}
			if ((ascii = string2num(this->_stack.back()->toString())) < 0)
				std::cout << "Warning : (execute) print | not printable value < 0\n";
			else if ((ascii == 127)
				std::cout << "Warning : (execute) print | not printable value = 127\n";
			else if (ascii < 32)
				std::cout << "Warning : (execute) print | not printable value < 32\n";
			std::cout << ascii << std::endl;
		}
		else if (scan2[c].instruction == EXIT)
			return true;
	}
	return true;

}
