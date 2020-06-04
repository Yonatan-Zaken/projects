/*********************
    Master
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

#include <boost/bind.hpp>

#include "master.hpp"

namespace ilrd
{

Master::Master(const char *dev, std::size_t size):
    m_communicator(dev, size, reactor, boost::bind(&Master::Callback, this)),
    m_reactor()
{

}

/******************************************************************************/

Master::~Master()
{

}

/******************************************************************************/

void Master::Callback()
{
    close(m_communicator.GetNBDFD());

    u_int64_t from;
    u_int32_t len;
    ssize_t bytes_read;
    struct nbd_request request;
    struct nbd_reply reply;
    void *chunk;

    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(0);

    while ((bytes_read = read(sk, &request, sizeof(request))) > 0) 
    {
        int i = 0;
        i++;
        printf("out of block on request %d!\n", i);
        assert(bytes_read == sizeof(request));
        memcpy(reply.handle, request.handle, sizeof(reply.handle));
        reply.error = htonl(0);

        len = ntohl(request.len);
        from = ntohll(request.from);
        assert(request.magic == htonl(NBD_REQUEST_MAGIC));

        switch(ntohl(request.type)) {
      /* I may at some point need to deal with the the fact that the
       * official nbd server has a maximum buffer size, and divides up
       * oversized requests into multiple pieces. This applies to reads
       * and writes.
       */
        case NBD_CMD_READ:
            if (BUSE_DEBUG) fprintf(stderr, "Request for read of size %d\n", len);
      /* Fill with zero in case actual read is not implemented */
        chunk = malloc(len);
        if (aop->read) 
        {
            reply.error = aop->read(chunk, len, from, userdata);
        } 
        else 
        {
            /* If user not specified read operation, return EPERM error */
            reply.error = htonl(EPERM);
        }
        
        write_all(sk, (char*)&reply, sizeof(struct nbd_reply));
        write_all(sk, (char*)chunk, len);
        free(chunk);
        break;

        case NBD_CMD_WRITE:
            if (BUSE_DEBUG) fprintf(stderr, "Request for write of size %d\n", len);
        chunk = malloc(len);
        read_all(sk, chunk, len);
        if (aop->write) 
        {
            reply.error = aop->write(chunk, len, from, userdata);
        } 
        else 
        {
            /* If user not specified write operation, return EPERM error */
            reply.error = htonl(EPERM);
        }
        
        free(chunk);
        write_all(sk, (char*)&reply, sizeof(struct nbd_reply));
        break;
}

} // namespace ilrd


