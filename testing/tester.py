import unittest
import requests

BASE_URL = 'http://localhost:8080'

get_endpoint = "/42lWatch.html"

post_endpoint = "/postex.html"

class TestWebserver(unittest.TestCase):

    def test_get(self):
        response = requests.get(f'{self.BASE_URL}{get_endpoint}')
        self.assertEqual(response.status_code, 200)

    def test_get2(self):    
        response = requests.get(f'{self.BASE_URL}')
        self.assertEqual(response.status_code, 200)


    # def test_post(self):
    #     data = {"key": "value"}
    #     response = requests.post(f'{self.BASE_URL}/path', json=data)
    #     self.assertEqual(response.status_code, 200)

    # def test_delete(self):
    #     response = requests.delete(f'{self.BASE_URL}/path')
    #     self.assertEqual(response.status_code, 200)


if __name__ == '__main__':
    unittest.main()
