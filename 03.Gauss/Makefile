CXX_EXTRA_FLAGS=-I ../external/lazycsv/include -I ../external/eigen $(shell pkgconf --cflags openblas)
LD_EXTRA_OPT=$(shell pkgconf --libs openblas)

include ../Makefile.inc

# Объявляем цели, которые не являются файлами
.PHONY: release run_utest run_itest astyle all

release : gauss

gauss : util.r.o Gauss_main.r.o Gauss_solve.r.o
	$(LD) -o $@ $^ $(LD_EXTRA_OPT)

debug : util.d.o Gauss_main.d.o Gauss_solve.d.o
	$(LD) -o $@ $^ $(LD_EXTRA_OPT)

utest : Gauss_test.d.o util.d.o Gauss_solve.d.o
	$(LD) -o $@ $^ $(GTEST_LIBS)

run_utest : utest debug
	./utest

run_itest : debug
	@echo "Integration tests..."
	./integration_test.sh

astyle:
	astyle --options=../astyle.ini *.h *.cpp

all: depends run_utest run_itest

include Makefile.hdrdep