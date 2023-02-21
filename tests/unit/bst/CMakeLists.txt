add_executable(bst bst.c)
target_link_libraries(bst Tree Types Util BST)

add_test(NAME insert COMMAND bst 1 int 50 3)
set_tests_properties(insert PROPERTIES PASS_REGULAR_EXPRESSION "50")

add_test(NAME multiple-insert COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 3)
set_tests_properties(multiple-insert PROPERTIES PASS_REGULAR_EXPRESSION "50 25 0 75 100")

add_test(NAME remove-no-children COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 2 int 0 3)
set_tests_properties(remove-no-children PROPERTIES PASS_REGULAR_EXPRESSION "50 25 75 100")

add_test(NAME remove-left-children COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 2 int 25 3)
set_tests_properties(remove-left-children PROPERTIES PASS_REGULAR_EXPRESSION "50 0 75 100" FAIL_REGULAR_EXPRESSION "25")

add_test(NAME remove-right-children COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 2 int 75 3)
set_tests_properties(remove-right-children PROPERTIES PASS_REGULAR_EXPRESSION "50 25 0 100" FAIL_REGULAR_EXPRESSION "75")

add_test(NAME remove-both-children COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 2 int 50 3)
set_tests_properties(remove-both-children PROPERTIES PASS_REGULAR_EXPRESSION "25 0 75 100" FAIL_REGULAR_EXPRESSION "50")

add_test(NAME remove-all-nodes COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 100 1 int 0 2 int 50 2 int 25 2 int 0 2 int 75 2 int 100 3)
set_tests_properties(remove-all-nodes PROPERTIES FAIL_REGULAR_EXPRESSION "0;25;50;75;100")

add_test(NAME remove-from-empty COMMAND bst 1 int 1000 2 int 1000 2 int 0 3)
set_tests_properties(remove-from-empty PROPERTIES PASS_REGULAR_EXPRESSION "\n" FAIL_REGULAR_EXPRESSION "1000;0")

add_test(NAME remove-then-insert COMMAND bst 1 int 50 1 int 25 1 int 75 1 int 37 1 int 62 1 int 100 1 int 0 2 int 50 2 int 62 2 int 100 2 int 0 1 int 35 1 int 47 1 int 96 3)
set_tests_properties(remove-then-insert PROPERTIES PASS_REGULAR_EXPRESSION "37 25 35 75 47 96")