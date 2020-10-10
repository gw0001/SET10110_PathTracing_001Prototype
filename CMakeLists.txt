##### CMAKE LISTS #####

### MINIMUM VERSION OF CMAKE REQUIRED ###
cmake_minimum_required(VERSION 3.9)

### VISUAL STUDIO PROJECT NAME ###
project(Path-Tracing_Prototype)

### C++ VERSION ###
set (CMAKE_CXX_STANDARD 11)

### SOURCE ###

set (STB stb/stb.h stb/stb_image.h stb/stb_image_write.h)

set (SOURCE_PATH_TRACER_PROTOTYPE ${STB} PathTracerPrototype/main.cpp)


# Executables
add_executable(Path-Tracing_Prototype ${SOURCE_PATH_TRACER_PROTOTYPE})


target_include_directories(Path-Tracing_Prototype PRIVATE .)
