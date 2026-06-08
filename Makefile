# Variáveis para facilitar a manutenção e leitura
CC = g++
# Flags de compilação: inclui o padrão C++11 exigido e o diretório de headers [1, 2]
CFLAGS = -std=c++11 -Iinclude
# Bibliotecas da SDL necessárias para o projeto [1, 2]
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer
# Arquivos de origem e nome do executável final
SRC = src/*.cpp
OBJ = PlayB-zombie

# Regra principal: compila o projeto
all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(OBJ)

# Regra para compilar e rodar o jogo imediatamente
run: all
	./$(OBJ)

# Regra para limpar o executável
clean:
	rm -f $(OBJ)

# Regra para só executar
play:
	./$(OBJ)

# make para compilar o projeto
# make run para compilar e rodar o jogo
# make clean para remover o executável.