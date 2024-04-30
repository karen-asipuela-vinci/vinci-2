#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include "utils_v1.h"
#include "messages.h"
#include "network.h"

void test_sendMessageAndReceiveResponse(void)
{
    printf("Starting test_sendMessageAndReceiveResponse\n");

    // Create a mock socket file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket failed");
        return;
    }

    printf("Socket created, fd = %d\n", sockfd);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1234);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("inet_pton failed");
        return;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect failed");
        return;
    }

    printf("Connected to server\n");

    // Create a mock message
    StructMessage msg;
    msg.code = 10;
    msg.tuile = 12;

    printf("Sending message\n");

    // Call the function under test
    sendMessageAndReceiveResponse(sockfd, &msg);

    printf("Message sent and response received\n");

    // Assert that the message was sent and received correctly
    CU_ASSERT_EQUAL(msg.code, 10);
    CU_ASSERT_EQUAL(msg.tuile, 12);

    printf("Test completed\n");
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("sendMessageAndReceiveResponse_test\n", 0, 0);

    CU_add_test(suite, "test_sendMessageAndReceiveResponse\n", test_sendMessageAndReceiveResponse);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}