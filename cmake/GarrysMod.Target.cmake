file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.hpp
)

add_library(${TARGET_NAME} SHARED)

target_sources(${TARGET_NAME}
        PRIVATE
        ${PROJECT_SOURCES}
)

target_include_directories(${TARGET_NAME}
        PRIVATE
        src
)

target_link_libraries(${TARGET_NAME}
        PRIVATE
        minhook
        imgui_dx9
)