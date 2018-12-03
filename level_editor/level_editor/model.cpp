#include "model.h"

model::model(int size)
{
    backing = boost::extents[size][size];
}

model::model(std::string path){
    path_to_json = path;
    //TODO!
}

int model::get_item(int x, int y){
    return backing[x][y];
}

void model::set_item(int x, int y, int item){
    backing[x][y] = item;
}
bool model::save_model(){
    return false; //TODO!
}
