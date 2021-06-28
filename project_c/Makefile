# The compiler: gcc for C program

CC=gcc

# compiler flags:
# -Wall turns on most, but not all, compiler warnings
# -std=c99 sets the language dialect to include syntax from the C99 standard, such as bool and other features used in CPU2017 benchmarks.

CFLAGS=-w --std=c99 -Wextra -Wall -O3 -D_GNU_SOURCE 

PKG=`pkg-config --cflags --libs glib-2.0`

# define any directories containing header files other than /usr/include

INCLUDES=includes

EXECUTABLE=program

# define the C source files

SRC=src

# define the C object files

OBJ=obj

# the build target executable

program: $(SRC)/prog.c $(SRC)/model/business.c $(SRC)/model/businesses.c $(SRC)/model/user.c $(SRC)/model/users.c $(SRC)/model/review.c $(SRC)/model/reviews.c $(SRC)/model/dataCross.c $(SRC)/model/sgr.c $(SRC)/model/errors.c $(SRC)/model/table.c $(SRC)/model/utils.c $(SRC)/model/variable.c $(SRC)/model/variable_list.c $(SRC)/controller/comint.c $(SRC)/controller/csv.c $(SRC)/controller/filter.c $(SRC)/controller/proj.c $(SRC)/controller/x.c $(SRC)/controller/controller.c $(SRC)/view/ui.c
	$(CC) -o program $(CFLAGS) $(SRC)/prog.c $(SRC)/model/business.c $(SRC)/model/businesses.c $(SRC)/model/user.c $(SRC)/model/users.c $(SRC)/model/review.c $(SRC)/model/reviews.c $(SRC)/model/dataCross.c $(SRC)/model/sgr.c $(SRC)/model/errors.c $(SRC)/model/table.c $(SRC)/model/utils.c $(SRC)/model/variable.c $(SRC)/model/variable_list.c $(SRC)/controller/comint.c $(SRC)/controller/csv.c $(SRC)/controller/filter.c $(SRC)/controller/proj.c $(SRC)/controller/x.c $(SRC)/controller/controller.c $(SRC)/view/ui.c $(PKG)

memcheck:
	valgrind --leak-check=yes ./program

clean:
	rm -rf $(OBJ)/*.o program