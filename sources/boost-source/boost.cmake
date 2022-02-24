
list(APPEND CC_EXTERNAL_PRIVATE_DEFINITIONS BOOST_ALL_NO_LIB)

set(BOOST_LIB_NAMES
    container
)

foreach(lib ${BOOST_LIB_NAMES})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${lib} boost/${lib})
    set_target_properties(boost_${lib} PROPERTIES FOLDER Utils)
    target_compile_definitions(boost_${lib} PUBLIC
        BOOST_UUID_FORCE_AUTO_LINK
    )
    list(APPEND CC_EXTERNAL_LIBS boost_${lib})
endforeach()
