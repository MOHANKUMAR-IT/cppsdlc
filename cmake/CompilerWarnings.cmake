# Compiler warnings configuration

function(set_project_warnings)
    if(MSVC)
        set(MSVC_WARNINGS
            /W4     # High warning level
            /w14242 # Conversion warning
            /w14254 # Different member qualifier
            /w14263 # Member function does not override
            /w14265 # Class has virtual functions but destructor is not virtual
            /w14287 # Unsigned/negative constant mismatch
            /we4289 # Loop control variable declared in the for-loop
            /w14296 # Expression is always false
            /w14311 # Pointer truncation
            /w14545 # Expression before comma has no effect
            /w14546 # Function call before comma missing argument list
            /w14547 # Operator before comma has no effect
            /w14549 # Operator before comma has no effect
            /w14555 # Expression has no effect
            /w14619 # Pragma warning number not available
            /w14640 # Thread-unsafe static member initialization
            /w14826 # Conversion is sign-extended
            /w14905 # Wide string literal cast
            /w14906 # String literal cast
            /w14928 # Illegal copy-initialization
            /permissive- # Standards conformance mode
        )
        add_compile_options(${MSVC_WARNINGS})
    else()
        set(GCC_CLANG_WARNINGS
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
        )
        
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            list(APPEND GCC_CLANG_WARNINGS
                -Wmisleading-indentation
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wuseless-cast
            )
        endif()
        
        add_compile_options(${GCC_CLANG_WARNINGS})
    endif()
endfunction()
