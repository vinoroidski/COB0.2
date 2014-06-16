####################################################################
# This Makefile started out as a copy of the one in the flex manual.
# Cf. http://flex.sourceforge.net/manual/Makefiles-and-Flex.html#Makefiles-and-Flex
#
# It replaces the amazingly complex Makefile that comes with the C++calc example
# found in the Bison manual.
#
# This is Verison 0.2 of the Makefile (as of 17 April 2013, 22:00
# The previous (unnumbered) version only worked with MAKEFLAGS=-j3
# (and it's strange that it worked then).
#
####################################################################
#      "Variables", die hier benutzt werden:
#      Vgl. http://www.makelinux.net/make3/make3-CHP-2-SECT-2.html
# $@ = The filename representing the target.
# $< = The filename of the first prerequisite.
# $* = The stem of the filename of the target (i.e. without .o, .cpp...)
# $^ = The names of all the prerequisites, with spaces between them.
####################################################################
# Uncomment only one of the next two lines (choose your c++ compiler)
# CC=g++
CC=clang++

LEX=flex
YACC=bison
YFLAGS=-v -d
# Wo   -d wichtig ist, weil damit Header-Dateien erzeugt werden
#         (*.hh - und nicht nur Quellcode in *.cc)
# aber -v nicht so wichtig ist, weil damit "nur" die  Datei
#         ex3-parser.output erzeugt wird, die zwar informativ aber nicht
#         unbedingt notwendig (sie wird nicht weiterverwendet).

HEADERS=ex3-parser.hh ex3-scanner.hh

ex3 : ex3.o ex3-scanner.o ex3-parser.o ex3-driver.o NumberExprAST.o BinaryExprAST.o Root.o

ex3.o : ex3.cc ex3-driver.hh ex3-parser.hh NumberExprAST.h BinaryExprAST.h ExprAST.h Root.h

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

ex3-scanner.cc: ex3-scanner.ll
	$(LEX) $(LFLAGS) -o ex3-scanner.cc ex3-scanner.ll

ex3-parser.cc ex3-parser.hh: ex3-parser.yy
	$(YACC) $(YFLAGS) -o ex3-parser.cc ex3-parser.yy

clean:
	$(RM) *~ *.o  ex3  ex3-scanner.cc ex3-parser.cc  ex3-scanner.hh ex3-parser.hh ex3-parser.output location.hh stack.hh position.hh

tests: test.sh ex3
	./test.sh
