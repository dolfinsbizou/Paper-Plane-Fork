LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all: compile paper-plane
%.o: src/%.cpp
	g++ -Wall -std=c++17 -c $< -o output/$@
compile:
	@echo "** Compilation de Paper Plane"
	@mkdir -p output
paper-plane: main.o ResourcePath.o Tileset.o PhysicGenerator.o ParticleSystem.o Entity.o BackgroundGenerator.o Tilemap.o Tile.o
	g++ -o paper-plane output/* $(LIBS)
clean:
	@echo "** Nettoyage de la compilation"
	rm -rf `git check-ignore ./*`
