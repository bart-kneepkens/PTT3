#include "Message.h"

Message::Message(int grid [][10])
: grid(grid){}

int [][] Message::GetGrid() const{
    return grid;
}
