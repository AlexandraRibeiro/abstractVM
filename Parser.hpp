/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:30:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 16:01:01 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "Lexer.hpp"

enum instructions {
	PUSH = 0,
	POP,		// 1
	DUMP,		// 2
	ASSERT,		// 3
	ADD,		// 4
	SUB,		// 5
	MUL,		// 6
	DIV,		// 7
	MOD,		// 8
	PRINT,		// 9
	EXIT,		// 10
};

enum type {
	INT8 = 0,
	INT16,		// 1
	INT32,		// 2
	FLOAT,		// 3
	DOUBLE,		// 4
};

struct scanner2 {
	bool	error;
};

class Parser {
	public:
		Parser(void);
		Parser(Parser const & cpy);
		~Parser(void);
		Parser &	operator=(Parser const & );
		std::string	get_errors(void) const;
		void		set_errors(std::string str);
		Lexer &		get_lexer(void);
		// int		get_instruction(void);
		// int		get_type(void);
	private:
		Lexer 						*_lexer;
		std::string					_errors;
		static const std::string	_instruct[11];
		static const std::string	_type[5];
};

#endif
