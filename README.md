# The Project: MyFTP
```
2nd year Epitech Project.
Implemented in C, this project serves as an FTP server that is compliant to RFC959.
The primary objective was to gain proficiency in socket programming and protocol implementation.
```

# Usage

```
./server [PORT] [PATH] -> path where server start.
```

# Commands
```
USER	Specify user for authentication
PASS	Specify password for authentication
CWD	  Change working directory
HELP	List available commands
NOOP	Do nothing
QUIT	Disconnection
PORT	Enable "active" mode for data transfer
PASV	Enable "passive" mode for data transfer
TYPE	Set type of transfer
DELE	Delete file on the server
PWD	  Print working directory
LIST	List files in the current working directory
RETR	Download file from server to client
STOR	Upload file from client to server
CDUP	Change to parent directory
```
