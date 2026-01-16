# Static analysis tools configuration

# clang-tidy
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY}
            -checks=-*,readability-*,modernize-*,performance-*,bugprone-*
            -warnings-as-errors=*
        )
        message(STATUS "clang-tidy enabled")
    else()
        message(STATUS "clang-tidy not found")
    endif()
endif()

# cppcheck
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK}
        --enable=warning,performance,portability
        --suppress=missingInclude
        --inline-suppr
        --quiet
    )
    message(STATUS "cppcheck enabled")
else()
    message(STATUS "cppcheck not found")
endif()
