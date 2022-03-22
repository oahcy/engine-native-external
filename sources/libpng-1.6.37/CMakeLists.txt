set(LIBPNG_SOURCE 
    ${CMAKE_CURRENT_LIST_DIR}/pngrio.c
    ${CMAKE_CURRENT_LIST_DIR}/pngwio.c
    ${CMAKE_CURRENT_LIST_DIR}/pngmem.c
    ${CMAKE_CURRENT_LIST_DIR}/pngerror.c
    ${CMAKE_CURRENT_LIST_DIR}/pngwtran.c
    ${CMAKE_CURRENT_LIST_DIR}/pngtrans.c
    ${CMAKE_CURRENT_LIST_DIR}/pngread.c
    ${CMAKE_CURRENT_LIST_DIR}/pngget.c
    ${CMAKE_CURRENT_LIST_DIR}/pngpread.c
    ${CMAKE_CURRENT_LIST_DIR}/pngwrite.c
    ${CMAKE_CURRENT_LIST_DIR}/pngset.c
    ${CMAKE_CURRENT_LIST_DIR}/png.c
    ${CMAKE_CURRENT_LIST_DIR}/pngwutil.c
    ${CMAKE_CURRENT_LIST_DIR}/pngrtran.c
    ${CMAKE_CURRENT_LIST_DIR}/pngrutil.c
)

set(LIBPNG_DEFINES
    PNG_ARM_NEON=off
    PNG_ARM_NEON_OPT=0
)


    if(NOT USE_MODULES)
        list(APPEND CC_EXTERNAL_SOURCES ${LIBPNG_SOURCE})
        list(APPEND CC_EXTERNAL_INCLUDES ${CMAKE_CURRENT_LIST_DIR})
        list(APPEND CC_EXTERNAL_PRIVATE_DEFINITIONS ${LIBPNG_DEFINES})
    else()
        add_library(libpng16 ${LIBPNG_SOURCE})

        target_include_directories(libpng16 PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}
        )

        set_property(TARGET libpng16
            APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS ${LIBPNG_DEFINES}
        )

        set(se_libs_name libpng16)
    endif()