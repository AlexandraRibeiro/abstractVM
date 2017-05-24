/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 20:57:07 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <iostream>

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
	private:
		static const int _fsm[9][9];
};

#endif
