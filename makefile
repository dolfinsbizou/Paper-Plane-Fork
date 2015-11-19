LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all: compile paper-plane
Tile.o: src/Tile.cpp
	g++ -std=c++11 -c src/Tile.cpp -o output/Tile.o
Tilemap.o: src/Tilemap.cpp
	g++ -std=c++11 -c src/Tilemap.cpp -o output/Tilemap.o
BackgroundGenerator.o: src/BackgroundGenerator.cpp
	g++ -std=c++11 -c src/BackgroundGenerator.cpp -o output/BackgroundGenerator.o
Entity.o: src/Entity.cpp
	g++ -std=c++11 -c src/Entity.cpp -o output/Entity.o
ParticleSystem.o: src/ParticleSystem.cpp
	g++ -std=c++11 -c src/ParticleSystem.cpp -o output/ParticleSystem.o
PhysicGenerator.o: src/PhysicGenerator.cpp
	g++ -std=c++11 -c src/PhysicGenerator.cpp -o output/PhysicGenerator.o
Tileset.o: src/Tileset.cpp
	g++ -std=c++11 -c src/Tileset.cpp -o output/Tileset.o
ResourcePath.o: src/ResourcePath.cpp
	g++ -std=c++11 -c src/ResourcePath.cpp -o output/ResourcePath.o
main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp -o output/main.o
compile:
	@echo "** Compilation de Paper Plane"
	@mkdir -p output
paper-plane: main.o ResourcePath.o Tileset.o PhysicGenerator.o ParticleSystem.o Entity.o BackgroundGenerator.o Tilemap.o Tile.o
	g++ -o paper-plane output/* $(LIBS)
clean:
	@echo "** Nettoyage de la compilation"
	rm -f paper-plane
	rm -rf output/
	rm -f res/score.dat
