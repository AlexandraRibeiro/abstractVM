/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/30 18:13:22 by aribeiro         ###   ########.fr       */
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
	ALPHA,		// Alpha || Alphanum
	INUM, 		// Int
	RNUM,		// Real (ex: 3.8)
	SIGN,		// + || -
	OPEN,		// '('
	CLOS,		// ')'
	SPACE,		// space || tab
	ERROR,
};

struct scanner {
	int			token;
	std::string	lexeme;
	int			nb_line;
	std::string line;
	bool		error;
};

class Lexer {
	public:
		Lexer(void);
		Lexer(Lexer const & cpy);
		~Lexer(void);
		Lexer & operator=(Lexer const & );
		void						set_input(std::string line);
		std::vector<std::string>	& get_input(void);
		void						set_lexical(void);
		std::vector<scanner>		& get_lexical(void);
		void						debug_print_lexical(void);
		int							get_token(char c);
	private:
		std::vector<std::string> 	_input;
		std::vector<scanner>		_lexical;
		static const int 			_fsm[9][9];
};

#endif
