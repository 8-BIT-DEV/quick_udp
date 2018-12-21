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

    qu_handle server_handle;
    int success = qu_listen(&server_handle, 1996);
    assert(success);

    qu_handle client_handles[64];
    int client_count = 0;

    while (1)
    {
        char buffer[1024];
        memset(buffer, 0, 1024);
        qu_handle sender;
        if (qu_receive(&server_handle, &sender, buffer, 1024))
        {
            int client_already_connected = 0;
            for (int i = 0; i < client_count; ++i)
            {
                if (qu_compare(&client_handles[i], &sender))
                {
                    client_already_connected = 1;
                    printf("[%03d] %s\n", i, buffer);
                }
                else
                {
                    qu_send(&client_handles[i], buffer, 1024);
                }
            }

            if (!client_already_connected)
            {
                if (client_count < 64)
                {
                    printf("[%03d] JOINED\n", client_count);
                    client_handles[client_count] = sender;
                    printf("[%03d] %s\n", client_count, buffer);
                    ++client_count;
                }
                else
                {
                    qu_send(&sender, "FULL", 4);
                }
            }
        }
    }

    qu_shutdown();
}
