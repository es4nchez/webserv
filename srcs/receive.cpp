#include "webserv.hpp"

std::string Webserv::getRequestMethod(const std::string& headers)
{
    std::string::size_type space_pos = headers.find(' ');
    if (space_pos == std::string::npos) {
        // Throw an error or handle this case as you see fit
        std::cerr << "Invalid HTTP request line" << std::endl;
        return "";
    }
    return headers.substr(0, space_pos);
}

int Webserv::getContentLengthFromHeaders(const std::string& headers)
{
    std::string::size_type content_length_pos = headers.find("Content-Length: ");
    if (content_length_pos == std::string::npos) {
        // No Content-Length header found
        return -1;
    }
    
    std::string::size_type end_of_line_pos = headers.find("\r\n", content_length_pos);
    if (end_of_line_pos == std::string::npos) {
        // Invalid HTTP headers
        std::cerr << "Invalid HTTP headers" << std::endl;
        return -1;
    }

    std::string content_length_str = headers.substr(content_length_pos + 16, end_of_line_pos - content_length_pos - 16);
    return std::stoi(content_length_str);
}


std::string Webserv::receive(int i, int sockfd)
{
    std::string buffer;
    while (true)
    {
        std::cout << "total : " << w_client_sockfd.size() << std::endl;
        std::cout << "i : " << i << std::endl;
        char temp_buffer[1000000] = {0};
        int bytes_received = recv(sockfd, temp_buffer, sizeof(temp_buffer) - 1, 0);
        std::cout << "we received !!!" << std::endl;
        if (bytes_received <= 0)
        {
            if (bytes_received < 0)
                std::cerr << "Error receiving data" << std::endl;
            break;
        }
        buffer.append(temp_buffer, bytes_received);

        // Check if we've received the end of the HTTP headers
        std::string::size_type header_end = buffer.find("\r\n\r\n");
        if (header_end != std::string::npos)
        {
            // Parse headers
            std::string headers = buffer.substr(0, header_end);
            std::string request_method = getRequestMethod(headers);
            int content_length = getContentLengthFromHeaders(headers);

            // Check if there's a request body and if we've received it all
            if ((request_method == "POST") && content_length >= 0)
            {
                if (buffer.size() >= header_end + 4 + content_length)
                    break;
            }
            else
                break;
        }
    }
    return buffer;
}
