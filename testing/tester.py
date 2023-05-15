import unittest
import requests

get_endpoint = "/42lWatch.html"

get_cgi = "/cgi_script.py"

post_endpoint = "/postex.html"

class TestWebserver(unittest.TestCase):

    BASE_URL = 'http://localhost:8080'

    def test_get(self):
        response = requests.get(f'{self.BASE_URL}')
        self.assertEqual(response.status_code, 200)

    def test_get2(self):    
        response = requests.get(f'{self.BASE_URL}{get_endpoint}')
        self.assertEqual(response.status_code, 200)

    def test_get3(self):    
        response = requests.get(f'{self.BASE_URL}{get_cgi}')
        self.assertEqual(response.status_code, 200)


    def test_post(self):
        data = {"name": "eduardo"}
        response = requests.post(f'{self.BASE_URL}/post.py', json=data)
        self.assertEqual(response.status_code, 200)

    # def test_delete(self):
    #     response = requests.delete(f'{self.BASE_URL}/path')
    #     self.assertEqual(response.status_code, 200)


if __name__ == '__main__':
    unittest.main()
