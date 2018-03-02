cmake_minimum_required(VERSION 3.4.1)

include_directories(libs)

add_subdirectory(libs/zip)

file(GLOB APP_SRC
    "src/main/cpp/*.c"
    "src/main/cpp/*.cpp"
)

add_library(gles3jni SHARED ${APP_SRC})

find_library(log-lib log)
find_library(GLESv2-lib GLESv2)
find_library(EGL-lib EGL)

target_link_libraries(
   gles3jni
   zip_static

   ${log-lib}
   ${EGL-lib}
   ${GLESv2-lib}
)