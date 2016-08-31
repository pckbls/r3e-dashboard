import unittest
import json
import lib.r3e as r3e

class TestR3E(unittest.TestCase):
    def setUp(self):
        with open("tests/r3e.json") as data_file:
            self.data = json.load(data_file)
            self.binary_data = bytes.fromhex(self.data["binary"])
            self.result_real = self.data["struct"]
            self.result_parser = r3e.parse(self.binary_data)

    def test_r3e_shared_size(self):
        self.assertEqual(len(self.binary_data), r3e.shared_size)

    def test_parser(self):
        self.maxDiff = None
        self.assertDictEqual(self.result_real, self.result_parser)
