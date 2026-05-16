#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.h"


class TileSet {
    public:
        // Construtor da classe TileSet
        TileSet(int tileWidth, int tileHeight, std::string file );

        // Renderiza um tile específico na posição (x, y)
        // index é o indice do tile na sprite, começando do 0
        void RenderTile(unsigned index, int x, int y);


        // Obtem o tamanho de um tile
        int GetTileWidth();
        int GetTileHeight();

    private:
        // O objeto Sprite que carrgea a imagem
        Sprite tileSet;
        
        // dimensões de cada tile e a quantidade total de tiles na imagem
        int tileWidth;
        int tileHeight;
        int tileCount;

}; 
#endif