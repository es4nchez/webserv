#!/bin/bash

SERVER="http://localhost:8080"

# Testing GET request
echo "Testing GET request:"
curl -I -X GET "$SERVER/cgi_script.py"

echo -e "\n"

# Testing POST request
echo "Testing POST request:"
curl -i -X POST -d "name=test1&email=test2%40gmail.com&message=test3" "$SERVER/post.py"

echo -e "\n"

# Testing DELETE request
# echo "Testing DELETE request: $SERVER/42lWatch.py"
# curl -I -X DELETE "$SERVER/test_cgi.py"

# echo -e "\n"

# echo "Testing DELETE request: $SERVER/test_cgi.py"
# curl -I -X DELETE "$SERVER/test_cgi.py"

echo -e "\n"

echo "Testing PATCH request: $SERVER/postex.html"
curl -I -X PATCH "$SERVER/postex.py"

echo -e "\n\n"