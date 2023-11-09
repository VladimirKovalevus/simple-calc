CPP= g++

TEST= test/*.cpp service/polishnotation.cpp service/utils.cpp
DIST= dist
DISTNAME=simplecalc
CFLAGS= -Wall -Werror -Wextra -lgtest



INVISIBLE= /dev/null

ifeq ($(shell uname -s), Linux)
	TESTFLAGS+=-lpthread -lrt 
endif

all: install

install:
	-mkdir -p ../build
	cd ../build && cmake ../simple-calc && make
	./../build/simple-calc

uninstall:
	-rm -rf ../build

clean: uninstall
	-rm -rf */.DS_Store
	-rm -rf .DS_Store
	-rm -rf ./SmartCalc_v1/backend/calculator.h.gch
	-rm -rf ../.DS_Store
	-rm -rf *.o *.a
	-rm -rf *gcno *.gcda *.info *.out *.gcov
	-rm -rf ./report
	-rm -rf test.out.dSYM
	-rm -rf docs/html
	-rm -rf frontend/moc*

dvi:
	doxygen doxy
	xdg-open html/index.html

dist:
	mkdir -p ../$(DIST)
	cd .. && cp -r simple-calc/* $(DIST)
	cd .. && tar cvzf simple-calc.tgz $(DIST)/
	rm -rf ../$(DIST)

test: 
	$(CPP) $(TEST) -o test.out $(CFLAGS)
	./test.out
	


reinstall: uninstall clean install

style:
	clang-format --style=GOOGLE -n $(SOURCE_CODE)

format:
	clang-format --style=GOOGLE -i $(SOURCE_CODE)

valgrind: backend $(TEST)
	$(CC) $(GCOVFLAGS) $(TEST) backend.a -o test.out $(TESTFLAGS)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="val_out.txt" -s ./test.out
	grep ERROR val_out.txt
	make clean
	cat val_out.txt

.PHONY: test