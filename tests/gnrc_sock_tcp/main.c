/*
 * Copyright (C) 2018   Simon Brummer <simon.brummer@posteo.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "msg.h"
//#include "net/af.h"
#include "net/sock/tcp.h"
#include "net/gnrc/tcp.h"

#define MAIN_QUEUE_SIZE (8)
//#define BUFFER_SIZE (2049)



static sock_tcp_t sock;
//static char buffer[BUFFER_SIZE];


void dump_args(int argc, char **argv)
{
    printf("%s: ", argv[0]);
    printf("argc=%d", argc);
    for (int i = 0; i < argc; ++i) {
        printf(", argv[%d] = %s", i, argv[i]);
    }
    printf("\n");
}

/* API Export for test script */
/*
int buffer_init_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    memset(buffer, '\0', sizeof(buffer));
    return 0;
}
*/

/*
int buffer_get_max_size_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    printf("%s: returns %d\n", argv[0], BUFFER_SIZE - 1);
    return 0;
}
*/

/*
int buffer_write_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    size_t offset = atol(argv[1]);
    char *src = argv[2];

    size_t src_len = strlen(src);
    char *dst = buffer + offset;

    memcpy(dst, src, src_len);
    return 0;
}
*/

/*
int buffer_read_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    size_t offset = atol(argv[1]);
    size_t size = atol(argv[2]);

    // Calculate Start and End of readout
    char *begin = buffer + offset;
    char *end = begin + size;

    // Place temporary endmarker in buffer and print
    char tmp = *end;
    *end = '\0';

    printf("%s: <begin>%s<end>\n", argv[0], begin);

    *end = tmp;

    return 0;
}
*/

/*
int gnrc_tcp_ep_from_str_cmd(int argc, char **argv)
{
    dump_args(argc, argv);

    gnrc_tcp_ep_t ep;
    int err = gnrc_tcp_ep_from_str(&ep, argv[1]);
    switch (err) {
        case -EINVAL:
            printf("%s: returns -EINVAL\n", argv[0]);
            break;

        default:
            printf("%s: returns %d\n", argv[0], err);
    }

    if (err == 0) {
        char addr_as_str[IPV6_ADDR_MAX_STR_LEN];
        switch (ep.family) {
            case AF_INET6:
                printf("Family: AF_INET6\n");
                ipv6_addr_to_str(addr_as_str, (ipv6_addr_t *) ep.addr.ipv6,
                                 sizeof(addr_as_str));
                printf("Addr: %s\n", addr_as_str);
                break;

            case AF_INET:
                printf("Family: AF_INET\n");
                break;

            default:
                printf("Family: %d\n", ep.family);
        }
        printf("Port: %d\n", ep.port);
        printf("Netif: %d\n", ep.netif);
    }
    return err;
}
*/

/*
int gnrc_tcp_tcb_init_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    gnrc_tcp_tcb_init(&tcb);
    return 0;
}*/

int sock_tcp_connect_cmd(int argc, char **argv)
{
    dump_args(argc, argv);

    sock_tcp_ep_t remote;
    gnrc_tcp_ep_from_str((gnrc_tcp_ep_t *) &remote, argv[1]);
    uint16_t local_port = atol(argv[2]);
    uint16_t flags = atol(argv[3]);

    int err = sock_tcp_connect(&sock, &remote, local_port, flags);
    switch (err) {
        case -EADDRINUSE:
            printf("%s: returns -EADDRINUSE\n", argv[0]);
            break;

        case -EAFNOSUPPORT:
            printf("%s: returns -EAFNOSUPPORT\n", argv[0]);
            break;

        case -ECONNREFUSED:
            printf("%s: returns -ECONNREFUSED\n", argv[0]);
            break;

        case -EINVAL:
            printf("%s: returns -EINVAL\n", argv[0]);
            break;

        case -ENETUNREACH:
            printf("%s: returns -ENETUNREACH\n", argv[0]);
            break;

        case -ENOMEM:
            printf("%s: returns -ENOMEM\n", argv[0]);
            break;

        case -EPERM:
            printf("%s: returns -EPERM\n", argv[0]);
            break;

        case -ETIMEDOUT:
            printf("%s: returns -ETIMEOUT\n", argv[0]);
            break;

        default:
            printf("%s: returns %d\n", argv[0], err);
    }
    return err;
}

