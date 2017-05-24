// ================================================================
// Class_Parser.cpp
//
//
// Simple file parser.
//
// ================================================================

#include "Global.hpp"
#include "Class_Parser.hpp"



Class_Parser::Class_Parser()
    : m_ifs(0),
      m_lineno(0),
      m_bufsz(65536)
{
    m_buf = new char[m_bufsz];
    size_t sz = sizeof(m_single_char_tokens)/sizeof(bool);
    m_extra = (char *)"";
    m_fn = "";
    for(size_t i=0; i<sz; ++i)
        m_single_char_tokens[i] = false;
}

Class_Parser::~Class_Parser()
{
    close();
    delete [] m_buf;
    m_bufsz = 0;
    if (m_tempf)
    	std::remove("temp_input_file.txt"); // delete file
}

bool Class_Parser::create_temp_file(const std::string& content)
{
	std::remove("temp_input_file.txt"); // delete file
	m_tempf = 1;
  	std::ofstream myfile;
  	myfile.open("temp_input_file.txt");  
  	if (myfile.is_open())
  	{
    	myfile << content;
    	myfile.close();
    	return open("temp_input_file.txt");
  	}
	return false;
}
	
bool Class_Parser::file_exists(const char* fn)
{
    std::ifstream ifs(fn);
    if (!ifs || ifs.bad())
        return false;
    return true;
}

bool Class_Parser::file_exists(const std::string& fn)
{
    return file_exists(fn.c_str());
}

bool Class_Parser::open(const std::string& fn)
{
    if (!file_exists(fn))
        return false;
    close();
    m_ifs = new std::ifstream(fn.c_str());
    if (!*m_ifs || m_ifs->bad())
    {
        close();
        return false;
    }
    m_fn = fn;
    return true;
}

void Class_Parser::close()
{
    if (m_ifs)
    {
        m_lineno = 0;
        delete m_ifs;
        m_ifs = 0;
        m_tokens.clear();
        m_fn = "";
    }
}

void Class_Parser::do_parse(std::vector<std::string> & my_tokens)
{
	my_tokens.clear();
	while (get_next_line())
    {
    	for(size_t i = 0; i < get_num_tokens(); i++)
    	{
  			my_tokens.push_back(get_token(i));
         	if (SHOW_ALL)
				std::cout <<  my_tokens.back() << std::endl;
    	}
    }
}


void Class_Parser::do_parse_info()
{
	while (get_next_line())
    {
        // Print out the tokens for each line.
        std::cout << "Line " << get_line_number() << " has "
             << get_num_tokens() << " tokens" << std::endl;  
		for(size_t i = 0; i < get_num_tokens(); i++)
 		{
  			std::cout << "   token[" << std::setw(2) << std::setfill('0')
     	 		<< std::right << i << std::left << std::setfill(' ') << "] = "
         		<< "'" << get_token(i) << "'" << std::endl;
    	}
    }
}

void Class_Parser::set_single_char_tokens(const char* tokens)
{
    if (tokens)
    {
        for(const char* p = tokens; *p; ++p)
        {
            size_t i = size_t(*p);
            m_single_char_tokens[i] = true;
        }
    }
}

const char* Class_Parser::get_single_char_tokens() const
{
    const size_t cache_size = sizeof(m_single_char_tokens)/sizeof(bool);
    static char cache[cache_size];
    char* p = cache;
    for(size_t i=0; i<cache_size; ++i)
    {
        if (m_single_char_tokens[i])
        {
            char ch = char(i);
            *p++ = ch;
        }
    }
    *p = 0;
    return cache;
}



char* Class_Parser::skip_comments(char* p)
{
    if (!*p)
        return p;
    const char *temp = get_extra_line_comment();
	if (temp[0] != '\0'&& strchr(temp, *p)!= NULL)
		for(; *p; ++p);			
    return p;
}

char* Class_Parser::skip_whitespace(char* p)
{
    if (!*p)
        return p;
    for(; *p != 0 && (*p <= ' ' || *p >= 127); ++p);
    p = skip_comments(p);
    if (*p && (*p <= ' ' || *p >= 127))
        p = skip_whitespace(p); 
    return p;
}

char* Class_Parser::skip_to_whitespace(char* p)
{
    for(; *p !=0 && *p > ' ' && *p < 127; ++p);
    return p;
}


void Class_Parser::add_token(char* token)
{

    char* cur = token;
    char* beg = token;
    for(; *cur; ++cur)
    {
		size_t i = size_t(*cur);
        if (m_single_char_tokens[i])
        {
            char single_char_token[2] = {*cur,0};
            single_char_token[0] = *cur;
            *cur = 0;
            if (*beg) // handle the case of a single character token
                m_tokens.push_back(beg);
            m_tokens.push_back(single_char_token);
            beg = cur + 1;
            *cur = single_char_token[0];
        }
        cur = skip_whitespace(cur);
        if (!*cur)
			return;         
    }
    if (!*cur && *beg)
    {
        //MYDEBUG("adding token \""<<beg<<"\"");
        m_tokens.push_back(beg);
    }
}

size_t Class_Parser::get_next_line()
{
    // Parsing happens here.
    m_buf[0] = '\0'; 
    m_tokens.clear();
    char *p = m_buf;
    if (m_ifs->eof())
   		return 0;
    while (1)
    {
        m_ifs->getline(m_buf, m_bufsz);
		m_lineno++;
		if (SHOW_ALL)
			std::cout << "Input line: " << m_lineno << "  >>" << m_buf << std::endl;
		// Process the line.
        p = skip_whitespace(m_buf);
        if (*p)
        {
            while (*p)
            {
				char* end = p;
				end = skip_to_whitespace(p);
                char ec = *end;
                *end = 0;
                add_token(p);
                if (ec)
                    p = skip_whitespace(end + 1);
                else
                    *p = 0;
            }
        }
		break;	
    }
    if(!m_tokens.empty()) // check if comment char at the end and kill it
    {
    	std::string s1 = m_tokens.back();
    	char c_x = s1[0];
    	if (c_x != '\0' && strchr(m_extra, c_x)!= NULL )
    		m_tokens.pop_back();
    }
    m_tokens.push_back("EOL");
    return get_num_tokens();
}


void Class_Parser::set_extra_line_comment(const char* extra)
{
	m_extra = (char *)extra;
	char *p = m_extra;
	while (*p)
	{
  		m_single_char_tokens[size_t(*p)] = true;
  		p++;
	}
}


const char* Class_Parser::get_extra_line_comment() const
{
	return (const char*)m_extra;
}
