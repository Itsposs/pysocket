
//utility.h

#ifndef _ZMQ_UTILITY_H_
#define _ZMQ_UTILITY_H_

#include <zmq.h>

#define NAME_LEN 256
#define MSG_LEN  1024

typedef struct
{
    char szSrc[NAME_LEN];
    char szDst[NAME_LEN];
    char szMsg[MSG_LEN];
}ZmqMsg;


typedef struct
{
    void* sock;
    int iType;
}ZmqSock;

int s_recv(ZmqSock* sock, ZmqMsg* msg);
int s_send(ZmqSock* sock, ZmqMsg* msg);

#endif 
