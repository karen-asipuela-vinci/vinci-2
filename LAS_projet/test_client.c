#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void function_to_test(int argc, char* argv[]) {
    // Code that was previously in main
}

void test_main() {
    int argc = 1;
    char* argv[] = {"./client", NULL};
    function_to_test(argc, argv);
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Create a suite and add the test case
    CU_pSuite suite = CU_add_suite("Main Suite", NULL, NULL);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(suite, "test_main", test_main)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up the test registry
    CU_cleanup_registry();

    return CU_get_error();
}