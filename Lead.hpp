/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:34 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/13 18:08:53 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAD_H
# define LEAD_H

#include "Parser.hpp"
#include "Factory.hpp"

class Lead {
	public:
		Lead(void);
		Lead(Lead const & cpy);
		~Lead(void);
		Lead 			& operator=(Lead const &);
		Parser			& get_parser(void);
		Factory			& get_factory(void);
		void			execute(void);
		bool			verif_error_operand(size_t c);
		void			print_all_errors(void);

	private:
		Parser 							*_parser;
		Factory							*_factory;
		std::vector<IOperand const *>	_stack;
};

#endif
