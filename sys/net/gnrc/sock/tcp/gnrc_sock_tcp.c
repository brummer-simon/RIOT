#include <errno.h>

#include "net/gnrc/tcp.h"
#include "net/sock/tcp.h"

#include "gnrc_sock_internal.h"

int sock_tcp_connect(sock_tcp_t *sock, const sock_tcp_ep_t *remote,
                     uint16_t local_port, uint16_t flags)
{
    (void) flags;
    int err = gnrc_tcp_open_active(&(sock->tcb), (const gnrc_tcp_ep_t *) remote, local_port);

    return err;
}

void sock_tcp_disconnect(sock_tcp_t *sock)
{
    gnrc_tcp_close(&(sock->tcb));
}

int sock_tcp_listen(sock_tcp_queue_t *queue, const sock_tcp_ep_t *local,
                    sock_tcp_t *queue_array, unsigned queue_len,
                    uint16_t flags)
{
    (void) queue;
    (void) local;
    (void) queue_array;
    (void) queue_len;
    (void) flags;
    return -ENOSYS;
}

void sock_tcp_stop_listen(sock_tcp_queue_t *queue)
{
    (void) queue;
}

int sock_tcp_get_local(sock_tcp_t *sock, sock_tcp_ep_t *ep)
{
    (void) sock;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_get_remote(sock_tcp_t *sock, sock_tcp_ep_t *ep)
{
    (void) sock;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_queue_get_local(sock_tcp_queue_t *queue, sock_tcp_ep_t *ep)
{
    (void) queue;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_accept(sock_tcp_queue_t *queue, sock_tcp_t **sock,
                    uint32_t timeout)
{
    (void) queue;
    (void) sock;
    (void) timeout;
    return -ENOSYS;
}

ssize_t sock_tcp_read(sock_tcp_t *sock, void *data, size_t max_len,
                      uint32_t timeout)
{
    (void) sock;
    (void) data;
    (void) max_len;
    (void) timeout;
    return -ENOSYS;
}

ssize_t sock_tcp_write(sock_tcp_t *sock, const void *data, size_t len)
{
    (void) sock;
    (void) data;
    (void) len;
    return -ENOSYS;
}
