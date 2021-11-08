
add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libuv/libuv_a.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/libuv
)

add_library(mpg123 SHARED IMPORTED GLOBAL)
set_target_properties(mpg123 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/mpg123/libmpg123.so
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/mpg123
)

add_library(ogg STATIC IMPORTED GLOBAL)
set_target_properties(ogg PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/ogg/libogg.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/ogg
)

add_library(vorbisfile STATIC IMPORTED GLOBAL)
set_target_properties(vorbisfile PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/vorbis/libvorbisfile.a
)

add_library(vorbis STATIC IMPORTED GLOBAL)
set_target_properties(vorbis PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/vorbis/libvorbis.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/vorbis
)

add_library(libz SHARED IMPORTED GLOBAL)
set_target_properties(libz PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libz/libz.so.1.2.11
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/libz
)

add_library(sqlite3 SHARED IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/sqlite/libsqlite3.so.0.8.6
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/sqlite
)

add_library(v8 STATIC IMPORTED GLOBAL)
set_target_properties(v8 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/v8/libv8_monolith.a
)

add_library(openal SHARED IMPORTED GLOBAL)
set_target_properties(openal PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/openal-soft/libopenal.so.1.21.1
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/openal-soft
)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/jpeg/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libpng/libpng16.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/libpng
)

add_library(cairo SHARED IMPORTED GLOBAL)
set_target_properties(cairo PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/cairo/libcairo.so
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/cairo
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libwebsockets/libwebsockets.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/libwebsockets
)

add_library(curl SHARED IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/curl/libcurl.so
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/curl
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libwebp/libwebp.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/libwebp
)

add_library(sdl2 SHARED IMPORTED GLOBAL)
set_target_properties(sdl2 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/sdl2/libSDL2.so
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/sdl2
)

#glslang
add_library(libGenericCodeGen STATIC IMPORTED GLOBAL)
set_target_properties(libGenericCodeGen PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libGenericCodeGen.a
)
add_library(libglslang STATIC IMPORTED GLOBAL)
set_target_properties(libglslang PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libglslang.a
)
add_library(libglslang-default-resource-limits STATIC IMPORTED GLOBAL)
set_target_properties(libglslang-default-resource-limits PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libglslang-default-resource-limits.a
)
add_library(libSPIRV STATIC IMPORTED GLOBAL)
set_target_properties(libSPIRV PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libSPIRV.a
)
add_library(libMachineIndependent STATIC IMPORTED GLOBAL)
set_target_properties(libMachineIndependent PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libMachineIndependent.a
)
add_library(libOGLCompiler STATIC IMPORTED GLOBAL)
set_target_properties(libOGLCompiler PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libOGLCompiler.a
)
add_library(libOSDependent STATIC IMPORTED GLOBAL)
set_target_properties(libOSDependent PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/glslang/libOSDependent.a
)

set(glslang_libs_name libMachineIndependent libGenericCodeGen libglslang libglslang-default-resource-limits libSPIRV libOGLCompiler libOSDependent)


list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/include/v8
  ${CMAKE_CURRENT_LIST_DIR}/include/uv
)

list(APPEND CC_EXTERNAL_LIBS
    uv
    vorbisfile
    vorbis
    ogg
    libz
    sqlite3
    v8
    openal
    mpg123
    jpeg
    png
    websockets
    crypto
    curl
    webp
    sdl2
	cairo
    ${optional_libs_name}
    ${glslang_libs_name}
)
