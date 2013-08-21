#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/uio.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUF_SIZE 1024

int main(void) {
  // ソケットディスクリプタ
  //  サーバ側のソケット作成をOSに依頼
  int socketd = socket(AF_INET, SOCK_STREAM, 0);
  // クライアント側のソケットディスクリプタ
  int client_socketd;
  int len, read_len;

  // サーバ側のソケットアドレス
  struct sockaddr_in server_address;
  // クライアント側
  struct sockaddr_in client_address;

  char buf[BUF_SIZE];

  // ソケットの情報埋める
  server_address.sin_family       = AF_INET;
  server_address.sin_port         = htons(6666);
  server_address.sin_addr.s_addr  = htonl(INADDR_ANY);

  // 作成したソケットに名前付け
  bind(socketd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in));

  // ソケットが受付できる状態であることをOSに知らせる
  listen(socketd, 5);

  while (true) {
    printf("[Server] Waiting...\n");

    len = sizeof(client_address);
    client_socketd = accept(socketd, (struct sockaddr *)&client_address, &len);

    read_len = read(client_socketd, buf, BUF_SIZE - 1);
    buf[read_len] = 0;

    for (int i = 0; i < 10; i++) {
      printf("%d ", buf[i]);
    }

    if (strcmp("kill\n", buf) == 0) {
      break;
    }

    write(client_socketd, buf, strlen(buf));
    close(client_socketd);
  }

  close(socketd);

  return 0;
}
