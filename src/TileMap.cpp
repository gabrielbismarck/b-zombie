#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
    
    // Seta o TileSet
    this->tileSet.reset(tileSet);
    
    // Carrega os dados do mapa a partir do arquivo especificado
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream input(file);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir o arquivo do mapa: " << file << std::endl;
        return;
    }
    mapWidth = mapHeight = mapDepth = 0; 

    char comma;
    // Verifica se a leitura das dimensões foi bem sucedida antes do resize
    if (!(input >> mapWidth >> comma >> mapHeight >> comma >> mapDepth >> comma)) {
        std::cerr << "Erro ao ler as dimensões do mapa!" << std::endl;
        return;
    }

    // Garante que não tentaremos alocar memória se os valores forem zero 
    if (mapWidth > 0 && mapHeight > 0 && mapDepth > 0) {
        tileMatrix.resize(mapWidth * mapHeight * mapDepth);
        for (int i = 0; i < (int)tileMatrix.size(); i++) {
            input >> tileMatrix[i] >> comma;
        }
    }
}
void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::Update(float dt) {}

void TileMap::RenderLayer(int layer) {
    // obtém as dimensões dos tiles
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();

    for (int y = 0; y < mapHeight; y++){
        for (int x = 0; x < mapWidth; x++){
            int tileIndex = At(x, y, layer);

            if (tileIndex != -1) {

                float posx = (float)(associated.box.x + (x * tileWidth));
                float posy = (float)(associated.box.y + (y * tileHeight));

                // Renderiza o tile na posição correta, multiplicando as coordenadas do tile pelo tamanho do tile
                tileSet->RenderTile((unsigned)tileIndex, posx, posy);
            }

        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; z++)
        RenderLayer(z);
}