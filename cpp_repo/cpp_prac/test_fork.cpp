#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

using namespace std;


void fork1() 
{
    cout << "fork1" << endl;
    pid_t pid = fork();
    if (pid < 0) {
        cout << "fork failed" << endl;
        return;
    }
    if (pid > 0) {
        cout << "father running, father pid: " << getpid() << ", son pid : " << pid << endl;
        wait(NULL);
        cout << "father end" << endl;
    } else {
        cout << "son running, son pid: " << getpid() << ", father pid(): " << getppid() << endl;
        cout << "son do something" << endl;
        cout << "son end" << endl;
    }
    return;
}

void fork2()
{
    cout << "fork2" << endl;
    pid_t pid = fork();
    if (pid < 0) {
        cout << "fork failed" << endl;
        return;
    }
    if (pid > 0) {
        cout << "father running, father pid: " << getpid() << ", son pid : " << pid << endl;
        wait(NULL);
        cout << "father end" << endl;
    } else {
        cout << "son running, son pid: " << getpid() << ", father pid(): " << getppid() << endl;
        //execlp("ls", "ls", "-l", NULL); 
        execl("/usr/bin/ls", "ls", "-l", "/", NULL);
        cout << "son end" << endl;
    }
    return;
}

void fork_ipc()
{
    // 管道
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        cout << "Pipe creation failed!" << endl;
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // 子进程：写数据到管道
        string str = "Hello from child";
        cout << str.length() << endl;
        close(pipefd[0]);  // 关闭读取
        write(pipefd[1], str.c_str(), str.length() + 1);
        close(pipefd[1]);
        _exit(0);
    } else {
        // 父进程：从管道读取数据
        close(pipefd[1]);  // 关闭写入
        char buf[100] = {0};
        read(pipefd[0], buf, sizeof(buf));
        cout << "Parent received: " << buf << endl;
        close(pipefd[0]);
        wait(NULL);  // 等待子进程退出
    }
}

#define PIPE_NAME "/tmp/myfifo" 

void fork_ipc_fifo()
{
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        cout << "mkfifo failed" << endl;
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        cout << "fork failed" << endl;
        unlink(PIPE_NAME);
        return;
    }

    if (pid > 0) {
        // 父进程从管道读
        cout << "father beign" << endl;
        int fd = open(PIPE_NAME, O_RDONLY);
        if (fd == -1) {
            cout << "open PIPE failed" << endl;
            return;
        }
        char buff[100] = {0};
        read(fd, buff, 100);
        cout << "buff : " << buff << endl;
        close(fd);
        wait(NULL);
        cout << "father end" << endl;
    } else {
        // 子进程向管道写
        cout << "son begin" << endl;
        int fd = open(PIPE_NAME, O_WRONLY);
        if (fd == -1) {
            cout << "SON open PIPE failed" << endl;
            return;
        }
        string str = "test fifo";
        write(fd, str.c_str(), str.length() + 1);
        cout << "SON endl" << endl;
        close(fd);
    }
    unlink(PIPE_NAME);
}


#define MSG_KEY 1234  // 消息队列的 key
struct msgbuf1 {
    long mtype;      // 消息类型
    char mtext[100]; // 消息内容
};

void test_ipc_msg_queue()
{
    pid_t pid = fork();
    if (pid < 0) {
        cout << "fork failed" << endl;
        return;
    }

    if (pid > 0) {
        // 父进程从管道读
        cout << "father beign" << endl;
        wait(NULL);
        struct msgbuf1 message;

        int msqid = msgget(MSG_KEY, 0666);
        if (msqid == -1) {
            cout << "create msg queue failed" << endl;
            return;
        }

        if (msgrcv(msqid, &message, sizeof(message.mtext), 1, 0) == -1) {
            cout << "recv msg queue failed" << endl;
            return;
        }

        printf("Message received: %s\n", message.mtext);

        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            cout << "delete msg queue failed" << endl;
            return;
        }

        cout << "father end" << endl;
    } else {
        // 子进程向管道写  
        cout << "son begin" << endl;
        int msqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
        if (msqid == -1) {
            cout << "create msg queue failed" << endl;
            return;
        }
        struct msgbuf1 message;
        message.mtype = 1;  // 消息类型为 1
        strcpy(message.mtext, "Hello, world!");

        if (msgsnd(msqid, &message, strlen(message.mtext) + 1, 0) == -1) {
            cout << "send msg queue failed" << endl;
            return;
        }

        cout << "son end" << endl;
    }

}



void test_fork_1() {
    //fork1();
    //fork2();
    //fork_ipc();
    //fork_ipc_fifo();
    test_ipc_msg_queue();
}