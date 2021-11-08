NAME_LIB = libmx.a

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: clean create_obj LIBMX create_lib

create_obj:
	mkdir obj

LIBMX:
	cp -f inc/libmx.h src/
	clang $(FLAGS) -c src/*.c
	mv *.o obj/
	rm src/libmx.h

create_lib:
	ar -rc $(NAME_LIB) obj/*.o
	ranlib $(NAME_LIB)

clean:
	rm -rf obj

uninstall:
	rm -rf obj
	rm -rf $(NAME_LIB)

reinstall:
	make uninstall
	make