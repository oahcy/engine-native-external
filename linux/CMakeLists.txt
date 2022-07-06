set(linux_lib_dir ${platform_spec_path}/lib)
MESSAGE(STATUS "${platform_spec_path}")

add_library(v8 STATIC IMPORTED GLOBAL)
set_target_properties(v8 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/v8/libv8_monolith.a
)

add_library(sdl2 STATIC IMPORTED GLOBAL)
set_target_properties(sdl2 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/sdl2/libSDL2.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/sdl2
)

list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/v8
)

include("/home/yc/code/conan-exp/cocos_libs/build/conanbuildinfo.cmake")
conan_basic_setup()

list(APPEND CC_EXTERNAL_LIBS
    v8
    ${CONAN_LIBS}
)

if(NOT USE_SERVER_MODE)
  list(APPEND CC_EXTERNAL_LIBS sdl2)
endif()
