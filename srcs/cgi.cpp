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

void CGI::handle_cgi_request(int sockfd, const std::string& query_string, char **wenvp)
{
    (void) query_string;
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

        char* args[] = { const_cast<char*>(PYTHON), const_cast<char*>(query_string.c_str()), nullptr };
        execve(PYTHON, args, wenvp);
        std::cerr << "Error executing CGI program: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    close(pipefd[1]);

    char buffer[1024];
    int bytes_read;

    while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        write(sockfd, buffer, bytes_read);
    }
    if (bytes_read == -1)
        std::cerr << "Error reading CGI output: " << strerror(errno) << std::endl;
    close(pipefd[0]);

}

bool CGI::is_cgi_request(const std::string& request_path)
{
    if (request_path.size() <= 1)
        return false; 
    const std::string py_extension = ".py";
    const std::string& ext = request_path.substr(request_path.find_last_of('.'));
    if (ext == py_extension) {
        return true;
    }
    return false;
}