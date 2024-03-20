CC				=	g++ -g
CFLAGS		=	-Wall -Wextra -std=c++17
WE 				= -Werror
FSAN 			= -fsanitize=address 
all: clean mcc

mcc: 
	$(CC) $(CFLAGS) main.cc model/since_calc/*.cc 
	./a.out


clean:
# @ echo "*--------------*"
# @ echo "|     CLEAN    |"
# @ echo "*--------------*"
	@ rm -f *.a *.gcda *.gcno *.info *.out test
	@ rm -f ./*.o ./*.gcda ./*.gcno ./*.info ./*.out 
	@ rm -rf coverage test.dSYM *.zip