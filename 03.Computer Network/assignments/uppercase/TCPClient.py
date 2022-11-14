# TCPClient.py
from socket import *

serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

message = input("Input lowercase message: ")
clientSocket.send(message.encode())

modifiedMessage = clientSocket.recv(1024)
print("From Server: ", modifiedMessage.decode())

clientSocket.close()
