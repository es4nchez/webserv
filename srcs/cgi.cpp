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

void CGI::handle_cgi_request(int sockfd, const std::string& cgi_path, char **_wenvp)
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        printf("Error creating pipe: %s\n", strerror(errno));
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        printf("Error forking process: %s\n", strerror(errno));
        return;
    }

    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        char* args[] = { const_cast<char*>(PYTHON), const_cast<char*>(cgi_path.c_str()), NULL};
        execve(PYTHON, args, _wenvp);
        printf("Error executing CGI program: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);

    std::string status = "HTTP/1.1 508 OK\n\n";
    write(sockfd, status.c_str(), status.size());

    int wpid, Stat;
    std::time_t start_time = std::time(NULL);
    const int timeout = 5;

    wpid = waitpid(pid, &Stat, WNOHANG);
    while (wpid == 0 && (std::time(NULL) - start_time) <= timeout) {
        std::time_t current_time = std::time(NULL);
        if (current_time - start_time < timeout) {
            char buffer[1024];
            int bytes_read;

            while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
                write(sockfd, buffer, bytes_read);
            }

            if (bytes_read == -1 && errno != EAGAIN) {
                printf("Error reading CGI output: %s\n", strerror(errno));
                break;
            }
        }
        else {
            printf("CGI execution time exceeded the limit. Terminating process.\n");
            kill(pid, SIGKILL);
            break;
        }

        wpid = waitpid(pid, &Stat, WNOHANG);
    }

    close(pipefd[0]);

    if (WIFEXITED(Stat)) {
        printf("Child exited, status=%d\n", WEXITSTATUS(Stat));
    }
    else if (WIFSIGNALED(Stat)) {
        printf("Child was terminated with a status of: %d\n", WTERMSIG(Stat));
    }
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
