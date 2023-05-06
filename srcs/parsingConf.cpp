#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "webserv.hpp"

enum e_token
{
	OPEN_SQUARE = '[',	 //[
	CLOSE_SQUARE = ']',	 //]
	OPEN_BRACKET = '{',	 //{
	CLOSE_BRACKET = '}', //}
	COLON = ':',				 //:
	COMMA = ',',				 //,
	QUOTE = '\"',				 //"

	WHITE,
	NL = '\n',
	CHAR,

	// lexems
	KEY,		//"nospace"
	WORD,		//"can space"
	BOOL,		// true false
	NUMBER, //*[0-9]
};

struct s_token
{
	enum e_token token;
	std::string value;
} typedef t_token;

enum e_state
{
	IN_VALUE,
	IN_OBJECT,
	IN_ARRAY,
	IN_KEY
};

enum e_token get_enum(char c)
{
	switch (c)
	{
	case OPEN_SQUARE:
		return OPEN_SQUARE;
		break;
	case CLOSE_SQUARE:
		return CLOSE_SQUARE;
		break;
	case OPEN_BRACKET:
		return OPEN_BRACKET;
	case CLOSE_BRACKET:
		return CLOSE_BRACKET;
	case COLON:
		return COLON;
	case COMMA:
		return COMMA;
	case QUOTE:
		return QUOTE;
	case NL:
		return NL;
	}
	if (isblank(c))
		return (WHITE);
	if (isdigit(c))
		return (NUMBER);
	return CHAR;
}

void skip_white_and_nl(std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	for (; it != end && (it->token == WHITE || it->token == NL); ++it)
	{
	}
}

t_token parse_string(std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	t_token t;

	t.token = WORD;
	t.value = "";
	if (it->token != QUOTE)
		throw("expected OPEN QUOTE");
	++it;
	for (; it != end && it->token != QUOTE && it->token != NL; ++it)
		t.value.push_back(it->value[0]);
	if (it->token != QUOTE)
		throw("expected CLOSE QUOTE");
	++it;
	return t;
}

t_token parse_bool(std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	static const std::string true_litteral("true");
	static const std::string false_litteral("false");
	t_token t = {.token = BOOL, .value = ""};
	size_t i = 0;

	switch (it->value[0])
	{
	case 't':
		i = true_litteral.length();
		break;
	case 'f':
		i = false_litteral.length();
		break;
	}

	for (size_t j = 0; it != end && j < i; ++j)
	{
		t.value.push_back(it->value[0]);
		++it;
	}
	if (t.value.compare(true_litteral) != 0 && t.value.compare(false_litteral) != 0)
		throw("unexpected BOOL");
	return t;
}

t_token parse_number(std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	t_token t;

	t.token = NUMBER;
	t.value = "";
	for (; it != end && isdigit(it->value[0]); ++it)
		t.value.push_back(it->value[0]);
	return t;
}

t_token state_parse_key(std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	t_token t;
	t.token = KEY;
	t.value = "";

	if (it->token != QUOTE)
		throw "expected key open_quote KEY";
	++it;
	for (; it != end && it->token == CHAR; ++it)
		t.value.push_back(it->value[0]);
	if (it->token != QUOTE)
		throw "expected close_quote KEY";
	++it;
	skip_white_and_nl(it, end);
	if (it->token != COLON)
		throw "expected colon KEY";
	++it;
	return t;
}

void state_in_object(std::vector<e_state> &states, std::vector<t_token> &lexems, std::vector<t_token>::const_iterator &it)
{
	switch (it->token)
	{
	case CLOSE_BRACKET:
		lexems.push_back(*it);
		states.pop_back();
		break;
	case COMMA:
		if (lexems.back().token == OPEN_BRACKET)
			throw("unexpected comma OBJECT");
		states.push_back(IN_KEY);
		break;
	default:
		throw("unexpected OBJECT");
	}
	++it;
}

