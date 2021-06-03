/*
    send.c
    Send a single udp message and exits.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define QUICK_UDP_IMPLEMENTATION
#include "../quick_udp.h"

int main(int argument_count, char ** arguments)
{
    qu_init();

    if (argument_count != 4) {
        puts("usage: address port message");
        return 1;
    }

    char * address = arguments[1];
    int port = atoi(arguments[2]);
    char * message = arguments[3];
    int message_length = strnlen(message, 200);

    if (!address || !port || !message || !message_length) {
        puts("usage: address port message");
        return 1;
    }

    qu_handle handle;
    int success = qu_connect(&handle, address, port);
    if (!success) {
        puts("An error occurred!\nusage: address port message");
        return 1;
    }

    int bytes_sent = qu_send(&handle, message, message_length);

    printf("Sent %d bytes to %s:%d\n", bytes_sent, address, port);

    qu_shutdown();
}
