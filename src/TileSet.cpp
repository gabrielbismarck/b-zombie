#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file ) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    
    if(tileSet.IsOpen()) {
        int columns = tileSet.GetWidth() / tileWidth;
        int rows = tileSet.GetHeight() / tileHeight;
        
        // Total de tiles
        tileCount = columns * rows;
        tileSet.SetFrameCount(columns, rows);
    }
}

void TileSet::RenderTile(unsigned index, int x, int y) {
    //  Verifica se o índice do tile é válido (esta entre 0 e tileCount-1) antes de renderizar
    if(index < (unsigned)tileCount) {
        // Seta o frame do tile correspondente ao índice e renderiza na posição (x, y)
        tileSet.SetFrame(index);
        tileSet.Render(x, y, tileWidth, tileHeight);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}