/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:35:04 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/14 19:42:28 by aribeiro         ###   ########.fr       */
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

# define FL_PRECIS	std::numeric_limits<float>::digits10
# define DB_PRECIS	std::numeric_limits<double>::digits10

# define VERBOSE_OPT	"-v"
# define GENERATE_OPT	"-g"

extern bool	verbose_option;
extern bool	generate_option;

long double string2num(const std::string & text);
std::string num2string_trunc(long double ld, int type);
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
