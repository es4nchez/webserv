#include "webserv.hpp"
#include "CGI.hpp"

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
    // Construct the command line to execute the Python script
    char *args[] = { const_cast<char*>(CGI_PATH), nullptr };
    std::cout << "args :" << args << std::endl;
    // Spawn a new process to execute the command
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process: execute the command
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(sockfd, STDIN_FILENO);
        dup2(sockfd, STDOUT_FILENO);
        execve("python3", args, wenvp);
        exit(0);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else
        perror("fork");
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