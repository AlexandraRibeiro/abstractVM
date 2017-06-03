/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/03 14:22:00 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"


Lexer::Lexer(void) : _errorFinded(false) {
	std::cout << "constructor Lexer called" << std::endl;
}

Lexer::Lexer(Lexer const & cpy) : _errorFinded(false) {
	*this = cpy;
}

Lexer::~Lexer(void) {
	std::cout << "destructor Lexer called" << std::endl;
}

Lexer &		Lexer::operator=(Lexer const & ) {
	return *this;
}


// INPUT ______________________________________________________________________
void							Lexer::set_input(std::string line) {
	this->_input.push_back(line);
}

std::vector<std::string> &		Lexer::get_input(void) {
	return (this->_input);
}

void							Lexer::debug_print_input(void) {
	std::vector<std::string>::const_iterator i = this->_input.begin();
	while (i != this->_input.end())
	{
		std::cout << *i << std::endl;
		i++;
	}
}


// LEXICAL ____________________________________________________________________
void							Lexer::set_lexical(void)
{
	int			j = 0;
	int			w = 0;
	int 		count_line = 1;
	std::string tmp;
	int			current_state = 0;
	int			previous_state = 0;
	bool		stop = false;
	std::vector<std::string>::const_iterator i = this->_input.begin();
	while (i != this->_input.end())
	{
		//go to the next line
		tmp = *i;
		j = 0;
		current_state = 0;
		previous_state = 0;
		stop = false;
		//read line
		while (tmp[j] != '\0')
		{
			this->_lexical.push_back(s_scanner());
			this->_lexical[w].line_nb = count_line;
			this->_lexical[w].original_line.append(tmp);
			this->_lexical[w].error = false;
			//read lexeme
			while (tmp[j] != '\0')
			{
				previous_state = current_state;
				current_state = this->_fsm[previous_state][this->get_token(tmp[j])];
				if (current_state != END)
				{
					this->_lexical[w].token = current_state;
					this->_lexical[w].lexeme.push_back(tmp[j]);
				}
				if (current_state == END)
				{
						this->_lexical[w].token = previous_state;
						break;
				}
				if (current_state == ERROR)
				{
						this->_lexical[w].error = true;
						this->_lexical[w].error_position = j;
						this->_errorFinded = true;
						stop = true;
						break;
				}
				j++;
				if (tmp[j] == '\0' || tmp[j] == ';')
				{
					this->_lexical[w].token = current_state;
					stop = true;
					break;
				}
			}
			w++;
			if (stop == true)
				break;
		}
		i++;
		count_line++;
	}
	std::vector<std::string>().swap(this->_input); 			//free this->_input
}

std::vector<s_scanner> &			Lexer::get_lexical(void) {
	return (this->_lexical);
}

void								Lexer::debug_print_lexical(void) {
	int c = 0;
	std::vector<s_scanner>::const_iterator i = this->_lexical.begin();
	while (i != this->_lexical.end())
	{
		std::cout << "line_nb = " << this->_lexical[c].line_nb << std::endl;
		std::cout << "token = " << this->_lexical[c].token << std::endl;
		std::cout << "lexeme = \"" << this->_lexical[c].lexeme << "\"" << std::endl;
		std::cout << "original line = \"" << this->_lexical[c].original_line << "\"" << std::endl;
		std::cout << "error = " << this->_lexical[c].error << std::endl;
		std::cout << "error position = " << this->_lexical[c].error_position << std::endl;
		std::cout << "___________________________________________" << std::endl;
		i++;
		c++;
	}
}


// GETTER ______________________________________________________________________
int		Lexer::get_token(char c) {
	if (c >= 'a' && c <= 'z')
		return ALPHA;
	else if (c >= '0' && c <= '9')
		return INUM;
	else if (c == '.')
		return RNUM;
	else if (c == '+' || c == '-')
		return SIGN;
	else if (c == '(')
		return OPEN;
	else if (c == ')')
		return CLOS;
	else if (c == ' ' || c == '\t')
		return SPACE;
	else
		return ERROR;
}

bool	Lexer::get_errorFinded(void) {
	return this->_errorFinded;
}


// STATIC _____________________________________________________________________
const int	Lexer::_fsm[9][9]= {
				/* INPUT */
{END,			ALPHA,	INUM,	RNUM,	SIGN,	OPEN,	CLOS,	SPACE,	ERROR},
/* STATE */
{ALPHA,			ALPHA,	ALPHA,	ERROR,	ERROR,	END,	ERROR,	END,	ERROR},
{INUM,			ERROR,	INUM,	RNUM,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{RNUM,			ERROR,	RNUM,	ERROR,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{SIGN,			ERROR,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{OPEN,			ERROR,	END,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR},
{CLOS,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR},
{SPACE,			END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{ERROR,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR}
};
