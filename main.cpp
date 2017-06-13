/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/13 18:28:47 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

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

int				main(int ac, char **av)
{
	Lead lead;
	Parser *parser;
	Lexer *lexer;
	parser = &lead.get_parser();
	lexer = &parser->get_lexer();

	// GET INPUT _______________________________________________________________
	try {
		if (ac > 1)
			stock_input_file(av[1], *lexer);
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
	////////////////////////////////////////////////////////////////////////////

	// LEXER ___________________________________________________________________
	try
	{
		lexer->set_lexical();
		// PARSER ______________________________________________________________
		try
		{
			parser->set_parsing();
			// EXECUTE _________________________________________________________
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
			////////////////////////////////////////////////////////////////////
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
		////////////////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////////////////////

	return (0);
}