void state_in_array(std::vector<e_state> &states, std::vector<t_token> &lexems, std::vector<t_token>::const_iterator &it)
{
	switch (it->token)
	{
	case CLOSE_SQUARE:
		lexems.push_back(*it);
		states.pop_back();
		break;
	case COMMA:
		if (lexems.back().token != OPEN_SQUARE)
		{
			states.push_back(IN_VALUE);
			break;
		}
	default:
		throw("unexpected ARRAY");
	}
	++it;
}

void state_in_value(std::vector<e_state> &states, std::vector<t_token> &lexems, std::vector<t_token>::const_iterator &it, std::vector<t_token>::const_iterator const &end)
{
	switch (it->token)
	{
	case OPEN_BRACKET:
		lexems.push_back(*it);
		states.pop_back();
		states.push_back(IN_OBJECT);
		skip_white_and_nl(it, end);
		++it;
		if (it->token == CLOSE_BRACKET)
		{
		}
		else
			states.push_back(IN_KEY);
		break;
	case OPEN_SQUARE:
		lexems.push_back(*it);
		states.pop_back();
		states.push_back(IN_ARRAY);
		++it;
		skip_white_and_nl(it, end);
		if (it->token == CLOSE_SQUARE) // empty array
		{
		}
		else
			states.push_back(IN_VALUE);
		break;
	case QUOTE:
		lexems.push_back(parse_string(it, end));
		states.pop_back();
		break;
	case NUMBER:
		lexems.push_back(parse_number(it, end));
		states.pop_back();
		break;
	case CHAR:
		lexems.push_back(parse_bool(it, end));
		states.pop_back();
		break;
	default:
		throw("unexpected VALUE");
	}
}

void lexer(std::vector<t_token> &lexems, std::vector<t_token> &tokens)
{
	std::vector<e_state> states;
	std::vector<t_token>::const_iterator it = tokens.begin();

	skip_white_and_nl(it, tokens.cend());
	if (it->token != OPEN_BRACKET)
		throw("expected global OPEN_BRACKET");
	lexems.push_back(*it);
	states.push_back(IN_OBJECT);
	states.push_back(IN_KEY);
	++it;
	while (it != tokens.cend())
	{
		skip_white_and_nl(it, tokens.cend());
		if (states.empty())
			break;
		switch (states.back())
		{
		case IN_OBJECT:
			state_in_object(states, lexems, it);
			break;
		case IN_ARRAY:
			state_in_array(states, lexems, it);
			break;
		case IN_VALUE:
			state_in_value(states, lexems, it, tokens.cend());
			break;
		case IN_KEY:
			lexems.push_back(state_parse_key(it, tokens.cend()));
			states.pop_back();
			states.push_back(IN_VALUE);
			break;
		default:
			throw("unexpected GLOBAL");
		}
	}
	if (lexems.back().token != CLOSE_BRACKET)
		throw("expected CLOSE_BRACKET");
}

void tokenizer(std::string const &file, std::vector<t_token> &tokens)
{
	t_token t;
	for (std::string::const_iterator it = file.cbegin(); it != file.cend(); ++it)
	{
		enum e_token e = get_enum(*it);
		t.value = *it;
		t.token = e;
		tokens.push_back(t);
	}
	if (tokens.empty())
		throw("tokenizer expected something");
}

// return
bool	search_key(std::vector<t_token>::iterator start, std::vector<t_token>::iterator const &end,
								std::string const &key,
								std::vector<t_token>::iterator &dst)
{
	
	return (true);
}

int parse(std::vector<t_token> &lexems)
{
	std::vector<t_token>::iterator dst;

	if (search_key(lexems.begin(), lexems.end(), "servers", dst))
		throw ("key not_found servers");
	
}

int parse_server_configuration(std::string const &file_path)
{
	std::string file;
	std::vector<t_token> tokens;
	std::vector<t_token> lexems;

	if (read_file(file_path, file))
	{
		std::cerr << "parseConf: configuration file: " << file_path << std::endl;
		return (1);
	}
	tokenizer(file, tokens);
	lexer(lexems, tokens);
	parse(lexems);
	std::cout << std::endl;
	return (0);
}