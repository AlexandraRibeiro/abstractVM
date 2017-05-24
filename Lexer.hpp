/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:31:44 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 17:41:55 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "Lead.hpp"

enum Instruction {
	END = 0;
	ALPHA;
	INUM;
	RNUM;
	SIGN;
	OPEN;
	CLOS;
	SPACE;
	ERROR;
};

class Lexer {
	public:
		Lexer(void);
		Lexer(Lexer const & cpy);
		~Lexer(void);
		Lexer & operator=(Lexer const & rhs);
	private:
		static int _fsm[7][7];
};

#endif