/*
int gnrc_tcp_open_passive_cmd(int argc, char **argv)
{
    dump_args(argc, argv);

    gnrc_tcp_ep_t local;
    gnrc_tcp_ep_from_str(&local, argv[1]);

    int err = gnrc_tcp_open_passive(&tcb, &local);
    switch (err) {
        case -EAFNOSUPPORT:
            printf("%s: returns -EAFNOSUPPORT\n", argv[0]);
            break;

        case -EINVAL:
            printf("%s: returns -EINVAL\n", argv[0]);
            break;

        case -EISCONN:
            printf("%s: returns -EISCONN\n", argv[0]);
            break;

        case -ENOMEM:
            printf("%s: returns -ENOMEM\n", argv[0]);
            break;

        default:
            printf("%s: returns %d\n", argv[0], err);
    }
    return err;
}
*/

/*
int gnrc_tcp_send_cmd(int argc, char **argv)
{
    dump_args(argc, argv);

    int timeout = atol(argv[1]);
    size_t to_send = strlen(buffer);
    size_t sent = 0;

    while (sent < to_send) {
        int ret = gnrc_tcp_send(&tcb, buffer + sent, to_send - sent, timeout);
        switch (ret) {
            case -ENOTCONN:
                printf("%s: returns -ENOTCONN\n", argv[0]);
                return ret;

            case -ECONNRESET:
                printf("%s: returns -ECONNRESET\n", argv[0]);
                return ret;

            case -ECONNABORTED:
                printf("%s: returns -ECONNABORTED\n", argv[0]);
                return ret;

            case -ETIMEDOUT:
                printf("%s: returns -ETIMEDOUT\n", argv[0]);
                return ret;
        }
        sent += ret;
    }

    printf("%s: sent %u\n", argv[0], (unsigned)sent);
    return sent;
}

int gnrc_tcp_recv_cmd(int argc, char **argv)
{
    dump_args(argc, argv);

    int timeout = atol(argv[1]);
    size_t to_receive = atol(argv[2]);
    size_t rcvd = 0;

    while (rcvd < to_receive) {
        int ret = gnrc_tcp_recv(&tcb, buffer + rcvd, to_receive - rcvd,
                                timeout);
        switch (ret) {
            case 0:
                printf("%s: returns 0\n", argv[0]);
                return ret;

            case -EAGAIN:
                printf("%s: returns -EAGAIN\n", argv[0]);
                continue;

            case -ETIMEDOUT:
                printf("%s: returns -ETIMEDOUT\n", argv[0]);
                continue;

            case -ENOTCONN:
                printf("%s: returns -ENOTCONN\n", argv[0]);
                return ret;

            case -ECONNRESET:
                printf("%s: returns -ECONNRESET\n", argv[0]);
                return ret;

            case -ECONNABORTED:
                printf("%s: returns -ECONNABORTED\n", argv[0]);
                return ret;
        }
        rcvd += ret;
    }

    printf("%s: received %u\n", argv[0], (unsigned)rcvd);
    return 0;
}
*/

int sock_tcp_disconnect_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    sock_tcp_disconnect(&sock);
    return 0;
}

/*
int gnrc_tcp_abort_cmd(int argc, char **argv)
{
    dump_args(argc, argv);
    gnrc_tcp_abort(&tcb);
    return 0;
}
*/

/* Exporting GNRC TCP Api to for shell usage */
static const shell_command_t shell_commands[] = {
    { "sock_tcp_connect", "Connect Endpoint", sock_tcp_connect_cmd},
    { "sock_tcp_disconnect", "Disconnect Endpoint", sock_tcp_disconnect_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
    msg_t main_queue[MAIN_QUEUE_SIZE];
    msg_init_queue(main_queue, sizeof(main_queue)/sizeof(main_queue[0]));
    printf("RIOT GNRC_SOCK_TCP test application\n");

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
