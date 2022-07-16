add_library(dbgcore SHARED IMPORTED GLOBAL)

set_target_properties(dbgcore PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/dbgcore.dll
)

add_library(dbghelp SHARED IMPORTED GLOBAL)

set_target_properties(dbghelp PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/dbghelp.dll
)

add_library(dbgeng SHARED IMPORTED GLOBAL)

set_target_properties(dbgeng PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/dbgeng.dll
)


add_library(tcmalloc SHARED IMPORTED GLOBAL)
set_target_properties(tcmalloc PROPERTIES
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libtcmalloc_minimal.lib
)

set(se_libs_name)

if(CC_EDITOR)
    message(VERBOSE "CC_EDITOR USE V8 FROM NODEJS")
elseif(USE_SE_V8)
    add_library(v8 SHARED IMPORTED GLOBAL)
    set_target_properties(v8 PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8.dll.lib
      INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS
    )

    add_library(v8_libbase SHARED IMPORTED GLOBAL)
    set_target_properties(v8_libbase PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libbase.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libbase.dll.lib
    )

    add_library(v8_libplatform SHARED IMPORTED GLOBAL)
    set_target_properties(v8_libplatform PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libplatform.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libplatform.dll.lib
    )

    target_link_libraries(v8 INTERFACE v8_libbase v8_libplatform)

    set_target_properties(v8 PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/v8
    )

    set(se_libs_name v8)
else()
    message(FATAL_ERROR "Only V8 is supported!")
endif()

include("${COCOS_X_PATH}/conan/win64/conanbuildinfo.cmake")
conan_basic_setup()

list(APPEND CC_EXTERNAL_LIBS
    ${CONAN_LIBS}
)

set(ZLIB zlib)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB}
    ${se_libs_name}
  )
endif()

list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)
