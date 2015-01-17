编译
gcc -o client ipc-socket-client.c
gcc -o server ipc-socket-server.c
运行

启动server
./server 127.0.0.1 4567 (ip是必须的，端口可以不写默认4567)

效果
socket create success!
bind success!
the server is listening!
*****************Start Server***************


启动client
./client 127.0.0.1 4567 (ip与server相同，端口与server相同，如果server端口为4567，则可以不写)

client效果
socket create success!
conncet success!
Send message to server：
select option：
1: ADD
2: SUB
3: MUL
4: DIV
5: QUIT CLIENT

此时server增加效果
The connecting client is 127.0.0.1: 43812
然后就可以进行相应计算。两个数字进行加减乘除

注：1、输入使用scanf，因函数的特性所以对应%d需要输入对应整数，输入字母或其他会出错
    2、服务器没有提供直接的退出，客户端退出后服务器会提示是否退出，所以最好先退客户端，如果愿意可以ctl+c（不推荐）

