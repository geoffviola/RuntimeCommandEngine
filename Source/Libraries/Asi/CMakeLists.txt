add_subdirectory(RuntimeCommandEngine)

if (ASI_RUNTIMECOMMAND_ENGINE_EXTRAS)
	add_subdirectory(SimpleMath)
	add_subdirectory(SimpleMathCmdTree)
endif ()
