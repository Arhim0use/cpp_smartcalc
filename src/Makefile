CC				=	g++
CFLAGS		=	-Wall -Wextra $(WE) -std=c++17
WE 				= -Werror
FSAN 			= -fsanitize=address 

LDFLAGS 	= -lgtest -pthread
GCFLAGS 	= -fprofile-arcs -ftest-coverage
VG_FLAGS 	=	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

PRJ = smart_calc_oop
SRC	= $(wildcard ./model/*/*.cc) $(wildcard ./controller/*.cc) 
OBJ	= $(SRC:.cc=.o)
BUILD_DIR = ../build/
TEST = test
LIB = l$(PRJ).a
FILE_TEST =	$(wildcard ./../unit_test/s21_*.cc)


all: style_check gcov_report leaks dist dvi install open


%.o: %.cc	
	@ $(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	@	echo "+-------------------+"
	@	echo "|     MAKE_LIB      |"
	@	echo "+-------------------+"
	@	ar -rcs $(BUILD_DIR)$@ $^
	@	find . -type f -name '*.o' | xargs -I {} sh -c 'mv {} ./tmp' 

$(TEST): clean $(LIB)
	@ echo "+-------------------+"
	@ echo "|     UNIT_TEST     |"
	@ echo "+-------------------+"
	@ $(CC) $(CFLAGS) $(FILE_TEST) -L. $(BUILD_DIR)$(LIB) -o $(BUILD_DIR)$@ $(LDFLAGS)
	@ ./$(BUILD_DIR)$(TEST)

clean:
	@ echo "*--------------*"
	@ echo "|     CLEAN    |"
	@ echo "*--------------*"
	@ rm -f ./*.info ./$(BUILD_DIR)$(LIB) ./*.out ./$(BUILD_DIR)$(TEST)
	@ find . -type f -name '*.o' | xargs -I {} sh -c 'echo "File deleted {} " && rm -f {}'
	@ find . -type f -name '*.gcno' -or -name '*.gcda' -or -name '$(PRJ).info' \
					| xargs -I {} sh -c 'echo "File deleted {} " && rm -f {}'
	@ rm -rf coverage test.dSYM *.zip

gcov_report: clean $(LIB)
	@ echo "+-------------------+"
	@ echo "|    GCOV_REPORT    |"
	@ echo "+-------------------+"
	@ $(CC) --coverage $(GCFLAGS) $(CFLAGS) $(LDFLAGS) $(FILE_TEST) $(BUILD_DIR)$(LIB) $(SRC) -o $(TEST) 
	@ ./$(TEST)
	@ mv ./*_test.gcno ./*_test.gcda ./tmp
	@ lcov -t lcov_branch_coverage=1 --ignore-errors  mismatch -t "$(TEST)" -o $(PRJ).info \
				-c -d ./ --no-external 
	@ genhtml -o coverage $(PRJ).info 
	@ open coverage/index.html
	@ mv ./$(TEST) $(BUILD_DIR)
	@ mv ./*.gcno ./*.gcda ./$(PRJ).info ./tmp

install: uninstall
	@ echo "*-------------------------*"
	@ echo "| ┬─┬ノ( º _ ºノ) INSTALL |"
	@ echo "*-------------------------*"
	@ cd application_view/MVCSmartCalc && qmake && make && make clean && rm Makefile && mv MVCSmartCalc.app ../../../build/SmartCalc_2.0.app

uninstall:
	@ echo "*--------------------------*"
	@ echo "| ( ╯°□°)╯ ┻━━┻ UNINSTALL  |"
	@ echo "*--------------------------*"
	@ rm -rf $(BUILD_DIR)SmartCalc_2.0.app

open:
	@ echo "*--------------------------------*"
	@ echo "|  ( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ OPEN CALC |"
	@ echo "*--------------------------------*"
	@ open $(BUILD_DIR)
	@ ./../build/SmartCalc_2.0.app/Contents/MacOS/MVCSmartCalc  

dvi:
	@ echo "*---------------*"
	@ echo "|  OPEN README  |"
	@ echo "*---------------*"
	@ open readme_SmartCalc_2.0.md
	@ open html/namespaces21.html

dist: clean
	@ echo "*---------------*"
	@ echo "|     DIST      |"
	@ echo "*---------------*"
	@ rm -rf ../Temp_SmartCalc/
	@ mkdir ../Temp_SmartCalc
	@ mkdir ../Temp_SmartCalc/src
	@ cp -r ../src/* ../Temp_SmartCalc/src
	@ mv ../Temp_SmartCalc/src .
	@ zip -0rq SmartCalc_2.0.zip src
	@ rm -rf ../Temp_SmartCalc src

#! only for school Mac
docker_setup:
	@ echo "+-------------------+"
	@ echo "|    DOCKER_SETUP   |"
	@ echo "+-------------------+"
	@ rm -rf ~/Library/Containers/com.docker.docker
	@ mkdir -p ~/goinfre/Docker/Data
	@ ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
	@ open ~/../../Applications/Docker.app

valgrind_check:
	@ echo "+-------------------+"
	@ echo "|    DOCKER_RUN     |"
	@ echo "+-------------------+"
	@ sh $(BUILD_DIR)run.sh

valgrind: 
	@	echo "+-------------------+"
	@	echo "|   VALGRIND_LEAK   |"
	@	echo "+-------------------+"
	@	CK_FORK=no valgrind  $(VG_FLAGS) ./$(BUILD_DIR)$(TEST) 

leaks: 
	@	echo "+-------------------+"
	@	echo "|     LEAKS_RUN     |"
	@	echo "+-------------------+"
	@	leaks -atExit -- ./$(BUILD_DIR)$(TEST)

style_check: 
	@ echo "+-------------------+"
	@ echo "|    STYLE_CHECK    |"
	@ echo "+-------------------+"
	@ find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "File {} checked" && clang-format -style=Google -n {}'
	@ clang-format -style=Google -n $(FILE_TEST)

style_set: clean
	@	echo "+-------------------+"
	@	echo "|     STYLE_SET     |"
	@	echo "+-------------------+"
	@	find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "File {} set Google style" && clang-format -style=Google -i {}'
	@	clang-format -style=Google -i $(FILE_TEST)
