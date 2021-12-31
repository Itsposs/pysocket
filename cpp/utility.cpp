
#include "utility.h"
#include <string.h>


int s_recv(ZmqSock* zmqsock, ZmqMsg* zmqmsg)
{
    if(NULL == zmqsock || NULL == zmqmsg)
    {
        return -1;
    }

    int ret = -1;
    int len = sizeof(int);
    (void)len;

    void* sock = zmqsock->sock;
    do 
    {
        int type = zmqsock->iType;
        if(ZMQ_ROUTER == type)
        {
            errno = 0;
            printf("router:\n");

            if(zmq_recv(sock, zmqmsg->szSrc, sizeof(zmqmsg->szSrc), 0) < 0)
            {
                printf("recv msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }

            printf("recv: [%s].\n", zmqmsg->szSrc);
            if(zmq_recv(sock, NULL, 0, 0) < 0)
            {
                printf("recv msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("recv: [].\n");
        }
        else if(ZMQ_DEALER == type)
        {
            errno = 0;
            printf("dealer:\n");

            if(zmq_recv(sock, NULL, 0, 0) < 0)
            {
                printf("recv msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("recv: []\n");

        }
        else if(ZMQ_REQ == type)
        {
            printf("req:\n");
        }
        else if(ZMQ_REP == type)
        {
            printf("rep:\n");
        }
        else
        {
            printf("unknown type.\n");
        }

        if(zmq_recv(sock, zmqmsg->szDst, sizeof(zmqmsg->szDst), 0) < 0)
        {
            printf("send msg failed: [%s].\n", zmq_strerror(errno));
            break;
        }
        
        printf("recv: [%s].\n", zmqmsg->szSrc);
        if(zmq_recv(sock, NULL, 0, 0) < 0)
        {
            printf("recv msg failed: [%s].\n", zmq_strerror(errno));
            break;
        }
        printf("recv: [].\n");

        if(zmq_recv(sock, zmqmsg->szMsg, sizeof(zmqmsg->szMsg), 0) < 0)
        {
            printf("send msg failed: [%s].\n", zmq_strerror(errno));
            break;
        }
        printf("recv: [%s]\n", zmqmsg->szMsg);
        ret = 0;

    }while(0);

    return 0;
}

int s_send(ZmqSock* zmqsock, ZmqMsg* zmqmsg)
{
    if(NULL == zmqsock || NULL == zmqmsg)
    {
        return -1;
    }

    int ret = -1;
    int len = sizeof(int);
    (void)len;

    void* sock = zmqsock->sock;
    do 
    {
        int type = zmqsock->iType;
        if(ZMQ_ROUTER == type)
        {
            errno = 0;
            printf("router:\n");

            if(zmq_send(sock, zmqmsg->szDst, strlen(zmqmsg->szDst), ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }

            printf("send: [%s].\n", zmqmsg->szDst);
            if(zmq_send(sock, "", 0, ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }

            printf("send: [].\n");
            if(zmq_send(sock, zmqmsg->szSrc, strlen(zmqmsg->szSrc), ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("send: [%s].\n", zmqmsg->szSrc);

        }
        else if(ZMQ_DEALER == type)
        {
            errno = 0;
            printf("dealer:\n");

            if(zmq_send(sock, NULL, 0, ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("send: []\n");

            if(zmq_send(sock, zmqmsg->szDst, strlen(zmqmsg->szDst), ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("send: [%s].\n", zmqmsg->szDst);

        }
        else if(ZMQ_REQ == type || ZMQ_REP == type)
        {
            printf("rex:\n");
            if(zmq_send(sock, zmqmsg->szDst, strlen(zmqmsg->szDst), ZMQ_SNDMORE) < 0)
            {
                printf("send msg failed: [%s].\n", zmq_strerror(errno));
                break;
            }
            printf("send: [%s].\n", zmqmsg->szDst);
        }
        else
        {
            printf("unknown type.\n");
        }

        if(zmq_send(sock, NULL, 0, ZMQ_SNDMORE) < 0)
        {
            printf("send msg failed: [%s].\n", zmq_strerror(errno));
            break;
        }
        printf("send: [].\n");

        if(zmq_send(sock, zmqmsg->szMsg, strlen(zmqmsg->szMsg), 0) < 0)
        {
            printf("send msg failed: [%s].\n", zmq_strerror(errno));
            break;
        }
        printf("send: [%s]\n", zmqmsg->szMsg);
        ret = 0;

    }while(0);

    return ret;
}
