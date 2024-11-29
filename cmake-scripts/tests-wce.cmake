add_test(
        NAME "wce"
        COMMAND ${CMAKE_COMMAND}
            -DASY_EXEC=$<TARGET_FILE:asy>
            -DASY_BASE_DIR=${ASY_BUILD_BASE_DIR}
            -DSOURCE_ROOT=${CMAKE_CURRENT_SOURCE_DIR}
            -P ${ASY_MISC_CMAKE_SCRIPTS_DIR}/wce.script.cmake
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
