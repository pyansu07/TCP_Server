
# TCP Server

This project demonstrates how to build a basic TCP server in C, covering key concepts like socket programming, three-way handshake, and connection termination.

## Features  
- Sets up a TCP server using Winsock  
- Handles client connections  
- Sends and receives data  
- Gracefully terminates connections  

## Steps to Build  
1. **Setup Winsock:** Initialize the Winsock library.  
2. **Create a Socket:** Create a server socket using `socket()`.  
3. **Bind to IP/Port:** Assign an IP address and port using `bind()`.  
4. **Listen for Connections:** Use `listen()` to prepare the server for incoming requests.  
5. **Accept Clients:** Accept incoming connections using `accept()`.  
6. **Send and Receive Data:** Use `recv()` and `send()` for communication.  
7. **Close Connection:** Close sockets with `closesocket()`.

## How to Run  
   1. Clone this repository:  
   ```bash
   git clone https://github.com/yourusername/tcp-server-c.git
   cd tcp-server-c
   ```

   2. Compile the server:
   ```bash
   gcc -o tcp_server tcp_server.c -lws2_32
   ```
   3. Run the server:
   ```bash
   ./tcp_server
   ```
   4. Connect a client to the server (e.g., using `telnet`):
   ```bash
   telnet localhost <port>
   ```

## Key Learnings 
- Basics of socket programming 
- TCP connection setup: Three-way handshake 
- Graceful connection termination

  
![Screenshot (9)](https://github.com/user-attachments/assets/430727c8-de61-4106-993c-73d1a8100ddb)
