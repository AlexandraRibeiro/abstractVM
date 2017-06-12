/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/06/12 17:14:01 by aribeiro         ###   ########.fr       */
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
		std::cout << YELLOW << "* WARNING : no \";;\" at the end of program read from standard input\n" << NORMAL;
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

	if (ac > 1)
		stock_input_file(av[1], *lexer);
	else
		stock_input_cin(*lexer);

	lexer->set_lexical();
/* DEBUG : VERIF SCAN LEXER _____________________*/
// lexer->debug_print_lexical();
/* DEBUG : VERIF DEALLOC VECTOR _input dans Lexer _____________________*/
// std::cout << "test dealloc vector" << std::endl;
// lexer->debug_print_input();

	parser->set_parsing();
/* DEBUG : VERIF SCAN PARSER _____________________*/
// parser->debug_print_parsing();

	if (lead.execute() == false)
		lead.print_all_errors();


	return (0);
}
