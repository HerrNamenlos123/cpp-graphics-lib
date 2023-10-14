find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
)

if (WIN32)
    add_custom_command(TARGET docs POST_BUILD
            COMMAND ${CMAKE_CURRENT_LIST_DIR}/make.bat html
            COMMENT "Generating sphinx documentation"
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            VERBATIM
    )
else()
    add_custom_command(TARGET docs POST_BUILD
            COMMAND make html
            COMMENT "Generating sphinx documentation"
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            VERBATIM
    )
endif ()