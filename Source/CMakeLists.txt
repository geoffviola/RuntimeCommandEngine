option(BUILD_UNIT_TESTS "Build and run unit tests" OFF)

#Set MT for gtest
if(MSVC)
	set(flags_for_compilers
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_MINSIZEREL
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS_DEBUG
		CMAKE_C_FLAGS_MINSIZEREL
		CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_RELWITHDEBINFO
	)
	foreach(flags_for_compiler ${flags_for_compilers})
		if(${${flags_for_compiler}} MATCHES "/MD")
			STRING(REPLACE "/MD" "/MT" ${flags_for_compiler} 
				${${flags_for_compiler}})
		else()
			set(${flags_for_compiler} "${${flags_for_compiler}} /MT")
		endif()
	endforeach()
endif()

#Set warnings to highest
if(MSVC)
	set(flags_for_compilers
		CMAKE_C_FLAGS
		CMAKE_CXX_FLAGS
	)
	foreach(flags_for_compiler ${flags_for_compilers})
		if(${${flags_for_compiler}} MATCHES "/W[0-4]")
			STRING(REGEX REPLACE  "/W[0-4]" "/W4" ${flags_for_compiler} 
				${${flags_for_compiler}})
		else()
			set(${flags_for_compiler} "${${flags_for_compiler}} /W4")
		endif()
		string(CONCAT ${flags_for_compiler} " /wd4373") #For gmock
		string(CONCAT ${flags_for_compiler} " /EHsc") #For gmock
	endforeach()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	add_definitions("-Wall -Wno-long-long -pedantic")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions("-Weverything")
endif()

#Add flags for C++14 features
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	add_definitions("-std=gnu++14")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions("-std=c++14")
endif()

set(RUNTIMECOMMANDENGINE_3RDPARTY_DIR 
	"${CMAKE_CURRENT_LIST_DIR}/Libraries/3rdParty")
function(setup_unit_test test_name test_file)
	add_executable(${test_name} ${test_file})
	target_link_libraries(${test_name} RuntimeCommandEngine gmock_main)
	target_include_directories(${test_name} PUBLIC 
		"${RUNTIMECOMMANDENGINE_3RDPARTY_DIR}/gmock/include")
	target_include_directories(${test_name} PUBLIC 
		"${RUNTIMECOMMANDENGINE_3RDPARTY_DIR}/gtest/include")
	set_target_properties(${test_name} PROPERTIES FOLDER "UnitTests")
	add_test(NAME ${test_name} 
		COMMAND "$<TARGET_FILE_DIR:${test_name}>/${test_name}"
		--gtest_shuffle)
endfunction ()

add_subdirectory(Libraries)
add_subdirectory(Executables)
