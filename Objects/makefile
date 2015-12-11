CCC = gccfilter -c -a g++
OBJECTS = wpn_test.o Weapon.o Bullet.o Objects.o
CCFLAGS = -g -std=c++11 -pedantic -w
SFFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-system
LDFLAGS = -L/sw/gcc-${GCC4_V}/lib -static-libstdc++
test: $(OBJECTS)
	$(CCC) $(CCFLAGS) $(LDFLAGS) wpn_test.o Weapon.o Bullet.o Objects.o -o test $(SFFLAGS)
wpn_test.o: wpn_test.cc
	$(CCC) $(CCFLAGS) -c wpn_test.cc
Weapon.o: Weapon.cc
	$(CCC) $(CCFLAGS) -c Weapon.cc
Bullet.o: Bullet.cc
	$(CCC) $(CCFLAGS) -c Bullet.cc
Objects.o: Objects.cc
	$(CCC) $(CCFLAGS) -c Objects.cc
