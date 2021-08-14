add_test( HelloTest.BasicAssertions C:/Users/marce/source/repos/close-to-gl/out/build/Unittest1.exe [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY C:/Users/marce/source/repos/close-to-gl/out/build/x64-Debug/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( Unittest1_TESTS HelloTest.BasicAssertions)
