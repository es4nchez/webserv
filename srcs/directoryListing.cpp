#include "webserv.hpp"

std::string Webserv::listFilesInDirectory(const std::string& directoryPath)
{
    DIR* dir = opendir(directoryPath.c_str());
    if (dir == NULL) {
        std::cerr << "Could not open directory: " << directoryPath << std::endl;
        return "";
    }

    std::string html = "<html>\n<head><title>Directory Listing</title></head>\n<body>\n<h1>Directory Listing for " + directoryPath + "</h1>\n<ul>\n";
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip the special entries "." and "..".
        if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
            html += "<li><a href=\"" + std::string(entry->d_name) + "\">" + std::string(entry->d_name) + "</a></li>\n";
        }
    }

    html += "</ul>\n</body>\n</html>";

    closedir(dir);
    return html;
}


void Webserv::directoryListing(s_request *requestData, int fd)
{
    (void)fd;
    std::string dirPath = this->rootPath + requestData->addr.substr(1, requestData->addr.size());

    std::string list = listFilesInDirectory(dirPath); 
    // std::cout << response << std::endl;

    std::string base = "HTTP/1.1 200 OK\n\n";
    std::string response = base + list;

    send(client_sockfd[fd], response.c_str(), response.size(), 0);
}