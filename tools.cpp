/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 19:56:03 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/05 16:59:15 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

long double string2num(const std::string & text)
{
	std::stringstream ss(text);
	long double result;
	return (ss >> result ? result : 0);
}
