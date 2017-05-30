/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/30 18:39:42 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

// ____________________________________________________________________________
Lexer::Lexer(void) {
	std::cout << "constructor Lexer called" << std::endl;
}

Lexer::Lexer(Lexer const & cpy) {
	*this = cpy;
}

Lexer::~Lexer(void) {
	std::cout << "destructor Lexer called" << std::endl;
}

Lexer &		Lexer::operator=(Lexer const & ) {
	return *this;
}


// ____________________________________________________________________________

void							Lexer::set_input(std::string line) {
	this->_input.push_back(line);
}

std::vector<std::string> &		Lexer::get_input(void) {
	return (this->_input);
}

void							Lexer::set_lexical(void)
{
	int j = 0;
	int c = 0;
	std::string tmp;
	int			current_state = 0;
	int			previous_state = 0;
	std::vector<std::string>::const_iterator i = this->_input.begin();
	while (i != this->_input.end())
	{
		tmp = *i;
		j = 0;
		this->_lexical.push_back(scanner());
		this->_lexical[c].nb_line = c + 1;
		this->_lexical[c].line.append(tmp);
		this->_lexical[c].error = false;
		while (tmp[j] != '\0' && tmp[j] != ';')
		{
			current_state = this->_fsm[previous_state][this->get_token(tmp[j])];
			if (current_state != END)
				this->_lexical[c].lexeme.push_back(tmp[j]);
			// else if (current_state == END)
			// {
			// 	this->_lexical[c].token = previous_state;
			// 	break;
			// }
			if (current_state == ERROR)
			{
				this->_lexical[c].error = true;
				break;
			}
			j++;
		}
		i++;
		c++;
	}
	this->debug_print_lexical();
}

std::vector<scanner> &			Lexer::get_lexical(void) {
	return (this->_lexical);
}

void							Lexer::debug_print_lexical(void) {
	int c = 0;
	std::vector<scanner>::const_iterator i = this->_lexical.begin();
	while (i != this->_lexical.end())
	{
		std::cout << "token = " << this->_lexical[c].token << std::endl;
		std::cout << "lexeme = " << this->_lexical[c].lexeme << std::endl;
		std::cout << "nb_line = " << this->_lexical[c].nb_line << std::endl;
		std::cout << "line = " << this->_lexical[c].line << std::endl;
		std::cout << "error = " << this->_lexical[c].error << std::endl;
		std::cout << "___________________________________________" << std::endl;
		i++;
		c++;
	}
}

int								Lexer::get_token(char c) {
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

// ____________________________________________________________________________
const int	Lexer::_fsm[9][9]= {
				/* INPUT */
{0,				ALPHA,	INUM,	RNUM,	SIGN,	OPEN,	CLOS,	SPACE,	ERROR},
/* STATE */
{ALPHA,			ALPHA,	ALPHA,	ERROR,	ERROR,	END,	ERROR,	END,	ERROR},
{INUM,			ERROR,	INUM,	RNUM,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{RNUM,			ERROR,	RNUM,	ERROR,	ERROR,	ERROR,	END,	ERROR,	ERROR},
{SIGN,			ERROR,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{OPEN,			ERROR,	END,	END,	END,	ERROR,	ERROR,	ERROR,	ERROR},
{CLOS,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR},
{SPACE,			END,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR},
{ERROR,			ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	ERROR,	END,	ERROR}
};
