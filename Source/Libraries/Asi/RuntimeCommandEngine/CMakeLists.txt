set(ROOT_SOURCES
	CommandWithoutParams.cpp
	CommandWithGenericParams.cpp
	StringUtils.cpp
	Tree.cpp
)
set(ROOT_HEADERS
	CommandInterface.hpp
	CommandWithoutParams.hpp
	CommandWithGenericParams.hpp
	CommandWithParams.hpp
	MakeCommand.hpp
	StringUtils.hpp
	Tree.hpp
)
set(PARAMETER_SOURCES
	Parameter/Percentage.cpp
	Parameter/String.cpp
	Parameter/StringSet.cpp
	Parameter/Union.cpp
)
set(PARAMETER_HEADERS
	Parameter/ParameterAbstract.hpp
	Parameter/Percentage.hpp
	Parameter/Range.hpp
	Parameter/String.hpp
	Parameter/StringSet.hpp
	Parameter/Union.hpp
)

set(SOURCES
	${ROOT_SOURCES}
	${PARAMETER_SOURCES}
)
set(HEADERS
	${ROOT_HEADERS}
	${PARAMETER_HEADERS}
)

add_library(RuntimeCommandEngine ${HEADERS} ${SOURCES})

install(FILES ${ROOT_HEADERS} DESTINATION include/Asi/RuntimCommandEngine)
install(FILES ${PARAMETER_HEADERS}
	DESTINATION include/Asi/RuntimCommandEngine/Parameter)
install(TARGETS RuntimeCommandEngine
	ARCHIVE DESTINATION lib)

source_group("" FILES ${ROOT_HEADERS} ${ROOT_SOURCES})
source_group(Parameter FILES ${PARAMETER_HEADERS} ${PARAMETER_SOURCES})

if (ASI_RUNTIMECOMMAND_ENGINE_EXTRAS)
	add_subdirectory(Parameter)
	add_subdirectory(UnitTests)
endif ()
