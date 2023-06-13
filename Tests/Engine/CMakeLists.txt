include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB Engine_Tests_cpp
        "*.cpp")
file(GLOB Engine_head_SRC
        "../../Engine/*.h")
file(GLOB Engine_imp_SRC
        "../../Engine/*.cpp")
add_executable(EngineTests ${Engine_Tests_cpp} ${Engine_head_SRC} ${Engine_imp_SRC})
target_link_libraries(EngineTests gtest_main)
add_test(NAME example_test COMMAND example)
