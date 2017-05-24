// ================================================================
// Class_Parser.hpp
//
//
// Class_Parser supports single characters tokens, 
// specific line comments with only 1 char ex ';'
//
// ================================================================
#ifndef ClASS_PARSER_HPP
# define ClASS_PARSER_HPP

# include "Global.hpp"

class Class_Parser
{
public:

    // Container for the tokens.
    typedef std::vector<std::string> tokens_t;

	//Default constructor.
    Class_Parser();

	//Destructor.
    ~Class_Parser();

    // do parsing file and collect into vector
	void do_parse(std::vector<std::string> &my_tokens);
	
    // do parsing file and print info
	void do_parse_info();
	
	// 
	bool create_temp_file(const std::string& content);
	
    /**
     * Does the file exist?
     * @param fn The file name to check (const char*).
     * @returns True if it does or false otherwise.
     */
    static bool file_exists(const char* fn);

    /**
     * Does the file exist (const string parameter)?
     * @param fn The file name to check (const string&).
     * @returns True if it does or false otherwise.
     */
    static bool file_exists(const std::string& fn);

    /**
     * Begin the parsing operation by opening the file and
     * setting up the internal state.
     * @param fn The file to parse.
     * @returns true if the file was opened and is ready to parse or
     *               false otherwise.
     */
    bool open(const std::string& fn);

    /**
     * End the parsing operation.
     * This method can be called multiple times.
     */
    void close();

    /**
     * Get the line number.
     * @return the current line number.
     */
    inline unsigned get_line_number() const
    {
        return m_lineno;
    }

    /**
     * Get the file name.
     * @return the file name.
     */
    inline const std::string& get_file_name() const
    {
        return m_fn;
    }

    /**
     * Get tokens from the next line.
     * Multi-line records are coalsced into a single record and comments are stripped out.
     * Blank lines are ignored.
     * @returns The number of tokens.
     */
    size_t get_next_line();

    /**
     * Get the number of tokens just parsed.
     * @returns The number of parsed tokens.
     */
    size_t get_num_tokens() const
    {
        return m_tokens.size();
    }

    /**
     * Get the i-th token.
     * @param i The token index in the range [0..(N-1)] where
     *          N == get_num_tokens(). If i is out of range,
     *          an exception is thrown from the underlying
     *          std::vector.
     * @returns The i-th token.
     */
    const std::string& get_token(size_t i) const
    {
        return m_tokens[i];
    }


    /**
     * Define the single character tokens.
     * This is used to define single character tokens.
     * Here is an example usage:
     * \code
     *    // Make ; and . separate tokens.
     *    sfp.set_single_char_tokens(";.");
     * \endcode
     * @param tokens A string the contains the list of single character tokens.
     */
    void set_single_char_tokens(const char* tokens);

    /**
     * Get the single character tokens.
     * @returns the single character tokens in a string. If there are no
     * tokens, an empty string it returned.
     */
    const char* get_single_char_tokens() const;
    
    /**
     * Get/Set the extra comment characters.
     */ 
    void set_extra_line_comment(const char* extra);
	const char* get_extra_line_comment() const;
	
private:

    /**
     * Remove comments from the string.
     * @param p Pointer to the token.
     * @returns the updated pointer.
     */
    char* skip_comments(char* p);

    /**
     * Skip white space.
     * @param p Pointer to the string.
     * @returns The pointer to the next token.
     */
    char* skip_whitespace(char* p);

    /**
     * Skip to white space.
     * @param p Pointer to the string.
     * @returns The pointer to the next white space.
     */
    char* skip_to_whitespace(char* p);

    /**
     * Add a token.
     * This is where the processing takes place to determine whether
     * there are embedded single character tokens.
     * @param token The token to add. It may contain embedded single
     *              character tokens.
     */
    void add_token(char* token);

    std::string			m_fn;
    std::ifstream     *	m_ifs;
    tokens_t       		m_tokens;	//std::vector<std::string>
    unsigned int   		m_lineno;
    char              * m_buf;
    unsigned int   		m_bufsz;
    bool           		m_single_char_tokens[256];
    char              * m_extra;
    unsigned int   		m_tempf;
};

#endif
