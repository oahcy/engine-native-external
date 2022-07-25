
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

list(APPEND CC_EXTERNAL_PRIVATE_DEFINITIONS __TBB_LIB_NAME=tbb)

set(third_parts)
set(third_include)

find_package(WebP CONFIG REQUIRED)
list(APPEND third_parts WebP::webp WebP::webpdemux WebP::libwebpmux WebP::webpdecoder )

find_package(SDL2 CONFIG REQUIRED)
list(APPEND third_parts SDL2::SDL2 SDL2::SDL2main)

find_package(OpenSSL REQUIRED)
list(APPEND third_parts OpenSSL::SSL OpenSSL::Crypto)

find_package(freetype CONFIG REQUIRED)
list(APPEND third_parts freetype)

find_package(JPEG REQUIRED)
list(APPEND third_parts  ${JPEG_LIBRARIES})
list(APPEND third_include ${JPEG_INCLUDE_DIR})

find_package(CURL CONFIG REQUIRED)
list(APPEND third_parts CURL::libcurl)

find_package(mpg123 CONFIG REQUIRED)
list(APPEND third_parts MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)

find_package(Ogg CONFIG REQUIRED)
list(APPEND third_parts PRIVATE Ogg::ogg)

find_package(PNG REQUIRED)
list(APPEND third_parts PRIVATE PNG::PNG)

find_package(libuv CONFIG REQUIRED)
list(APPEND third_parts  $<IF:$<TARGET_EXISTS:uv_a>,uv_a,uv>)

# Vorbis reference encoder and decoder, low-level API
find_package(Vorbis CONFIG REQUIRED)
list(APPEND third_parts Vorbis::vorbis)

# Audio stream decoding and basic manipulation, high-level API
find_package(Vorbis CONFIG REQUIRED)
list(APPEND third_parts Vorbis::vorbisfile)

find_package(OpenAL CONFIG REQUIRED)
list(APPEND third_parts OpenAL::OpenAL)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
list(APPEND third_parts unofficial::sqlite3::sqlite3)

find_package(ZLIB REQUIRED)
list(APPEND third_parts ZLIB::ZLIB)

find_package(libwebsockets CONFIG REQUIRED)
list(APPEND third_parts websockets_shared)

find_package(glslang CONFIG REQUIRED)
list(APPEND third_parts HLSL SPIRV glslang OGLCompiler)

find_package(TBB CONFIG REQUIRED)
list(APPEND third_parts TBB::tbb)

list(APPEND CC_EXTERNAL_LIBS
    ${se_libs_name}
    ${third_parts}
)

list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${third_include}
)
