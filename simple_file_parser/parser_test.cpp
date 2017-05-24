// ================================================================
// parser_test.cpp
//
//
// Class_Parser supports single characters tokens,
// specific line comments with only 1 char ex ';'
//
// ================================================================

#include "Global.hpp"
#include "Class_Parser.hpp"

std::string get_input()
{
    std::string result = "";
    std::string line ;
    std::cout << "Input lines here ( terminate with ';;' ) :" << std::endl;
    while ( std::getline(std::cin, line) )
    {
        // unsigned int loc = line.find( ";;", 0 );
        // if( loc == std::string::npos )
			// line.append("\n");
        result.append(line) ;
    	// if( loc != std::string::npos )
            // break;
    }
    return(result);
}

int main(int argc,char** argv)
{
    Class_Parser sfp;
	if (argc < 2)
    {
    	std::string result = get_input();
    	if (!sfp.create_temp_file(result))
    		MYERR("cannot treat input : leaving...");
    }
    else
    {
    	std::string file_name = argv[1];
    	if (!sfp.open(file_name))
			MYERR("cannot read file: '" << file_name << "'");
    }
	// Describe additional single line comment
	sfp.set_extra_line_comment(";");

	// Describe additional single character delimiters ex '+'
    // so that it will break out 'foo+bar' as 3 tokens instead of 1.
    sfp.set_single_char_tokens("()");

	// parse and show info.
	//sfp.do_parse_info();

	// parse and collect.
	std::vector<std::string> my_tokens;
	sfp.do_parse(my_tokens);

	for( unsigned int i = 0; i < my_tokens.size(); i++ )
	{
  		std::cout << "Element " << i << " is " << my_tokens.at(i) << std::endl;
	}

}
