CSTD = -std=c++11
PROG = main.cpp
CFLAGS = -g
CC = g++

CSV_FILES=${sort ${wildcard *.csv}}
TEST_NAMES=${subst .csv,,${CSV_FILES}}
TEST_OUTS=${addsuffix .out,${TEST_NAMES}}
TEST_DIFFS=${addsuffix .diff,${TEST_NAMES}}
TEST_RESULTS=${addsuffix .result,${TEST_NAMES}}
TEST_TESTS=${addsuffix .test,${TEST_NAMES}}

all : ${PROG};
   
${PROG} : Makefile
	@-rm -f $*
	${CC} ${CFLAGS} ${CSTD} main.cpp -o most_active_cookie

run: Makefile all
	./most_active_cookie cookie_log.csv -d 2018-12-08 > cookie_log.out
	./most_active_cookie duplicate.csv -d 2018-12-11 > duplicate.out
	./most_active_cookie empty.csv -d 2018-12-11 > empty.out
	./most_active_cookie repetitive.csv -d 2018-12-11 > repetitive.out
	./most_active_cookie no_matching_date.csv -d 2018-12-12 > no_matching_date.out

${TEST_DIFFS} : %.diff : Makefile run %.out %.ok
	@echo "failed to diff" > $*.diff
	-diff -a $*.out $*.ok > $*.diff 2>&1 || true

${TEST_RESULTS} : %.result : Makefile %.diff
	@echo "fail" > $*.result
	(test \! -s $*.diff && echo "pass" > $*.result) || true

${TEST_TESTS} : %.test : Makefile %.result
	@echo "$* ... `cat $*.result`"

test: ${TEST_TESTS};

clean:
	-rm -rf *.out *.diff *.err *.result *.d *.o most_active_cookie *~

.PHONY: all run test clean

-include *.d

