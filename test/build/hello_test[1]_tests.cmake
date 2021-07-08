add_test( HelloTest.BasicAssertions /Users/niney/Desktop/code/ninechippers/test/build/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /Users/niney/Desktop/code/ninechippers/test/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( hello_test_TESTS HelloTest.BasicAssertions)
