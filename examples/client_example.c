/*
    server_example.c
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define QUICK_UDP_IMPLEMENTATION
#include "../quick_udp.h"

int main()
{
    qu_init();

    // Set up a handle that will allow
    qu_handle handle;
    int success = qu_connect(&handle, "localhost", 1996);
    assert(success);

    // Send the server anything so that it has this client's address.
    qu_send(&handle, (void *)"Hello", 5);

    // Recieve any incoming packets and print then.
    while (1)
    {
        char buffer[1024];
        memset(buffer, 0, 1024);

        // This call to qu_receive will block, so we don't have to
        // worry about high CPU usage in this loop.
        int bytes_recieved = qu_receive(&handle, NULL, buffer, 1024);
        if (bytes_recieved > 0)
        {
            puts(buffer);
        }
    }

    qu_shutdown();
}
