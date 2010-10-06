CPPUTEST_HOME = $(pwd)
all: CppUTest/lib/libCppUTest.a
	make -i -C CppUTest
	make -i -C t0
	make -i -C t1
	make -i -C t2
	make -i -C t3
	make -i -C SandBox
	make -i -C tests
	make -i -C unity

clean:
	make -i -C t0 clean
	make -i -C t1 clean
	make -i -C t2 clean
	make -i -C t3 clean
	make -i -C SandBox clean
	make -i -C tests clean
	make -i -C unity clean
	
CppUTest/lib/libCppUTest.a:
	pwd
	make -i -C CppUTest
	