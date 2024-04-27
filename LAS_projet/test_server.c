#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void test_server_response(void) {
    // Créez un socket client et connectez-vous au serveur
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(33431);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Envoyez un message au serveur
    char message[256] = "Test message";
    write(sockfd, message, strlen(message));

    // Lisez la réponse du serveur
    char response[256];
    read(sockfd, response, 256);
    printf("Response: %s\n", response);

    // Vérifiez que la réponse du serveur est ce que vous attendez
    CU_ASSERT_STRING_EQUAL(response, "Test message");
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite1 = CU_add_suite("server_test", 0, 0);

    CU_add_test(suite1, "test_server_response", test_server_response);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}