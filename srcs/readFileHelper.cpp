#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int	read_file(std::string const &file_path, std::string &config)
{
	std::ifstream ifs(file_path);
	std::ostringstream ostr;

	ostr << ifs.rdbuf();
	if (ostr.fail() || ifs.fail())
	{
		ifs.close();
		return (1);
	}
	config = ostr.str();
	return (0);
}