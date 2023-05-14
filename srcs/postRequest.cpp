#include "webserv.hpp"

std::string     Webserv::parseBody(std::string request_body)
{
    std::string::size_type data_start_pos = request_body.find("\r\n\r\n");
    if (data_start_pos == std::string::npos) {
        // Handle error: no blank line found
        std::cerr << "Invalid multipart/form-data request body: no blank line found" << std::endl;
        return "";
    }
    std::string fileData = request_body.substr(data_start_pos + 4);
    return fileData;
}

std::string     Webserv::getFilename(std::string request_data)
 {
    std::string::size_type disposition_start_pos = request_data.find("Content-Disposition: ");
    if (disposition_start_pos == std::string::npos) {
        std::cerr << "Invalid multipart/form-data request body: no Content-Disposition header found" << std::endl;
        return "";
    }

    std::string::size_type filename_start_pos = request_data.find("filename=\"", disposition_start_pos);
    if (filename_start_pos == std::string::npos) {
        std::cerr << "Invalid multipart/form-data request body: no filename found" << std::endl;
        return "";
    }

    std::string::size_type filename_end_pos = request_data.find("\"", filename_start_pos + 10);
    if (filename_end_pos == std::string::npos) {
        std::cerr << "Invalid multipart/form-data request body: no end quote found for filename" << std::endl;
        return "";
    }

    return request_data.substr(filename_start_pos + 10, filename_end_pos - filename_start_pos - 10);
}



void    Webserv::parsePostRequest(std::string request, int fd)
{
    (void) fd;

    std::cout << std::endl << request << std::endl;
    std::string request_body = request.substr(request.find("\r\n\r\n") + 4);


    std::string request_data = parseBody(request_body);
	  std::string boundary = request.substr(request.find("boundary") + 11, 55);
	  std::cout << "BOUND : " << "<<" << boundary << boundary.size() << ">>" << std::endl;
	  std::string file_data = request_data.substr(0, (request_data.size() - boundary.size()) - 8);
    std::string filename = getFilename(request);
	  std::cout << "FILENAME : " << filename << std::endl;
    std::cout << "file DATA : <<" << file_data << ">>" << std::endl;

    std::string path = "www/upload/" + filename;
    std::ofstream file(path, std::ios::binary);



    file.write(file_data.c_str(), file_data.size());
    file.close();

}