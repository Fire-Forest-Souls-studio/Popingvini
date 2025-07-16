cmake_minimum_required(VERSION 3.16)
project(Popingvini VERSION 1.0.0 LANGUAGES CXX)

# 1) Компилятор и стандарт
set(CMAKE_CXX_COMPILER gcc-13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2) Опция статической сборки
option(BUILD_STATIC "Build a fully static executable" OFF)

# 3) Базовые флаги
set(BASE_FLAGS "-g -Wall -W -pg")
if (BUILD_STATIC)
  set(CMAKE_EXE_LINKER_FLAGS "${BASE_FLAGS} -static")
  set(CMAKE_CXX_FLAGS        "${BASE_FLAGS}")
  set(CMAKE_C_FLAGS          "${BASE_FLAGS}")
else()
  set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} ${BASE_FLAGS}")
  set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS}   ${BASE_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "-pg -z execstack")
endif()

# 4) Пути
set(SRC_DIR   "${CMAKE_SOURCE_DIR}/src")
set(RES_DIR   "${CMAKE_SOURCE_DIR}/Resources")
include_directories("${SRC_DIR}")

# 5) Исходники
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/Code/src/*.cpp"
)

# 6) Встраивание ресурсов через objcopy
find_program(OBJCOPY_EXECUTABLE objcopy REQUIRED)

file(GLOB_RECURSE RESOURCE_RAW_FILES
    "${RES_DIR}/Images/*.png"
    "${RES_DIR}/Sound/*.ogg"
    "${RES_DIR}/Shrift/*.otf"
)

set(RESOURCE_OBJ_FILES)
foreach(raw ${RESOURCE_RAW_FILES})
    # относительный путь "Resources/Images/icon.png"
    file(RELATIVE_PATH rel_path "${CMAKE_SOURCE_DIR}" "${raw}")
    string(REGEX REPLACE "[/\\\\\\.]" "_" sym "${rel_path}")
    set(out_obj "${CMAKE_BINARY_DIR}/resources/${sym}.o")

    add_custom_command(
      OUTPUT "${out_obj}"
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/resources"
      COMMAND ${OBJCOPY_EXECUTABLE}
        --input binary
        --output elf64-x86-64
        --binary-architecture i386
        "${rel_path}"
        "${out_obj}"
      DEPENDS "${raw}"
      COMMENT "Embedding ${rel_path} → ${sym}.o"
    )

    list(APPEND RESOURCE_OBJ_FILES "${out_obj}")
endforeach()

# 7) Основной исполняемый с ресурсами
add_executable(Popingvini
  ${SRC_FILES}
  ${RESOURCE_OBJ_FILES}
)
set_target_properties(Popingvini PROPERTIES
  OUTPUT_NAME "Попингвини"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# 8) Линковка SFML и прочих библиотек
if (BUILD_STATIC)
  find_package(SFML 2.5 COMPONENTS window graphics audio system REQUIRED STATIC)
  target_link_libraries(Popingvini PRIVATE
    sfml-window-s  sfml-graphics-s  sfml-audio-s  sfml-system-s
    stdc++ m
  )
else()
  find_package(SFML 2.5 COMPONENTS window graphics audio system REQUIRED)
  target_link_libraries(Popingvini PRIVATE
    sfml-window  sfml-graphics  sfml-audio  sfml-system
    stdc++ m
  )
endif()
