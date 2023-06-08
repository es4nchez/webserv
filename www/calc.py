#!/usr/bin/python

# Import modules for CGI handling 
import cgi, cgitb 

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

# Get data from fields
first_number = form.getvalue('first_number')
second_number = form.getvalue('second_number')
operator = form.getvalue('operator')
result = 0

if operator == '+':
    result = int(first_number) + int(second_number)

elif operator == '-':
    result = int(first_number) - int(second_number)

elif operator == '*':
    result = int(first_number) * int(second_number)

elif operator == '/':
    result = int(first_number) / int(second_number)

else:
    result = 'Operator invalid'


print('HTTP/1.1 200 OK\r\n')
print ("Content-type:text/html\r\n\r\n")
print ("<html>")
print ("<head>")
print ("<title>Calc</title>")
print ("</head>")
print ("<body>")
print (f"<h2>Hello result of {first_number} {operator} {second_number} = {result}</h2>")
print ("</body>")
print( "</html>")