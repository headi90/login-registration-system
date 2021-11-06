cmake_minimum_required(VERSION 3.10)

project(LoginRegistrationSystem VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include(FetchContent)

##############################################################################################################
# Google test download
message("Google test download")
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
##############################################################################################################

##############################################################################################################
#OpenSSL finding
find_package(OpenSSL REQUIRED)

message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")

include_directories(${OPENSSL_INCLUDE_DIR})
list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
##############################################################################################################


##############################################################################################################
# Nlohmann JSON library download
message("Nlohmann JSON library download")
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT NLOHMANNJSON_ROOT)
  set(NLOHMANNJSON_ROOT "${CMAKE_BINARY_DIR}/_deps/json-src/include")
endif()

message("NLOHMANNJSON_ROOT: ${NLOHMANNJSON_ROOT}")

##############################################################################################################

set(SOURCES
    src/user.cpp
    src/md5PasswordHasher.cpp
    src/sha256PasswordHasher.cpp
    src/passwordValidator.cpp
    src/jsonUserDatabaseHandler.cpp
    src/loginPasswordManager.cpp
    )
    
set(HEADERS
    inc/user.hpp
    inc/iPasswordHasher.hpp
    inc/md5PasswordHasher.hpp
    inc/sha256PasswordHasher.hpp
    inc/iPasswordValidator.hpp
    inc/passwordValidator.hpp
    inc/iUserDatabaseHandler.hpp
    inc/jsonUserDatabaseHandler.hpp
    inc/loginPasswordManager.hpp
    )
    
set(TESTS
    tests/user.ut.cpp
    tests/md5PasswordHasher.ut.cpp
    tests/sha256PasswordHasher.ut.cpp
    tests/passwordValidator.ut.cpp
    tests/jsonUserDatabaseHandler.ut.cpp
    tests/loginPasswordManager.ut.cpp
    )

set(FLAGS 
    -Wall
    -Wextra
    -pedantic
    -Wconversion
    -Werror
    )


add_library(${PROJECT_NAME}-lib STATIC ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME}-ut ${TESTS})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib ssl crypto nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gmock gtest_main ssl crypto)

target_include_directories(${PROJECT_NAME} PRIVATE inc ${NLOHMANNJSON_ROOT})
target_include_directories(${PROJECT_NAME}-ut PRIVATE inc ${NLOHMANNJSON_ROOT})
target_include_directories(${PROJECT_NAME}-lib PRIVATE inc ${NLOHMANNJSON_ROOT})

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

add_test(NAME ${PROJECT_NAME}-tests COMMAND ${PROJECT_NAME}-ut)