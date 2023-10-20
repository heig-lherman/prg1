SET(CMAKE_CXX_FLAGS)
add_executable(L3-TestLongMath
        longmathTest.cpp
        catch_main.cpp
        ../lm_tostring.cpp
        ../lm_fromstring.cpp
        ../lm_add.cpp
        ../lm_multiply.cpp
        ../helper.cpp
)

if (MINGW)
    # CI is failing without the following flags
    target_compile_options(L3-TestLongMath PRIVATE "-Wa,-mbig-obj")
endif()
