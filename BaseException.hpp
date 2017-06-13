/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:35:04 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/13 17:06:07 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASEEXCEPTION_H
# define BASEEXCEPTION_H

# include <iostream>
# include <vector>
# include <string>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <cstdint>
# include <cfloat>
# include <tgmath.h>


# define YELLOW		"\033[33;1m"
# define BLUE		"\033[36;1m"
# define MAGENTA	"\033[35;1m"
# define GREEN		"\033[32;1m"
# define NORMAL		"\033[0m"

# define DEBUG	1

long double string2num(const std::string & text);
std::string num2string(long double ld);
std::string num2string(long double ld, int precision);
std::string num2string(long long ll, int precision);
int			verif_value(int type, long double value);



class BaseException : public std::exception {
	public:
		BaseException(void);
		~BaseException(void) throw (); 			// virtual
		BaseException(std::string const & meassage);
		BaseException(BaseException const &);
		BaseException & operator=(BaseException const &);
		const char *what(void) const throw (); //virtual
	private:
		std::string		_msg;
};

#endif
