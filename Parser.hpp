/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:30:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 18:00:24 by aribeiro         ###   ########.fr       */
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

enum types {
	INT8 = 11,
	INT16,		// 12
	INT32,		// 13
	FLOAT,		// 14
	DOUBLE,		// 15
};

struct s_scanner2 {
	int				nb_line;
	int				instruction;
	int				type;
	int				value;
	std::string		line;
	bool			error;
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
		//parsing _____________________________________________
		void	set_parsing(void);
		int		get_instruction(std::string lexeme);
		int		get_type(std::string lexeme);
	private:
		Lexer 						*_lexer;
		std::string					_errors;
		std::vector<s_scanner2>		_parsing;
		static const std::string	_instruct[11];
		static const std::string	_type[5];
};

#endif
