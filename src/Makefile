CC				=	g++
CFLAGS		=	-Wall -Wextra -std=c++17
WE 				= -Werror
FSAN 			= -fsanitize=address 

LDFLAGS = -lgtest -pthread
GCFLAGS = -fprofile-arcs -ftest-coverage
VG_FLAGS =	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# SRC	= $(wildcard ./model/since_calc/calc_validation.cc) 
# OBJ	= $(patsubst ./model/since_calc/calc_validation.cc, ./model/since_calc/calc_validation.o, ${SRC})

SRC	= $(wildcard ./model/since_calc/*.cc) 
OBJ	= $(patsubst ./model/since_calc/%.cc, ./model/since_calc/%.o, ${SRC})
TEST = test
LIB = lsmart_calc_oop.a
FILE_TEST =	$(wildcard ./unit_test/s21_*.cc)
all: clean mcc

mcc: 
	$(CC) -g $(CFLAGS) main.cc $(SRC) 
	./a.out

$(LIB):
	@echo "+-------------------+"
	@echo "|     MAKE_LIB      |"
	@echo "+-------------------+"
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC) 
# mv *_credit.o *_deposit.o ./model/bank_calc
	mv *.o ./model/since_calc
	ar -rcs $@ $(OBJ)

$(TEST): clean $(LIB)
	@echo "+-------------------+"
	@echo "|     UNIT_TEST     |"
	@echo "+-------------------+"
	@$(CC) $(CFLAGS) $(FILE_TEST) -L. $(LIB) -o $@ $(LDFLAGS)
	@./$(TEST)

clean:
# @ echo "*--------------*"
# @ echo "|     CLEAN    |"
# @ echo "*--------------*"
	@ rm -f *.a *.gcda *.gcno *.info *.out test
	@ rm -f ./*.o ./*.gcda ./*.gcno ./*.info ./*.out 
	@ rm -f ./model/since_calc/*.o
	@ rm -rf coverage test.dSYM *.zip


docker_setup:
	@echo "+-------------------+"
	@echo "|    DOCKER_SETUP   |"
	@echo "+-------------------+"
	@rm -rf ~/Library/Containers/com.docker.docker
	@mkdir -p ~/goinfre/Docker/Data
	@ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
	@open ~/../../Applications/Docker.app

docker:
	@echo "+-------------------+"
	@echo "|    DOCKER_RUN     |"
	@echo "+-------------------+"
	@sh ../build/run.sh

valgrind: test
	@echo "+-------------------+"
	@echo "|   VALGRIND_LEAK   |"
	@echo "+-------------------+"
	@CK_FORK=no valgrind  $(VG_FLAGS) ./../build/$(TEST)

leaks: 
	@echo "+-------------------+"
	@echo "|     LEAKS_RUN     |"
	@echo "+-------------------+"
	@leaks -atExit -- ./../build/$(TEST)