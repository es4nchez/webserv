#include "webserv.hpp"
#include "cgi.hpp"

CGI::CGI()
{
    return;
}

CGI::~CGI()
{
    return;
}

void CGI::handle_cgi_request(int sockfd, const std::string& cgi_path, char **wenvp)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "Error creating pipe: " << strerror(errno) << std::endl;
        return;
    }

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Error forking process: " << strerror(errno) << std::endl;
        return;
    }

    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        char* args[] = { const_cast<char*>(PYTHON), const_cast<char*>(cgi_path.c_str()), NULL};
        execve(PYTHON, args, wenvp);
        std::cerr << "Error executing CGI program: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    close(pipefd[1]);

    std::string status = "HTTP/1.1 200 OK\n\n";
    write(sockfd, status.c_str(), status.size());

    char buffer[1024];
    int bytes_read;

    while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        write(sockfd, buffer, bytes_read);
    }
    if (bytes_read == -1)
        std::cerr << "Error reading CGI output: " << strerror(errno) << std::endl;
    close(pipefd[0]);

}

#include <algorithm>
#include <vector>

bool CGI::is_cgi_request(const std::string& request_path)
{
    if (request_path.size() <= 1)
        return false;

    std::vector<std::string> cgi_extensions;
    cgi_extensions.push_back(".py");
    cgi_extensions.push_back(".cgi");

    size_t dot_pos = request_path.find_last_of('.');
    if (dot_pos == std::string::npos)
        return false;

    std::string ext = request_path.substr(dot_pos);


    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    return std::find(cgi_extensions.begin(), cgi_extensions.end(), ext) != cgi_extensions.end();
}
