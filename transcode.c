#include "trans_encapsulation.h"
#include <pthread.h>
#include <stdlib.h>

int transcode(void *message)
{
    const char *cmd = (const char *)message;
    return system(cmd);
}

int main()
{
    char *filename[3] = {"video2.flv", "video2.mp4", "xvideo2.mp4"};
    const char *cmd;
    sscanf(cmd, "ffmpeg -i %s %s", filename[0], filename[2]);
    int ret_thread;
    pthread_t trans_thread;
    void *retval;

    ret_thread = pthread_create(&trans_thread, NULL, (void *)&transcode, (void *)cmd);
    if(ret_thread != 0){
        printf("fail to create trans_thread \n");
    }

    int ret_encap = trans_encapsulation(filename);
    if(ret_encap != 0){
        printf("need to transcode \n");
        ret_thread = pthread_join(trans_thread, &retval);
        remove(filename[1]);
        rename(filename[2], filename[1]);
    }
    else{
        printf("trans encapsulation successfully \n");
        pthread_cancel(trans_thread);
        ret_thread = pthread_join(trans_thread, NULL);
        remove(filename[2]);
    }

    printf("hello world! \n");
    return 0;
}