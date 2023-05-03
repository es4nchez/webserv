#!/usr/bin/env python3

import cgi 


form = cgi.FieldStorage()

last_name  = form.getvalue('NAME')


# Send a response back to the client
print('HTTP/1.1 200 OK\n\n')
print("<html><head><title>POST Request Example</title></head><body>")
print("<h1>POST Request Example</h1>")
print("<p>Received form data:</p>")
print("<ul>")
print(f"<li>Name: {name}</li>")
# print(f"<li>Email: {email}</li>")
# print(f"<li>Email: {message}</li>")
print("</ul>")
print("</body></html>")