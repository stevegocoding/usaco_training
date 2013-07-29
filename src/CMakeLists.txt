set(PROBS
	transform
	namenum
	palsquare
	dualpal
	milk
	barn1
	calfflac
	crypt1
    packrec
    clocks
    ariprog
    milk3
    numtri
    pprime
	)

add_executable(transform transform.cpp ../data/transform.in)
add_executable(namenum namenum.cpp ../data/namenum.in ../data/dict.txt)
add_executable(palsquare palsquare.cpp ../data/palsquare.in)
add_executable(dualpal dualpal.cpp ../data/dualpal.in)
add_executable(milk milk.cpp ../data/milk.in)
add_executable(barn1 barn1.cpp ../data/barn1.in)
add_executable(calfflac calfflac.cpp ../data/calfflac.in)
add_executable(crypt1 crypt1.cpp ../data/crypt1.in)
add_executable(packrec packrec.cpp ../data/packrec.in)
add_executable(clocks clocks.cpp ../data/clocks.in)
add_executable(ariprog ariprog.cpp ../data/ariprog.in)
add_executable(milk3 milk3.cpp ../data/milk3.in)
add_executable(numtri numtri.cpp ../data/numtri.in)
add_executable(pprime pprime.cpp ../data/pprime.in)

install(TARGETS ${PROBS} RUNTIME DESTINATION bin/) 