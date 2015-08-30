cmake_minimum_required(VERSION 2.8.12)
project(RuntimeCommandEngine)

enable_testing()

#Allow folders in MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Source)
