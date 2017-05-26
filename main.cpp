/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:39:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/05/26 20:22:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lead.hpp"


static void		read_input_file(Lead *l)
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
			l->stock_input(buff);
	}
	if (i == false)
	{
		l->set_errors("_______ ERROR : no \";;\" at the end of program read from standard input");
		std::cout << l->get_errors() << std::endl;
	}

//DEBUG *******************************************
std::cout << "<DEBUG> print _input : " << std::endl;
l->read_input();
//DEBUG *******************************************
}

static void		read_input_cin(char *filename, Lead *l)
{
	std::string buff;
	std::ifstream file (filename);
	if (file.is_open())
	{
		while (std::getline(file, buff))
			l->stock_input(buff);
		file.close();
	}
//DEBUG *******************************************
std::cout << "<DEBUG> print _input : " << std::endl;
l->read_input();
//DEBUG *******************************************
}

int				main(int ac, char **av)
{
	Lead l;
	Parser *parser;
	Lexer *lexer;

	if (ac > 1)
		read_input_cin(av[1], &l);
	else
		read_input_file(&l);
	parser = &l.get_parser();
	lexer = &parser->get_lexer();
	lexer->read(); //test debug
	// l.run_lexer_parser();
	return (0);
}
