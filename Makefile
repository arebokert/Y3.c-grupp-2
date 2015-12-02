#
# Makefile för sfml-app, nivå G, GNU GCC (g++)
#
# Filkataloger där andra delar av programet finns.
FILEHANDLER = Filehandler
OBJS = Objects
TOOLS = Tools
GRAPHICS = Graphics

# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter.
CCC = gccfilter -c -a g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -std=c++11 -pthread

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I$(FILEHANDLER)

# Länkflaggor - Fix för att lösa lokala problem med C++ länkbibliotek.
LDFLAGS  += -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++
SFFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Objektkodsmoduler som ingår i det kompletta programmet.
OBJECTS = main.o Filehandler.o Matrix.o Player.o Camera.o

# Huvudmål - skapas med kommandot 'make'.
sfml-app: $(OBJECTS) Makefile
	$(CCC) $(OBJECTS) -o sfml-app $(LDFLAGS) $(SFFLAGS)


# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
main.o: main.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c main.cc

Filehandler.o: $(FILEHANDLER)/Filehandler.h $(FILEHANDLER)/Filehandler.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(FILEHANDLER)/Filehandler.cc

Matrix.o: $(TOOLS)/Matrix.h $(TOOLS)/Matrix.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(TOOLS)/Matrix.cc

Player.o: $(OBJS)/Character.h $(OBJS)/Player.h $(OBJS)/Player.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(OBJS)/Player.cc

Camera.o: $(GRAPHICS)/Camera.h $(GRAPHICS)/Camera.cc 
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(GRAPHICS)/Camera.cc



# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o *.gch core

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf kalkylator *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 
