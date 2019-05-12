#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>

#define FILEPATH "/etc/passwd"
#define PROJID 1234
#define MSG "hello world!"

struct data{
    long  type;
    char mtext[BUFSIZ-8];
};

struct Buf {
    long mtype;
    struct data mdata;
};
void hand(int msgid)
{
    struct Buf buf;
    buf.mtype = 1;
    std::cout << sizeof(struct data) << std::endl;
    std::cin >> buf.mdata.mtext;

    if (msgsnd(msgid, &buf, sizeof(struct data), 0) == -1) {
        perror("msgsnd()");
        exit(1);
    }
}

int main()
{
    int msgid;
    key_t key;

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

    std::cout << msgid  << std::endl;

    std::thread t(hand,msgid);
    t.join();
    return 0;
}
