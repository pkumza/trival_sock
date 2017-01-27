# Trival Sock

a test for socket of version C.

# Usage

$make
$./server
# Use another terminal
$./client localhost 2017 "A Message From A Client."

After that client will get:

```bash
Zamac:trival_sock zach$ ./client localhost 2017 "A Message From A Client."
Echo string received:A Message From A Client.
```

Server will get:

```bash
Connection form 127.0.0.1, port 56359 
```

Yes, the port is randomly generated.
