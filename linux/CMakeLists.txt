set(linux_lib_dir ${platform_spec_path}/lib)
MESSAGE(STATUS "${platform_spec_path}")

add_library(v8 STATIC IMPORTED GLOBAL)
set_target_properties(v8 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/v8/libv8_monolith.a
)

### vcpkg
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

if(NOT USE_SERVER_MODE)
  find_package(SDL2 CONFIG REQUIRED)
  list(APPEND third_parts SDL2::SDL2 SDL2::SDL2main)
endif()

###vcpkg end
list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/v8
  ${platform_spec_path}/include/uv
  ${third_include}
)



list(APPEND CC_EXTERNAL_LIBS
  v8
  ${third_parts}
)