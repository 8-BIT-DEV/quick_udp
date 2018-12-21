# Quick UDP
A simple single-header library for UDP networking.

- UDP only.
- Works on UNIX (Linux, macOS, BSD, ...) and Windows.
- Supports IPv4 and IPv6.
- No malloc - you supply storage for everything.
- Complete flow control (no call-backs), with non-blocking and blocking modes.
- No protocol, just sending and receiving of UDP packets.
- Public domain.

To build on Windows link to Winsock2 (`Ws2_32`).

## Examples
See [`examples/`](https://github.com/benhenshaw/quick_udp/tree/master/examples) for more.

#### Usage
Include the file like this in ONE source file then use as a normal header file in any others:
```C
#define QUICK_UDP_IMPLEMENTATION
#include "quick_udp.h"
```

#### Send a packet.
```C
qu_init();

qu_handle handle;
int success = qu_connect(&handle, "localhost", 1996);
if (!success) exit(1);
qu_send(&handle, "Hello", 5);

qu_shutdown();
```

#### Receive a packet.
```C
qu_init();

qu_handle handle;
int success = qu_listen(&handle, 1996);
if (!success) exit(1);

char buffer[1024];
memset(buffer, 0, 1024);

qu_handle sender;
qu_receive(&handle, &sender, buffer, 1024 - 1);

puts(buffer);

qu_shutdown();
```

## Entire API

```C
int qu_init(void);
int qu_shutdown(void);
int qu_listen(qu_handle * handle, int port);
int qu_connect(qu_handle * handle, char * address, int port);
void qu_close(qu_handle * handle);
int qu_receive(qu_handle * handle, qu_handle * sender, void * buffer, size_t buffer_length);
int qu_send(qu_handle * handle, void * data, int byte_count);
int qu_disable_blocking(qu_handle * handle, int disable_blocking);
int qu_wait(qu_handle * handle, int timeout_ms);
int qu_compare(qu_handle * a, qu_handle * b);
```
