add_executable(ProgramOptionsExample Main.cpp)
target_link_libraries(ProgramOptionsExample PUBLIC RuntimeCommandEngine)
set_target_properties(ProgramOptionsExample PROPERTIES FOLDER "Examples")
target_include_directories(ProgramOptionsExample PUBLIC 
	"${CMAKE_SOURCE_DIR}/Source/Libraries")
