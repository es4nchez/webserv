# webserv => HTTP server in C++ 98

## Roadmap :

* [x] Create a function that creates a socket and binds it to a specific port. The function will wait for incoming connections.
    * [ ] Specify the port to bind ( now its 8080 by default)
    * [x] Listen to differents ports ?
        * [x] Ports

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

* [ ] Put settings into a containers ( map ?) and change all files ( damn )

* [x] Really use a cpp webserv class ( only one ? ) and not a kind of struct
    * [x] basic webserv class
    * [ ] More class ? For socket, response, errors, parsing ?

* [ ] ???

* [ ] WE SHOULD NEVER DIE

* [ ] Time to stress testing

## Testing

### From Navigator
    localhost:8080
    localhost:8080/
    localhost:8080/index.html
    localhost:8080/wkfnewjnf

### From command line
    curl -X GET localhost:8080
    curl -X DELETE localhost:8080
    curl -X PATCH localhost:8080
    curl -X ADJASID localhost:8080

    curl --resolve example.com:80:127.0.0.1 http://example.com/
   
   
   
   
![](https://giphy.com/gifs/spongebob-spongebob-squarepants-episode-1-3oKHW5ygEPHUNrb1SM)
