/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/14 23:08:02 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

bool	verbose_option = false;
bool	generate_option = false;

static void		stock_input_cin(Lexer &l)
{
	std::string buff;
	bool i = false;
	while (std::getline(std::cin, buff))
	{
		if (buff.compare(";;") == 0)
		{
			i = true;
			break ;
		}
		else
			l.set_input(buff);
	}
	if (i == false)
		throw BaseException("* WARNING : no \";;\" at the end of program read from standard input");
}

static void		stock_input_file(char *filename, Lexer &l)
{
	std::string buff;
	std::ifstream file (filename);
	if (file.is_open())
	{
		while (std::getline(file, buff))
			l.set_input(buff);
		file.close();
	}
}

static void		check_input(int ac, char **av, Lexer &l)
{
	if ((verbose_option == true || generate_option == true) && ac > 2)
		stock_input_file(av[2], l);
	else if (verbose_option == true || generate_option == true)
		stock_input_cin(l);
	else
		stock_input_file(av[1], l);
}

static void		set_options(char *av1)
{
	if (strcmp(av1, VERBOSE_OPT) == 0)
		verbose_option = true;
	else if (strcmp(av1, GENERATE_OPT) == 0)
		generate_option = true;
}

int				main(int ac, char **av)
{
	if (ac > 1)
		set_options(av[1]);

	Lead lead;
	Parser *parser;
	Lexer *lexer;
	parser = &lead.get_parser();
	lexer = &parser->get_lexer();

	// GET INPUT _______________________________________________________________
	try {
		if (ac > 1)
			check_input(ac, av, *lexer);
		else
			stock_input_cin(*lexer);
	}
	catch (BaseException & e) {
		std::cout << YELLOW << e.what() << NORMAL << std::endl;
	}
	catch (std::exception & exception) {
		std::cerr << MAGENTA << "\nSome other std::exception occured" << NORMAL << std::endl;;
		std::cerr << YELLOW << "\t" << exception.what() << NORMAL << std::endl;
		return 1;
	}


	// LEXER ///////////////////////////////////////////////////////////////////
	try
	{
		lexer->set_lexical();
		if (verbose_option == true)
			lexer->debug_print_lexical();
		// PARSER ______________________________________________________________
		try
		{
			parser->set_parsing();
			if (verbose_option == true)
				parser->debug_print_parsing();
			// EXECUTE - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			try {
				lead.execute();
			}
			catch (BaseException & e) {
				std::cout << MAGENTA << e.what() << NORMAL << std::endl;
				lead.print_all_errors(); 		// bonus print all errors
				return 1;
			}
			catch (std::exception & exception) {
				std::cerr << "\nSome other std::exception occured :\n";
				std::cerr << "\t" << exception.what() << std::endl;
				return 1;
			}
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		}
		catch (BaseException & e) {
			std::cout << MAGENTA << "\nERROR(S) DETECTED" << NORMAL << std::endl;
			std::cout << YELLOW << e.what() << NORMAL << std::endl;
		}
		catch (std::exception & exception) {
			std::cerr << "\nSome other std::exception occured :\n";
			std::cerr << "\t" << exception.what() << std::endl;
			return 1;
		}
		//______________________________________________________________________
	}
	catch (BaseException & e) {
		std::cout << MAGENTA << "\nERROR(S) DETECTED" << NORMAL << std::endl;
		std::cout << YELLOW << e.what() << NORMAL << std::endl;
	}
	catch (std::exception & exception) {
		std::cerr << "\nSome other std::exception occured :\n";
		std::cerr << "\t" << exception.what() << std::endl;
		return 1;
	}
	// /////////////////////////////////////////////////////////////////////////

	return (0);
}
