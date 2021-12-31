
//send1.cpp

#include <zmq.h>
#include <string.h>
#include "utility.h"


int main(int argc, char* argv[])
{
    const char* paddr = "ipc://drd.ipc";
    void* pctx = zmq_ctx_new();
    void* psock = zmq_socket(pctx, ZMQ_DEALER);

    int timeout = 5000;
    if (zmq_setsockopt(psock, ZMQ_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    const char* pname = "send";
    if(zmq_setsockopt(psock, ZMQ_IDENTITY, pname, strlen(pname)) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    if(zmq_connect(psock, paddr) < 0)
    {
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return -1;
    }

    printf("connect to [%s].\n", paddr);

    ZmqSock zmqsock;
    zmqsock.iType = ZMQ_DEALER;
    zmqsock.sock = psock;

    while(true)
    {
        static unsigned int i = 0;
        
        ZmqMsg zmsg;
        memset(&zmsg, 0, sizeof(zmsg));
        snprintf(zmsg.szDst, sizeof(zmsg.szDst), "recv");
        snprintf(zmsg.szMsg, sizeof(zmsg.szMsg), "hello world : %3d", i++);

        printf("enter to send...\n");
        if(s_send(&zmqsock, &zmsg) < 0)
        {
            fprintf(stderr, "send message failed.\n");
            return -1;
        }
        printf("------------------------------------------------\n");
    }
    zmq_close(psock);
    zmq_ctx_destroy(pctx);

    return 0;
}
