# -*- coding: utf-8 -*-
"""
EPITECH PROJECT, 2024
client_module.py
Description:
Test file for parsing.py
"""

import unittest
from unittest.mock import patch
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from src.parsing import parse_arguments

class TestParsing(unittest.TestCase):
    @patch('sys.argv', ['../../zappy_ai', '-p', '12345', '-n', 'antoine', '-h', '127.0.0.1'])
    def test_parse_arguments(self):
        port, name, host = parse_arguments()
        self.assertEqual(port, 12345)
        self.assertEqual(name, 'antoine')
        self.assertEqual(host, '127.0.0.1')

if __name__ == '__main__':
    unittest.main()
