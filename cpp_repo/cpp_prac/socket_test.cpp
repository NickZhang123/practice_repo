#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
#include<vector>
#include<thread>
#include<chrono>

using namespace std;

int connect_tgt(string tgtIp, int port)
{
    // 1. socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout << "socket error" << endl;
        return -1;
    }

    // 2. connect
    struct sockaddr_in server_ad;
    server_ad.sin_family = AF_INET;
    server_ad.sin_port = htons(port);
    //server_ad.sin_addr.s_addr = inet_addr(tgtIp.c_str());
    if (inet_pton(AF_INET, tgtIp.c_str(), &server_ad.sin_addr) <= 0) {
        cout << "trans ip failed" << endl;
        close(sockfd);  // 关闭连接
        return -1;
    }
    if (connect(sockfd, (struct sockaddr *)(&server_ad), sizeof(struct sockaddr_in)) < 0) {
        cout << "connect failed" << ", errno = " << errno << endl;
        close(sockfd);
        return -1;
    }
    cout << "connect success, ip = " << tgtIp << ", port = " << port << endl;
    
    // 3. write
    string str = "hello world";
    int r = write(sockfd, str.c_str(), str.length());
    if (r != str.length()) {
        cout << "write failed" << endl;
        close(sockfd);
        return -1;
    }

    // 4. read
    char buf[1024] = {0};
    r = read(sockfd, buf, 1024);
    if (r < 0) {
        cout << "read failed" << endl;
        close(sockfd);
        return -1;
    }
    cout << buf << endl;

    // 5. close
    close(sockfd);

    return 0;
}


int tcp_server(int port)
{
    // 1. socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout << "socket error" << endl;
        return -1;
    }

    // 2. bind
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(struct sockaddr_in)) < 0) {
        cout << "socket bind failed" << endl;
        close(sockfd);
        return -1;
    }

    // 3. listen
    if (listen(sockfd, 20) < 0) {
        cout << "listen socket failed" << endl;
        close(sockfd);
        return -1;
    }

    cout << "listening on port " << port << endl;

    // 4. accept
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int sock_cliet = accept(sockfd, (struct sockaddr*)(&client_addr), &client_len);
    if (sock_cliet < 0) {
        cout << "accept socket failed" << endl;
        close(sockfd);
        return -1;
    }
    char client_ip[INET_ADDRSTRLEN] = {0};
    if (inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN) < 0) {
        cout << "tran ip to host failed" << endl;
        close(sock_cliet);
        close(sockfd);
        return -1;
    }
    cout << "new-client: ip = " << client_ip << ", port = " << ntohs(client_addr.sin_port) << endl;

    // 5. read
    char buf[1024] = {0};
    int r = read(sock_cliet, buf, 1024);
    if (r < 0) {
        cout << "read failed" << endl;
        close(sock_cliet);
        close(sockfd);
        return -1;
    }
    cout << "recv from cliet: " << buf << endl;
 
    // 6. write
    int rw = write(sock_cliet, buf, r);
    if (rw != r) {
        cout << "write failed" << endl;
        close(sock_cliet);
        close(sockfd);
        return -1;
    }
    

    // 7. close
    close(sock_cliet);
    close(sockfd);

    return 0;
}


int test_server()
{
    vector<shared_ptr<thread>> vec;
    vec.emplace_back(make_shared<thread>(tcp_server, 5555));
    this_thread::sleep_for(chrono::milliseconds(100));
    vec.emplace_back(make_shared<thread>(connect_tgt, "127.0.0.1", 5555));
    for (auto &t: vec) {
        t->join();
    }
    return 0;
}