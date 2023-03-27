# webserv

## HTTP server in C++ 98

### Roadmap :

* [x] Create a function that creates a socket and binds it to a specific port. The function will wait for incoming connections.
    * [ ] Specify the port to bind ( now its 8080 by default)
    * [ ] Listen to multiple servers and ports ?

* [x] Create a function that takes incoming connections and reads the data from the socket. It parses the HTTP request and determines the appropriate response.
    * [ ] Handle differents http errors codes
    * [ ] Load default index.html ?
    * [x] GET
    * [ ] POST
    * [ ] DELETE

* [x] Create a function that sends the response to the client, with the correct HEADERS and BODY of response.
    * [ ] Upload files

* [x] All this in a while loop that waits for connections to respond

* [ ] Parse a config file or default config
    * [ ] port / host ( first is default)
    * [ ] limit client body size
    * [ ] errors pages
    * [ ] routes
    * [ ] CGI
    * [ ] ???

* [ ] ???

* [ ] WE SHOULD NEVER DIE

* [ ] STRESS TEST

* [ ] Time to testing
