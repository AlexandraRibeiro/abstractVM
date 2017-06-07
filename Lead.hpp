/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:34 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/07 15:57:54 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAD_H
# define LEAD_H

#include "Parser.hpp"
#include "IOperand.hpp"

class Lead {
	public:
		Lead(void);
		Lead(Lead const & cpy);
		~Lead(void);
		Lead 						& operator=(Lead const &);
		Parser						& get_parser(void);

	private:
		Parser 						*_parser;
};

#endif
