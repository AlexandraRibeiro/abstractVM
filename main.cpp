/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/31 18:16:53 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"

static void		stock_input_file(Lexer &l, Parser &p)
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
	{
		p.set_errors("_______ WARNING : no \";;\" at the end of program read from standard input");
		std::cout << p.get_errors() << std::endl;
	}
}

static void		stock_input_cin(char *filename, Lexer &l)
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
		stock_input_cin(av[1], *lexer);
	else
		stock_input_file(*lexer, *parser);

	lexer->set_lexical();
	// if (lexer->get_errorFinded() == true)
	// {
	// 	parser->set_errors();
	// 	parser->print_errors();
	// }
	// else
		parser->set_parsing();

/* DEBUG : VERIF SCAN LEXER _____________________*/
// lexer->debug_print_lexical();



// std::cout << "test dealloc vector" << std::endl;
// lexer->debug_print_input();

	// parser->

	return (0);
}
