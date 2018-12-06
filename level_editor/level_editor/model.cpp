#include "model.h"
#include "QJsonObject"
#include "QFile"
#include "QByteArray"
#include "QJsonObject"
#include "qjsondocument.h"
#include "QJsonArray"
model::model(int size)
{
    backing.resize(boost::extents[0][0]);
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
    QFile file(":/../levels/levels.json");
    std::string levename  = findNextLevel();
    file.open(QIODevice::ReadWrite);
    QByteArray barray = file.readAll();
    QJsonDocument doc;
    doc.fromJson(barray);
    QJsonObject json = doc.object();
    //Tiles
    QJsonArray* bigarray;
    QJsonArray* miniarray;
    for(int i =0; i < backing.size(); i++){
        for (int j = 0; j < backing.size(); j++){
            miniarray->append(backing[i][j]);
        }
        bigarray->append(*miniarray);
        miniarray =  new QJsonArray();
    }
    //Objects
    QJsonArray ob;
    //TODO!







    return false; //TODO!
}

void model::resize_array(int size){
    backing.resize(boost::extents[size][size]);
}
std::string model::findNextLevel(){
    QFile file(":/../levels/levels.json");
    file.open(QIODevice::ReadOnly);
    QByteArray barray = file.readAll();
    QJsonDocument doc;
    doc.fromJson(barray);
    QJsonObject json = doc.object();
    //QJsonValue
}

void model::add_object(std::string s, int loc1, int loc2){
    auto t = std::make_tuple(s,loc1,loc2);
    objects.emplace_back(t);
}
void model::remove_object(int val){
    objects.erase(objects.begin()+ val);
}
void model::update_loc1(int obj, int loc1){
    std::get<1>(objects[obj])=loc1;
}
void model::update_loc2(int obj, int loc2){
    std::get<1>(objects[obj])=loc2;
}
