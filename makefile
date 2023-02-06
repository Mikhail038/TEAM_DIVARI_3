#=============================================================================================================================================================================

VR_FLAGS = -D _DEBUG -g -ggdb3 -std=c++17 -O0

ASSAN = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

DOP = -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE

DIRECTORIES = -IEXTRA

VR_FLAGS += $(ASSAN)

VR_FLAGS += $(DIRECTORIES)

VR_FLAGS += $(DOP)

#=============================================================================================================================================================================

VR_COMPILER = g++

#=============================================================================================================================================================================

VR_SRC = .

VR_OBJ = OBJECTS

#=============================================================================================================================================================================

DO: FOLDERS  DO_RPN

FOLDERS:
	mkdir -p OBJECTS;

DO_RPN: $(VR_OBJ)/rpn_main.o $(VR_OBJ)/calculating.o $(VR_OBJ)/pst_notation.o $(VR_OBJ)/post_conversion.o
	$(VR_COMPILER) $(VR_OBJ)/rpn_main.o $(VR_OBJ)/calculating.o $(VR_OBJ)/pst_notation.o $(VR_OBJ)/post_conversion.o -o rpn $(VR_FLAGS)

#=============================================================================================================================================================================

$(VR_OBJ)/rpn_main.o: $(VR_SRC)/rpn_main.cpp
	$(VR_COMPILER) -c -o $(VR_OBJ)/rpn_main.o $(VR_SRC)/rpn_main.cpp $(VR_FLAGS)

$(VR_OBJ)/calculating.o: $(VR_SRC)/calculating.cpp
	$(VR_COMPILER) -c -o $(VR_OBJ)/calculating.o $(VR_SRC)/calculating.cpp $(VR_FLAGS)

$(VR_OBJ)/pst_notation.o: $(VR_SRC)/pst_notation.cpp
	$(VR_COMPILER) -c -o $(VR_OBJ)/pst_notation.o $(VR_SRC)/pst_notation.cpp $(VR_FLAGS)

$(VR_OBJ)/post_conversion.o: $(VR_SRC)/post_conversion.cpp
	$(VR_COMPILER) -c -o $(VR_OBJ)/post_conversion.o $(VR_SRC)/post_conversion.cpp $(VR_FLAGS)

#=============================================================================================================================================================================

# vg:
# 	colour-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./front

#=============================================================================================================================================================================
