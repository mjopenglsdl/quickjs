project(demo)

add_executable(${PROJECT_NAME}
    main.cpp
    demo_app.cpp
    qjs-mylib.c
)

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/quickjs-libc.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${qjs_defines})
target_link_libraries(${PROJECT_NAME} qjs)