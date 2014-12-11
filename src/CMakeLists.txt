set(SOURCE_FILES main.cpp
BSPTypes.h
Quake3BSP.h
Quake3BSP.cpp
Common.h)
set(EXTERNAL_LIBS glfw ${GLFW_LIBRARIES})

add_executable(Q3MapView ${SOURCE_FILES})
target_link_libraries(Q3MapView ${EXTERNAL_LIBS})

install (TARGETS Q3MapView DESTINATION ../bin)