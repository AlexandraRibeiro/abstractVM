/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:31:02 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 19:55:10 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : _lexer(NULL) {
	std::cout << "constructor Parser called" << std::endl;
	this->_lexer = new Lexer();
}

Parser::Parser(Parser const & cpy) : _lexer(NULL) {
	*this = cpy;
}

Parser::~Parser(void) {
	if (this->_lexer)
		delete(this->_lexer);
	std::cout << "destructor Parser called" << std::endl;
}

Parser &	Parser::operator=(Parser const & ) {
	return *this;
}

// ERRORS _____________________________________________________________________
std::string	Parser::get_errors(void) const {
		return (this->_errors);
}

void		Parser::set_errors(std::string str) {
		this->_errors.append(str);
		this->_errors.push_back('\n');
}

// LEXER ______________________________________________________________________
Lexer &		Parser::get_lexer(void) {
	return *this->_lexer;
}


// PARSING ____________________________________________________________________
void		Parser::set_parsing(void)
{
	int c = 0;
	int	j = -1;
	std::vector<s_scanner> lex = this->_lexer->get_lexical();
	std::vector<s_scanner>::const_iterator i = lex.begin();
	while (i != lex.end())
	{
		if (j == -1 || this->_parsing[j].line_nb != lex[c].line_nb)
		{
			this->_parsing.push_back(s_scanner2());
			j++;
			this->init_scanner2(j, lex[c].line_nb, -1, -1, -1, lex[c].original_line, false, -1);
		}
		i++;
		c++;
	}
}

void		Parser::debug_print_parsing(void)
{
	int c = 0;
	std::vector<s_scanner2>::const_iterator i = this->_parsing.begin();
	while (i != this->_parsing.end())
	{
		std::cout << "line_nb = \"" << this->_parsing[c].line_nb << "\"" << std::endl;
		std::cout << "instruction = \"" << this->_parsing[c].instruction << "\"" << std::endl;
		std::cout << "type = \"" << this->_parsing[c].type << "\"" << std::endl;
		std::cout << "value = \"" << this->_parsing[c].value << "\"" << std::endl;
		std::cout << "original_line = \"" << this->_parsing[c].original_line << "\"" << std::endl;
		std::cout << "error = \"" << this->_parsing[c].error << "\"" << std::endl;
		std::cout << "error position = " << this->_parsing[c].error_position << "\"" << std::endl;
		std::cout << "___________________________________________" << std::endl;
		i++;
		c++;
	}

}

void		Parser::init_scanner2(int j, int line_nb, int instruction, int type,
				int value, std::string original_line, bool error, int error_position)
{
	this->_parsing[j].line_nb = line_nb;
	this->_parsing[j].instruction = instruction;
	this->_parsing[j].type = type;
	this->_parsing[j].value = value;
	this->_parsing[j].original_line.append(original_line);
	this->_parsing[j].error = error;
	this->_parsing[j].error_position = error_position;
}

int			Parser::get_instruction(std::string lexeme)
{
	int i = 0;
	while (i < 11)
	{
		if (lexeme.compare(this->_instruct[i]) == 0)
			return i;
		i++;
	}
	return (-1);
}

int			Parser::get_type(std::string lexeme)
{
	int i = 0;
	while (i < 5)
	{
		if (lexeme.compare(this->_type[i]) == 0)
			return (i + 11);
		i++;
	}
	return (-1);
}


// STATIC _____________________________________________________________________
const std::string		Parser::_instruct[11] = {
	"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit" };
	/* 0  ,  1	 ,  2	 ,  3      ,  4   ,  5   ,  6   ,  7   ,  8   ,  9     ,  10 	*/

const std::string		Parser::_type[5] = {
	"int8", "int16", "int32", "float", "double" };
	/* 11  ,  12   ,  13    ,  14    ,  15      */
