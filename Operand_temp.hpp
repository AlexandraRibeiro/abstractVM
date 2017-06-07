/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand_temp.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:43:01 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/07 21:06:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMP_H
# define OPERAND_TEMP_H

#include "Parser.hpp"

template<typename T>

class Operand {
	public:
		Operand(std::string const & value);
		~Operand(void);
};

#endif
