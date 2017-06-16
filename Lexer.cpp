/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:41 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/16 15:07:15 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"


Lexer::Lexer(void) {
	if (verbose_option == true)
		std::cout << BLUE << "\t -> " << NORMAL << "Lexer's constructor called" << std::endl;
}

Lexer::Lexer(Lexer const & cpy) {
	*this = cpy;
}

Lexer::~Lexer(void) {
	if (verbose_option == true)
		std::cout << BLUE << "\t\t -> " << NORMAL << "Lexer's destructor called" << std::endl;
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
	size_t c = 0;
	while (c < this->_input.size())
	{
		std::cout << this->_input[c] << std::endl;
		c++;
	}
}

void							Lexer::generate_option_stock_input(void)
{
	size_t c = 0;
	std::string filename;
	std::cout << GREEN << "\n\tOption -g detected -> " << NORMAL << "Please enter the filename (no need the extension) : ";
	std::cin >> filename;
	if (filename.compare("") == 0)
		filename = "input";
	std::ofstream savefile (filename + ".txt", std::ofstream::out);
	while (c < this->_input.size())
	{
		savefile << this->_input[c] << std::endl;
		c++;
	}
	savefile.close();
	std::cout << GREEN << "\t-> " << NORMAL << "The file " << filename << ".txt has been created\n\n";
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
	if (i == this->_input.end())
		throw BaseException("\t(lexer) Empty input!");
	while (i != this->_input.end())
	{
		//go to the next line
		tmp = *i;
		j = 0;
		current_state = 0;
		previous_state = 0;
		stop = false;
		//read line
		while (tmp[j] != '\0' && tmp[j] != ';')
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
						this->_lexical[w].error_position_lexer = j;
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
	if (generate_option == true)
		generate_option_stock_input();
	std::vector<std::string>().swap(this->_input); 			//free this->_input
}

std::vector<s_scanner> &			Lexer::get_lexical(void) {
	return (this->_lexical);
}

void								Lexer::debug_print_lexical(void) {
	size_t c = 0;
	std::cout << BLUE << "\n\n\t********** LEXER **********\n" << NORMAL;
	while (c < this->_lexical.size())
	{
		std::cout << "\tline_nb = " << this->_lexical[c].line_nb << std::endl;
		std::cout << "\ttoken = " << this->_lexical[c].token << std::endl;
		std::cout << "\tlexeme = \"" << this->_lexical[c].lexeme << "\"\n";
		std::cout << "\toriginal line = \"" << this->_lexical[c].original_line << "\"\n";
		std::cout << "\terror = " << this->_lexical[c].error << std::endl;
		std::cout << "\terror position = " << this->_lexical[c].error_position_lexer << std::endl;
		std::cout << BLUE << "\t___________________________\n" << NORMAL;
		c++;
	}
	std::cout << "\n";
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
