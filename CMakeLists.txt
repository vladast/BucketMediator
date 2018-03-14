cmake_minimum_required(VERSION 2.8)

project(bucketmediator)

set(CMAKE_CXX_STANDARD 11)

find_package(AWSSDK REQUIRED)
include_directories(${PROJECT_SOURCE_DIR})
link_directories(/usr/local/lib)

add_definitions(-DUSE_IMPORT_EXPORT)
add_executable(${PROJECT_NAME}
    main.cpp
    AwsS3Helper.cpp
    FileHelper.cpp
    FileInfo.cpp
    AudioInfoSerializer.cpp
    FileSizeInfoSerializer.cpp
    RestServer.cpp
    HttpRequest.cpp
    HttpResponse.cpp)

target_link_libraries(${PROJECT_NAME} aws-cpp-sdk-core aws-cpp-sdk-s3)
