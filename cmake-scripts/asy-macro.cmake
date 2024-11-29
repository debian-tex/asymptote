if (NOT ASY_VERSION_OVERRIDE)
if (ASY_ADDR_VERSION_SUFFIX_FILE STREQUAL "NOTFOUND")
    if (CMAKE_BUILD_TYPE IN_LIST cmake_debug_build_types)
        set(ASY_VERSION_SUFFIX "+debug")
    endif()
endif()

set(ASY_VERSION "${ASY_VERSION_BASE}${ASY_VERSION_SUFFIX}")
else()
    message(STATUS "Override version specified")
    set(ASY_VERSION ${ASY_VERSION_OVERRIDE})
endif()

message(STATUS "Asymptote version: ${ASY_VERSION}")


list(APPEND ASY_MACROS
        PACKAGE_NAME="${ASY_PACKAGE_NAME}"
        PACKAGE_VERSION="${ASY_VERSION}"
        PACKAGE_BUGREPORT="${ASY_BUGREPORT}"
        PACKAGE_STRING="${ASY_PACKAGE_NAME} ${ASY_VERSION}"
)

# Since we require C++11 and up, some macros are automatically included
list(APPEND ASY_MACROS
        HAVE_UNORDERED_MAP
        HAVE_STRFTIME
        _USE_MATH_DEFINES
)

if (DEBUG_GC_ENABLE)
    list(APPEND ASY_MACROS GC_DEBUG)
endif()

if (DEBUG_GC_BACKTRACE_ENABLE)
    list(APPEND ASY_MACROS GC_BACKTRACE)
endif()

if (CMAKE_BUILD_TYPE IN_LIST cmake_debug_build_types)
    list(APPEND ASY_MACROS DEBUG)
endif()

if (CTAN_BUILD)
    list(APPEND ASY_MACROS CTAN_BUILD)
endif()
