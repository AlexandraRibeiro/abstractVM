/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:31:02 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/04 20:59:41 by aribeiro         ###   ########.fr       */
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
	int pos = 0;
	size_t c = 0;
	int	j = -1;
	int sign = 1;
	bool exit_found = false;
	std::vector<s_scanner> lex = this->_lexer->get_lexical();
	if (c == lex.size())
	{
		std::cout << "error empty input" << std::endl;
		return;
	}
	while (c < lex.size())
	{
		pos = 0;
		this->_parsing.push_back(s_scanner2());
		j++;
		this->init_scanner2(j, lex[c].line_nb, -1, -1, -1, lex[c].original_line, false, -1);
		while (c < lex.size() && this->_parsing[j].line_nb == lex[c].line_nb)
		{
			if (lex[c].error == true)
			{
				pos = 20; //dit qu'il y a une erreur lexer
				this->_parsing[j].error_position_lexer = lex[c].error_position_lexer;
				break;
			}
			else if (pos == 0) 													//search instruction
			{
				this->_parsing[j].instruction = this->get_instruction(lex[c].lexeme);
				if (this->_parsing[j].instruction == -1)
					break;
				if (this->_parsing[j].instruction == EXIT && exit_found == false)
					exit_found = true;
				else if (this->_parsing[j].instruction == EXIT && exit_found == true)
				{
					pos = 12;
					break;
				}
				if (this->_parsing[j].instruction == PUSH || this->_parsing[j].instruction == ASSERT)
					pos = 2;
				else
					pos = 1;
			}
			else if (pos == 1 || pos == 2) 										//search SPACE
			{
				if (lex[c].token != SPACE)
				{
					if (pos == 1)
						pos = 11;
					break;
				}
				if (pos == 2)
					pos++;
			}
			else if (pos == 3)													//search type
			{
				this->_parsing[j].type = this->get_type(lex[c].lexeme);
				if (this->_parsing[j].type == -1)
					break;
				pos++;
			}
			else if (pos == 4)													//search OPEN
			{
				if (lex[c].token != OPEN)
					break;
				pos++;
			}
			else if (pos == 5)													//search SIGN (optional)
			{
				if (lex[c].token != SIGN && lex[c].token != INUM && lex[c].token != RNUM)
					break;
				else if (lex[c].token == SIGN && lex[c].lexeme.compare("-") == 0)
					sign = -1;
				else if (lex[c].token == INUM || lex[c].token != RNUM)
					pos++;
			}
			/***** Because SIGN is optional start with "if" not "else if" *****/
			if (pos == 6)														//search value
			{
				if (lex[c].token != SIGN && lex[c].token != INUM && lex[c].token != RNUM)
					break;
				// if (sign == true)
				// 	lex[c].lexeme.insert(0, lex[c - 1].lexeme);
				this->_parsing[j].value = 42; //valeur en dur remplacer par un atoi
				pos++;
			}
			else if (pos == 7)
			{
				if (lex[c].token != CLOS)
					break;
				pos++;
			}
			else if (pos == 8)													//search SPACE (optional)
			{
				if (lex[c].token != SPACE)
				{
					pos++;
					break;
				}
			}
			c++;
		}
		/***** End parsing line *****/
		if (pos != 1 && pos != 8)
		{
			this->_parsing[j].error = true;
			if (pos != 20)
				this->set_error_verbose(j, this->_verbose[pos], -1);
			while (c < lex.size() && this->_parsing[j].line_nb == lex[c].line_nb)
			{
				if (lex[c].error == true)
					this->set_error_verbose(j, " : (lexer) error found at the position ", lex[c].error_position_lexer);
				c++;
			}
		}
	}
	if (this->_parsing[j].instruction != EXIT)
		this->set_error_verbose(j, this->_verbose[EXIT], -1);
}


void		Parser::set_error_verbose(int j, std::string str1, int position_lexer)
{
	std::ostringstream oss; //to convert int -> str
	this->_parsing[j].error_verbose.append("------> line ");
	oss.str(""); //to clear stream
	oss << this->_parsing[j].line_nb;
	this->_parsing[j].error_verbose.append(oss.str());
	this->_parsing[j].error_verbose.append(str1);
	if (position_lexer != -1)
	{
		oss.str(""); //to clear stream
		oss << position_lexer;
		this->_parsing[j].error_verbose.append(oss.str());
	}
	this->_parsing[j].error_verbose.push_back('\n');
}


void		Parser::debug_print_parsing(void)
{
	size_t c = 0;
	std::cout << "\n**** PARSER ****\n";
	while (c < this->_parsing.size())
	{
		std::cout << "line_nb = \"" << this->_parsing[c].line_nb << "\"\n";
		std::cout << "instruction = \"" << this->_parsing[c].instruction << "\"\n";
		std::cout << "type = \"" << this->_parsing[c].type << "\"\n";
		std::cout << "value = \"" << this->_parsing[c].value << "\"\n";
		std::cout << "original_line = \"" << this->_parsing[c].original_line << "\"\n";
		std::cout << "error = \"" << this->_parsing[c].error << "\"\n";
		std::cout << "error position lexer = \"" << this->_parsing[c].error_position_lexer << "\"\n";
		std::cout << "error verbose = \"" << this->_parsing[c].error_verbose << "\"\n";
		std::cout << "___________________________________________\n";
		c++;
	}

}

void		Parser::init_scanner2(int j, int line_nb, int instruction, int type,
				int value, std::string original_line, bool error, int error_position_lexer)
{
	this->_parsing[j].line_nb = line_nb;
	this->_parsing[j].instruction = instruction;
	this->_parsing[j].type = type;
	this->_parsing[j].value = value;
	this->_parsing[j].original_line.append(original_line);
	this->_parsing[j].error = error;
	this->_parsing[j].error_position_lexer = error_position_lexer;
	this->_parsing[j].error_verbose.append("");
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
			return i;
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
	/* 0  ,  1     ,  2     ,  3     ,  4       */

const std::string		Parser::_verbose[13] = {
	" : (parser) error not a valid instruction",					// pos = 0
	"",
	" : (parser) error after the instruction", 						// pos = 2
	" : (parser) error expected type after space",					// pos = 3
	" : (parser) error expected '(' after type",					// pos = 4
	" : (parser) error after '('",									// pos = 5
	" : (parser) error not a valid value",							// pos = 6
	" : (parser) error expected ')' after value",					// pos = 7
	"",
	" : (parser) error after ')'",									// pos = 9
	" : (parser) the program doesn’t have an exit instruction",		// pos = 10 = EXIT
	" : (parser) error expected nothing after this instruction",	// pos = 11
	" : (parser) error find 2 'exit' instruction",					// pos = 12
};
