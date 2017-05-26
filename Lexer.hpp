/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:25:35 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <iostream>
#include <vector>

enum Instruction {
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

class Lexer {
	public:
		Lexer(void);
		Lexer(Lexer const & cpy);
		~Lexer(void);
		Lexer & operator=(Lexer const & );
		void						stock_input(std::string line);
		std::vector<std::string>	& get_input(void);
		void						read_input(void);
	private:
		std::vector<std::string> 	_input;
		static const int 			_fsm[9][9];
};

#endif
