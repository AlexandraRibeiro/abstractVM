/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:34 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:31:00 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAD_H
# define LEAD_H

#include <exception>
#include <fstream>
#include <string>
#include <iomanip>

#include "Parser.hpp"
//ajouter std::exception ?
class Lead {
	public:
		Lead(void);
		Lead(Lead const & cpy);
		~Lead(void);
		Lead 						& operator=(Lead const &);
		// void						run_lexer_parser(void);
		Parser						& get_parser(void);

	private:
		Parser 						*_parser;
};

#endif
