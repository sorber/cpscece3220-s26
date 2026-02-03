#include <aio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#define BUFSIZE 2500

int main()
{

        int ret;
        struct aiocb aioinfo;
        int fd = open("pthreadex.c", O_RDONLY);
        if (fd < 0)
                perror("open");

        /**** In case you prefer fopen
        FILE *f = fopen("pthreadex.c","r");
        if (f == NULL) perror("fopen");
        int fd = fileno(f);
        */

        /* Zero out the aiocb structure (recommended) */
        memset((char *)&aioinfo, 0, sizeof(struct aiocb));

        /* Allocate a data buffer for the aiocb request */
        aioinfo.aio_buf = malloc(BUFSIZE + 1);
        if (!aioinfo.aio_buf)
                perror("malloc");

        /* Initialize the necessary fields in the aiocb */
        aioinfo.aio_fildes = fd;
        aioinfo.aio_nbytes = BUFSIZE;
        aioinfo.aio_offset = 0;

        ret = aio_read(&aioinfo);
        if (ret < 0)
                perror("aio_read");

        // you could do other stuff here. The read is in progress.

        uint64_t count = 0;
        while (aio_error(&aioinfo) == EINPROGRESS)
        {
                count++;
        }

        printf("Counted to %lu while waiting\n", count);
        if ((ret = aio_return(&aioinfo)) > 0)
        {
                printf("Got %d bytes:\n", ret);

                printf("Bytes: %s\n", (char *)aioinfo.aio_buf);
        }
        else
        {
                printf("READ FAILED!!!\n");
        }
        close(fd);
}
