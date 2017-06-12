/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/12 16:52:53 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cfloat>
#include <tgmath.h>

#define YELLOW	"\033[33;1m"
#define BLUE	"\033[36;1m"
#define MAGENTA	"\033[35;1m"
#define GREEN	"\033[32;1m"
#define NORMAL	"\033[0m"

#define DEBUG	0

long double string2num(const std::string & text);
std::string num2string(long double ld);
std::string num2string(long double ld, int precision);
std::string num2string(long long ll, int precision);
int			verif_value(int type, long double value);

enum tokens {
	END = 0,
	ALPHA,		// 1 = Alpha || Alphanum
	INUM, 		// 2 = Int
	RNUM,		// 3 = Real (ex: 3.8)
	SIGN,		// 4 = + || -
	OPEN,		// 5 = '('
	CLOS,		// 6 = ')'
	SPACE,		// 7 = space || tab
	ERROR		// 8
};

struct s_scanner {
	int			line_nb;
	int			token;
	std::string	lexeme;
	std::string original_line;
	bool		error;
	int			error_position_lexer;
};

class Lexer {
	public:
		Lexer(void);
		Lexer(Lexer const & cpy);
		~Lexer(void);
		Lexer & operator=(Lexer const & );
		//input ________________________________________________
		void						set_input(std::string line);
		std::vector<std::string>	& get_input(void);
		void						debug_print_input(void);
		//lexical ______________________________________________
		void						set_lexical(void);
		std::vector<s_scanner>		& get_lexical(void);
		void						debug_print_lexical(void);
		// getter _______________________________________________
		int							get_token(char c);

	private:
		std::vector<std::string> 	_input;
		std::vector<s_scanner>		_lexical;
		// static ______________________________________________
		static const int 			_fsm[9][9];
};

#endif
