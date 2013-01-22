set(PROBS
	transform
	namenum
	palsquare
	dualpal
	)
add_executable(transform transform.cpp ../data/transform.in)
add_executable(namenum namenum.cpp ../data/namenum.in ../data/dict.txt)
add_executable(palsquare palsquare.cpp ../data/palsquare.in)
add_executable(dualpal dualpal.cpp ../data/dualpal.in)
install(TARGETS ${PROBS} RUNTIME DESTINATION bin/)