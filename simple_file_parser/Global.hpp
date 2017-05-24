// ================================================================
// Global.hpp
//
//
// used to put global includes and define
//
// ================================================================
#ifndef GLOBAL_HPP
# define GLOBAL_HPP

# include <iostream>
# include <istream>
# include <fstream>
# include <vector>
# include <cstdlib>
# include <cstring>
# include <iomanip>

# define SHOW_ALL	0
# define MYDEBUG(msg) cout << "DEBUG:" << __FILE__ << ":" << __LINE__ << ": " << msg << endl
# define MYERR(msg) {std::cerr << std::endl << "ERROR:" << __FILE__ << ":" << __LINE__ << ": " << msg << std::endl; exit(1);}

#endif