/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:30:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:33:59 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "Lexer.hpp"

class Parser {
	public:
		Parser(void);
		Parser(Parser const & cpy);
		~Parser(void);
		Parser &	operator=(Parser const & );
		std::string	get_errors(void) const;
		void		set_errors(std::string str);
		Lexer &		get_lexer(void);
	private:
		Lexer 			*_lexer;
		std::string		_errors;
};

#endif
