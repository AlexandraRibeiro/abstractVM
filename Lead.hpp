/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lead.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:14:34 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/24 20:29:13 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAD_H
# define LEAD_H

#include <iostream>
#include <exception>

#include "Lexer.hpp"
//ajouter std::exception
class Lead {
	public:
		Lead(void);
		Lead(Lead const & cpy);
		~Lead(void);
		Lead & operator=(Lead const &);
	private:
		Lexer* _lexer;
};

#endif
