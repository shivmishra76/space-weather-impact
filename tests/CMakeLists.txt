add_executable(test_fetcher test_fetcher.cpp ../src/fetcher.cpp)
target_link_libraries(test_fetcher PRIVATE CURL::libcurl)
add_test(NAME test_fetcher COMMAND test_fetcher)

add_executable(test_parser test_parser.cpp ../src/parser.cpp)
add_test(NAME test_parser COMMAND test_parser)

add_executable(test_model test_model.cpp ../src/model.cpp)
add_test(NAME test_model COMMAND test_model)
