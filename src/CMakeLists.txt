set(SOURCE_FILES main.cpp
BSPTypes.h
Quake3BSP.h
Quake3BSP.cpp
Common.h
Common.cpp
stb_lib.h
stb_image.c
glew.h
wglew.h
glew.c
ShaderManager.h
ShaderManager.cpp
Keyboard.h
Keyboard.cpp
FreeCamera.h
FreeCamera.cpp
Renderer.h
Renderer.cpp
Texture.h
Texture.cpp)

set(EXTERNAL_LIBS glfw ${GLFW_LIBRARIES})

add_executable(Q3MapView ${SOURCE_FILES})
target_link_libraries(Q3MapView ${EXTERNAL_LIBS})

install (TARGETS Q3MapView DESTINATION ../bin)