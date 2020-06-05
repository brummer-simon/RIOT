#include <errno.h>
#include <assert.h>

#include "net/gnrc/tcp.h"
#include "net/sock/tcp.h"

#include "gnrc_sock_internal.h"

int sock_tcp_connect(sock_tcp_t *sock, const sock_tcp_ep_t *remote,
                     uint16_t local_port, uint16_t flags)
{
    assert(sock != NULL);
    assert(remote != NULL);
    assert(remote->port != 0);

    (void) flags;

    gnrc_tcp_tcb_init(&(sock->tcb));

    int err = gnrc_tcp_open_active(&(sock->tcb), (const gnrc_tcp_ep_t *) remote,
                                   local_port);

    // TODO: Handle error codes correctly

    // Differences regarding GNRC_TCP Error codes
    // GNRC_TCP_API:
    // -EADDRINUSE if @p local_port is already used by another connection.
    // -EISCONN if TCB is already in use.

    // SOCK_TCP_API:
    // -EADDRINUSE, if `(flags & SOCK_FLAGS_REUSE_EP) == 0` and @p local_port is already used elsewhere
    // -EINVAL, if sock_tcp_ep_t::netif of @p remote is not a valid interface.
    // -ENETUNREACH, if network defined by @p remote is not reachable.
    // -EPERM, if connections to @p remote are not permitted on the system (e.g. by firewall rules).
    return err;
}

void sock_tcp_disconnect(sock_tcp_t *sock)
{
    assert(sock != NULL);
    gnrc_tcp_close(&(sock->tcb));
}

int sock_tcp_listen(sock_tcp_queue_t *queue, const sock_tcp_ep_t *local,
                    sock_tcp_t *queue_array, unsigned queue_len,
                    uint16_t flags)
{
    assert(queue != NULL);
    assert(local != NULL);
    assert(local->port != 0);
    assert(queue_array != NULL);
    assert(queue_len != 0);

    (void) queue;
    (void) local;
    (void) queue_array;
    (void) queue_len;
    (void) flags;
    return -ENOSYS;
}

void sock_tcp_stop_listen(sock_tcp_queue_t *queue)
{
    assert(queue != NULL);
    (void) queue;
}

int sock_tcp_get_local(sock_tcp_t *sock, sock_tcp_ep_t *ep)
{
    assert(sock != NULL);
    assert(ep != NULL);

    (void) sock;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_get_remote(sock_tcp_t *sock, sock_tcp_ep_t *ep)
{
    assert(sock != NULL);
    assert(ep != NULL);

    (void) sock;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_queue_get_local(sock_tcp_queue_t *queue, sock_tcp_ep_t *ep)
{
    assert(queue != NULL);
    assert(ep != NULL);

    (void) queue;
    (void) ep;
    return -ENOSYS;
}

int sock_tcp_accept(sock_tcp_queue_t *queue, sock_tcp_t **sock,
                    uint32_t timeout)
{
    assert(queue != NULL);
    assert(sock != NULL);

    (void) queue;
    (void) sock;
    (void) timeout;
    return -ENOSYS;
}

ssize_t sock_tcp_read(sock_tcp_t *sock, void *data, size_t max_len,
                      uint32_t timeout)
{
    assert(sock != NULL);
    assert(data != NULL);
    assert(max_len > 0);

    (void) sock;
    (void) data;
    (void) max_len;
    (void) timeout;
    return -ENOSYS;
}

ssize_t sock_tcp_write(sock_tcp_t *sock, const void *data, size_t len)
{
    assert(sock != NULL);
    assert(data != NULL);
    assert(len > 0);

    // No need for remapping error codes, they are the same except:
    // 1) -ETIMEDOUT (Can't be returned, timeout is infinite)
    // 2) -ENOMEM (Can't be returned, gnrc preallocated receive buffer)
    return gnrc_tcp_send(&(sock->tcb), data, len, 0);
}
