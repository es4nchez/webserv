#include "ParserJSON.hpp"
#include "server_conf.hpp"

// HELPER
bool parse_words(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const &word, std::vector<std::string> &words)
{
	std::string tmp;

	if (parse_word(json, word, tmp))
		return (true);
	words.push_back(tmp);
	return (false);
}

bool parse_word(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const & word, std::string &dst)
{
	std::string tmp;
	
	(void) json;
	if (word->lexem != ParserJSON::WORD || has_space(word->value) || word->value.empty())
		return (true);
	dst = tmp;
	return (false);
}
