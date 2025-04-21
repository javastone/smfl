//
// Created by sophi on 4/17/2025.
//

#ifndef TILE_H
#define TILE_H

class tile {
  bool isFlagged = false;
  bool isMine = false;
  bool isOpen = false;
  int minesAround;
  int x;
  int y;
public:
  tile(int column, int row) {
    x = column;
    y = row;
  }
  bool getFlagged() {
    return isFlagged;
  }

  bool getMine() {
    return isMine;
  }

  bool getOpen() {
    return isOpen;
  }

  void setOpen(bool open) {
    isOpen = open;
  }

  void setFlagged(bool flagged) {
    isFlagged = flagged;
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getMinesAround() {
    return minesAround;
  }

  void setMinesAround(int minesAround) {
    this->minesAround = minesAround;
  }

  void setMineState(bool state) {
    isMine = state;
  }

};

#endif //TILE_H