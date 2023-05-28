#include <string>
#include <sstream>
#include <fstream>

std::string read_file(std::string const &file_path)
{
	std::ifstream ifs(file_path);
	std::ostringstream ostr;

	if (ifs.fail())
		throw "failed to open file";
	if (ifs.eof())
		return "";
	ostr << ifs.rdbuf();
	if (ostr.fail() || ifs.fail())
		throw "error occured";
	return ostr.str();
}