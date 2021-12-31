
//router1.cpp

#include <zmq.h>
#include <string.h>
#include "utility.h"


int main(int argc, char* argv[])
{
    const char* paddr = "ipc://drd.ipc";
    void* pctx = zmq_ctx_new();
    void* psock = zmq_socket(pctx, ZMQ_ROUTER);

    int timeout = -1;
    if (zmq_setsockopt(psock, ZMQ_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    const char* pname = "router";
    if(zmq_setsockopt(psock, ZMQ_IDENTITY, pname, strlen(pname)) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    if(zmq_bind(psock, paddr) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    printf("bind at [%s].\n", paddr);

    ZmqSock zmqsock;
    zmqsock.iType = ZMQ_ROUTER;
    zmqsock.sock = psock;

    while(true)
    { 
        errno = 0;
        printf("waitting for ...\n");

        ZmqMsg zmsg;
        memset(&zmsg, 0, sizeof(zmsg));

        if(s_recv(&zmqsock, &zmsg) < 0)
        {
            fprintf(stderr, "error: %s\n", zmq_strerror(errno));
            continue;
        }
        printf("------------------------------------------------\n");

        if(s_send(&zmqsock, &zmsg) < 0)
        {
            fprintf(stderr, "error: %s\n", zmq_strerror(errno));
            continue;
        }
        printf("------------------------------------------------\n");
    }
    zmq_close(psock);
    zmq_ctx_destroy(pctx);

    return 0;
}
