# webserv
HTTP server in C++ 98

Roadmap :

- Create a function that creates a socket and binds it to a specific port. The function will wait for incoming connections. DONE
    - specify the port to bind ( now its 8080 by default)

- Create a function that takes incoming connections and reads the data from the socket. It parses the HTTP request and determines the appropriate response DONE

- Create a function that sends the response to the client, with the correct HEADERS and BODY of response. DONE

- All this in a while loop that waits for connections to respond DONE

- Time to testing
