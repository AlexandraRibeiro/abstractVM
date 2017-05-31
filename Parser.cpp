/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:31:02 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 18:11:57 by aribeiro         ###   ########.fr       */
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
void		Parser::set_parsing(void) {
	int c = 0;
	// int	j = 0;
	std::vector<s_scanner> lex = this->_lexer->get_lexical();
	std::vector<s_scanner>::const_iterator i = lex.begin();
	while (i != lex.end())
	{
		this->_parsing.push_back(s_scanner2());
		if (lex[c].error == true)
		{
			this->_parsing[j].nb_line = lex[c].nb_line;
			this->_parsing[j].instruction = -1;
			this->_parsing[j].type = -1;
			this->_parsing[j].value = -1;
			this->_parsing[j].line.append(lex[c].str);
			this->_parsing[j].error = true;
		}

		std::cout << "nb_line = " << lex[c].nb_line << std::endl;
		std::cout << "token = " << lex[c].token << std::endl;
		std::cout << "lexeme = \"" << lex[c].lexeme << "\"" << std::endl;
		std::cout << "str = \"" << lex[c].str << "\"" << std::endl;
		std::cout << "error = " << lex[c].error << std::endl;
		std::cout << "___________________________________________" << std::endl;



		i++;
		c++;
	}
}

int			Parser::get_instruction(std::string lexeme) {
	int i = 0;
	while (i < 11)
	{
		if (lexeme.compare(this->_instruct[i]) == 0)
			return i;
		i++;
	}
	return (-1);
}

int			Parser::get_type(std::string lexeme) {
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
	/* 0  ,  1	   ,  2	    ,  3     ,  4       */
