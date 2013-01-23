set(PROBS
	transform
	namenum
	palsquare
	dualpal
	milk
	barn1
	calfflac
	crypt1
	)
add_executable(transform transform.cpp ../data/transform.in)
add_executable(namenum namenum.cpp ../data/namenum.in ../data/dict.txt)
add_executable(palsquare palsquare.cpp ../data/palsquare.in)
add_executable(dualpal dualpal.cpp ../data/dualpal.in)
add_executable(milk milk.cpp ../data/milk.in)
add_executable(barn1 barn1.cpp ../data/barn1.in)
add_executable(calfflac calfflac.cpp ../data/calfflac.in)
add_executable(crypt1 crypt1.cpp ../data/crypt1.in)


install(TARGETS ${PROBS} RUNTIME DESTINATION bin/) 