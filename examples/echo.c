/*
    echo.c
    Listens on a port and sends anything received back to its sender.
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define QUICK_UDP_IMPLEMENTATION
#include "../quick_udp.h"

int main()
{
    qu_init();

    qu_handle server_handle;
    int success = qu_listen(&server_handle, 1999);
    assert(success);

    while (1)
    {
        char buffer[1024];
        memset(buffer, 0, 1024);

        // This call to qu_receive will block until a packet is received.
        qu_handle sender;
        int bytes_received = qu_receive(&server_handle, &sender, buffer, 1024);
        if (bytes_received > 0) {
            qu_send(&sender, buffer, bytes_received);
        }
    }

    qu_shutdown();
}
