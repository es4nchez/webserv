#ifndef PARSERJSON_HPP
#define PARSERJSON_HPP

#include <string>
#include <vector>

class ParserJSON
{
	class ReadFileException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class ParsingException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

public:
	ParserJSON(std::string const &src);
	std::string const &getRaw() const;
	virtual ~ParserJSON();

	std::string toString() const;

private:
	enum e_state
	{
		STATE_IN_VALUE,
		STATE_IN_OBJECT,
		STATE_IN_ARRAY,
		STATE_IN_KEY
	};

	// LEXER
	enum e_lexem
	{
		OPEN_ARR = 0x1,
		CLOSE_ARR = 0x10,
		OPEN_OBJ = 0b100,
		CLOSE_OBJ = 0b1000,
		KEY = 0b100000,		 // nospace
		WORD = 0b1000000,	 // canspace
		BOOL = 0b10000000, // true | false
		NUMBER = 0b100000000,
		VALUE = 0b111000000 // WORD & BOOL & NUMBER
	};

	struct s_lexem
	{
		ParserJSON::e_lexem lexem;
		std::string value;
	} typedef t_lexem;

	// TOKENIZER
	enum e_token
	{
		TOKEN_OPEN_SQUARE,	 //[
		TOKEN_CLOSE_SQUARE,	 //]
		TOKEN_OPEN_BRACKET,	 //{
		TOKEN_CLOSE_BRACKET, //}
		TOKEN_COLON,				 //:
		TOKEN_COMMA,				 //,
		TOKEN_QUOTE,				 //"

		TOKEN_WHITE,
		TOKEN_NL,
		TOKEN_CHAR,
		TOKEN_NUMBER
	};

	struct s_token
	{
		ParserJSON::e_token token;
		std::string value;
	} typedef t_token;

	std::string const _raw;
	std::vector<ParserJSON::t_lexem> _lexems;

	void tokenizer(std::vector<t_token> &tokens) const;
	e_token get_token(char c) const;

	void lexer(std::vector<t_token> &tokens);
	void skip_white_and_nl(std::vector<ParserJSON::t_token>::const_iterator &it,
												 std::vector<ParserJSON::t_token>::const_iterator const &end) const;
	ParserJSON::t_lexem parse_string(std::vector<ParserJSON::t_token>::const_iterator &it,
																	 std::vector<ParserJSON::t_token>::const_iterator const &end) const;
	ParserJSON::t_lexem parse_bool(std::vector<ParserJSON::t_token>::const_iterator &it,
																 std::vector<ParserJSON::t_token>::const_iterator const &end) const;
	ParserJSON::t_lexem parse_number(std::vector<ParserJSON::t_token>::const_iterator &it,
																	 std::vector<ParserJSON::t_token>::const_iterator const &end) const;
	ParserJSON::t_lexem state_parse_key(std::vector<ParserJSON::t_token>::const_iterator &it,
																			std::vector<ParserJSON::t_token>::const_iterator const &end) const;
	void state_in_object(std::vector<ParserJSON::e_state> &states,
											 std::vector<ParserJSON::t_token>::const_iterator &it);
	void state_in_array(std::vector<ParserJSON::e_state> &states,
											std::vector<ParserJSON::t_token>::const_iterator &it);
	void state_in_value(std::vector<ParserJSON::e_state> &states,
											std::vector<ParserJSON::t_token>::const_iterator &it,
											std::vector<ParserJSON::t_token>::const_iterator const &end);
	bool token_is_open(t_lexem const &l) const;
	ParserJSON::t_lexem token_to_lexem(t_token const &token) const;
	void check_unique_keys() const;

	void parse();
	// Colpien
	ParserJSON();
	ParserJSON(ParserJSON const &rhs);
	ParserJSON &operator=(ParserJSON const &rhs);
};

std::ostream &operator<<(std::ostream &out, ParserJSON const &parser);

#endif