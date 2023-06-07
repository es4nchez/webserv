#include "ParserJSON.hpp"

// HELPER
bool parse_words(ParserJSON const &json, std::vector<ParserJSON::t_lexem>::const_iterator const &word, std::vector<std::string> &words)
{
	std::string tmp;

	if (ParserJSON::to_word(json, word, tmp))
		return (true);
	words.push_back(tmp);
	return (false);
}
