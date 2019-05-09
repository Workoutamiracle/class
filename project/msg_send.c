#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH "/etc/passwd"
#define PROJID 1234
#define MSG "hello world!"

struct Buf {
    long mtype;
    char mtext[BUFSIZ];
};


int main()
{
    int msgid;
    key_t key;
    struct msgbuf buf;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }

    msgid = msgget(key, 0);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }

    buf.mtype = 1;
    strncpy(buf.mtext, MSG, strlen(MSG));
    if (msgsnd(msgid, &buf, strlen(buf.mtext), 0) == -1) {
        perror("msgsnd()");
        exit(1);
    }

}
