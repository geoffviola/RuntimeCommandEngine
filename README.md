# RuntimeCommandEngine
<h2> Overview </h2>
Library meant to convert sentences into function calls at runtime with support for English error descriptions

[![Build Status](https://travis-ci.org/geoffviola/RuntimeCommandEngine.svg?branch=master)](https://travis-ci.org/geoffviola/RuntimeCommandEngine)

<h2> Use Cases </h2>
<h3> Correct Use Case </h3>
Convert
```
"add 1 2"
```
into
```
add(1, 2);
```


<h3> Error Use Case </h3>
There are some human friendly error messages
```
"add 1 f"
```
could return
```
"Bad token "f". Expected [-100.0, 100.0]"
```
See examples for details

<h2> Implementation Details </h2>
The code is written to follow the C++14 standard. It compiles in MSVC14 2015, clang 3.6, and GCC 5 without warnings. 

<h2> Integration </h2>
It is currently meant to be incorporated into a project from source. After cloning the repository, a CMake script should call "add_subdirectory" in the "Source" folder. Then, the dependent target must link it and have "Source/Libraries" in the include path.
