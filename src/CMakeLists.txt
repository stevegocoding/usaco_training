add_executable(ride ride.cpp)
add_executable(gift1 gift1.cpp ../data/gift1.in)
install(TARGETS ride RUNTIME DESTINATION bin/ride)
install(TARGETS gift1 RUNTIME DESTINATION bin/gift1)