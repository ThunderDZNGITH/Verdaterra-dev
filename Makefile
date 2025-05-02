CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Recherche récursive des .cpp
SRCS = $(shell find src -name '*.cpp')
# Transforme les noms de fichiers source en noms d'objets dans un dossier temporaire
OBJS = $(SRCS:.cpp=.o)

EXEC = Verdaterra

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LIBS)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
