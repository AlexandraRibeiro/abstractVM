/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 18:15:26 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

enum tokens {
	END = 0,
	ALPHA,		// 1 = Alpha || Alphanum
	INUM, 		// 2 = Int
	RNUM,		// 3 = Real (ex: 3.8)
	SIGN,		// 4 = + || -
	OPEN,		// 5 = '('
	CLOS,		// 6 = ')'
	SPACE,		// 7 = space || tab
	ERROR,		// 8
};

struct s_scanner {
	int			nb_line;
	int			token;
	std::string	lexeme;
	std::string str;
	bool		error;
	int			error_position;
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
		bool						get_errorFinded(void);

	private:
		std::vector<std::string> 	_input;
		std::vector<s_scanner>		_lexical;
		bool						_errorFinded;
		// static ______________________________________________
		static const int 			_fsm[9][9];
};

#endif
