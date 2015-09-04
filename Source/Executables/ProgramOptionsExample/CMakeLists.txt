add_executable(ProgramOptionsExample Main.cpp)
target_link_libraries(ProgramOptionsExample PUBLIC RuntimeCommandEngine)
set_target_properties(ProgramOptionsExample PROPERTIES FOLDER "Examples")
target_include_directories(ProgramOptionsExample PUBLIC 
	"${CMAKE_SOURCE_DIR}/Source/Libraries")

add_test(ProgramOptionsExampleIntegrationTest.NoTokens ProgramOptionsExample)
set_tests_properties(ProgramOptionsExampleIntegrationTest.NoTokens
	PROPERTIES PASS_REGULAR_EXPRESSION 
	"No tokens received. Expected: add, increment, help")
set_tests_properties(ProgramOptionsExampleIntegrationTest.NoTokens PROPERTIES 
	TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.BadCommand ProgramOptionsExample
	"junk")
set_tests_properties(ProgramOptionsExampleIntegrationTest.BadCommand
	PROPERTIES PASS_REGULAR_EXPRESSION 
	"Bad token \"junk\". Expected: add, increment, help")
set_tests_properties(ProgramOptionsExampleIntegrationTest.BadCommand PROPERTIES 
	TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.Help ProgramOptionsExample "help")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Help
	PROPERTIES PASS_REGULAR_EXPRESSION 
"\
\tadd:\n\
\t\tDescription: add two numbers\n\
\t\tParameters:\n\
\t\t\tleft value:\n\
\t\t\t\tDomain: \\[-100\\.0, 100\\.0\\]\n\
\t\t\t\tType: Range<int>\n\
\t\t\tright value:\n\
\t\t\t\tDomain: \\[-100\\.0, 100\\.0\\]\n\
\t\t\t\tType: Range<int>\n\
\tincrement:\n\
\t\tDescription: increment a number by one\n\
\t\tParameters:\n\
\t\t\tvalue:\n\
\t\t\t\tDomain: \\[-100\\.0, 100\\.0\\]\n\
\t\t\t\tType: Range<int>\n\
\thelp:\n\
\t\tDescription: print help information\n\
Format: signature_0 signature_1\\.\\.\\. signature_n \
\\[parameter_0 parameter_1\\.\\.\\. parameter_n\\]\n\
")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Help 
	PROPERTIES TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.IncrementBadArg 
	ProgramOptionsExample "increment" "1000")
set_tests_properties(ProgramOptionsExampleIntegrationTest.IncrementBadArg
	PROPERTIES PASS_REGULAR_EXPRESSION 
	"Bad token \"1000\". Expected: \\[-100\\.0, 100\\.0\\]")
set_tests_properties(ProgramOptionsExampleIntegrationTest.IncrementBadArg 
	PROPERTIES TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.Increment
	ProgramOptionsExample "increment" "2")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Increment
	PROPERTIES PASS_REGULAR_EXPRESSION "2 \\+ 1 = 3")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Increment 
	PROPERTIES TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.IncrementExtraToken
	ProgramOptionsExample "increment" "2" "1")
set_tests_properties(ProgramOptionsExampleIntegrationTest.IncrementExtraToken
	PROPERTIES PASS_REGULAR_EXPRESSION "Unknown extra token \"1\"")
set_tests_properties(ProgramOptionsExampleIntegrationTest.IncrementExtraToken 
	PROPERTIES TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.AddNoArgs ProgramOptionsExample 
	"add")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddNoArgs
	PROPERTIES PASS_REGULAR_EXPRESSION 
	"Expected next token: \\[-100\\.0, 100\\.0\\]")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddNoArgs PROPERTIES 
	TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.AddOnlyOneArg 
	ProgramOptionsExample "add")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddOnlyOneArg
	PROPERTIES PASS_REGULAR_EXPRESSION 
	"Expected next token: \\[-100\\.0, 100\\.0\\]")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddOnlyOneArg 
	PROPERTIES TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.Add ProgramOptionsExample 
	"add" "1" "1")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Add
	PROPERTIES PASS_REGULAR_EXPRESSION "1 \\+ 1 = 2")
set_tests_properties(ProgramOptionsExampleIntegrationTest.Add PROPERTIES 
	TIMEOUT 1)

add_test(ProgramOptionsExampleIntegrationTest.AddExtraToken 
	ProgramOptionsExample "add" "1" "1" "1")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddExtraToken
	PROPERTIES PASS_REGULAR_EXPRESSION "Unknown extra token \"1\"")
set_tests_properties(ProgramOptionsExampleIntegrationTest.AddExtraToken 
	PROPERTIES TIMEOUT 1)
