add_executable(CommandLineExample Main.cpp)
target_link_libraries(CommandLineExample PUBLIC RuntimeCommandEngine)
target_link_libraries(CommandLineExample PUBLIC SimpleMath)
target_link_libraries(CommandLineExample PUBLIC SimpleMathCmdTree)
set_target_properties(CommandLineExample PROPERTIES FOLDER "Examples")
target_include_directories(CommandLineExample PUBLIC 
	"${CMAKE_SOURCE_DIR}/Source/Libraries")
