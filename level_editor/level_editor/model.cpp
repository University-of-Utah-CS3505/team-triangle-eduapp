#include "model.h"
#include "QJsonObject"
#include "QFile"
#include "QByteArray"
#include "QJsonObject"
#include "qjsondocument.h"
#include "QJsonArray"
#include "QDir"
#include "iostream"
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
    std::string lvlname = findNextLevel();
    QJsonObject json;
    //Tiles
    QJsonArray* bigarray =  new QJsonArray;
    QJsonArray* miniarray =  new QJsonArray;
    for(int i =0; i < backing.size(); i++){
        for (int j = 0; j < backing.size(); j++){
            miniarray->append(backing[i][j]);
        }
        bigarray->append(*miniarray);
        miniarray =  new QJsonArray();
    }
    json["name"] = "custom levelname";
    json["tiles"] = *bigarray;
    std::cout << "FINISHED ARRA" << std::endl;


    //Objects
    QJsonArray ob;

    for(auto item : objects){
        QJsonObject* objpointer = new QJsonObject;
        QJsonObject obj = *objpointer;
        if(std::get<0>(item) == std::string("spawn")){
                obj["type"] = "spawn";
                QJsonArray size_ob;
                size_ob.append(16);
                size_ob.append(28);

                obj["size"] = size_ob;
                obj["img"] = "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/shotOrange.png";

        }
         else if(std::get<0>(item) == std::string("destroyable")){
                obj["type"] = "destroyable";
                QJsonArray size_ob;
                size_ob.append(28);
                size_ob.append(28);

                obj["size"] = size_ob;
                obj["img"] = "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/flag.png";
        }
        else{
            obj["type"] = "goal";
            QJsonArray size_ob;
            size_ob.append(32);
            size_ob.append(32);

            obj["size"] = size_ob;
            obj["img"] = "../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/crateWood.png";
        }
        QJsonArray pos;
        pos.append(std::get<1>(item));
        pos.append(std::get<2>(item));
        obj["pos"] = pos;

    ob.append(obj);
    }
    json.insert("objects", ob);
    std::cout << "FINISHED OB" << std::endl;
    QJsonArray tiledefsjson;
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater1.png", "water"));
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadNorth.png", "road"));
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadEast.png", "road"));
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater1.png", "road"));
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater1.png", "road"));
    tiledefs.emplace_back(std::make_tuple("../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater1.png", "road"));   //HARDCODED!

    for(auto item : tiledefs){
        QJsonObject* tile  = new QJsonObject;
        auto tilederef = *tile;
        auto item2 = std::get<0>(item);
        tilederef.insert("img", item2.c_str()) ;
        tilederef.insert("type",  std::get<1>(item).c_str()) ;
        tiledefsjson.append(*tile);

    }
    std::cout << "FINISHED TILEDEF" << std::endl;
    json["tiledefs"] = tiledefsjson;
    std::string str("../../levels");
    str+= lvlname;
    std::cout << str.c_str() << std::endl;
    QDir().mkdir(str.c_str());
    str+= "/level.json";
    QFile writeFile(str.c_str());
    writeFile.open(QIODevice::WriteOnly);
    QJsonDocument docs(json);
    writeFile.write(docs.toJson());
    writeFile.close();
    return true; //TODO!
}

void model::resize_array(int size){
    backing.resize(boost::extents[size][size]);
}

std::string model::findNextLevel(){
    QFile file("../../levels/levels.json");
    file.open(QIODevice::ReadWrite);
    QByteArray barray = file.readAll();
    QJsonDocument doc;
    doc.fromJson(barray);
    QJsonObject json = doc.object();
    QJsonArray lev = json["levels"].toArray();
    QString q = QString::number(lev.size());
    q.prepend("/level");
    //q.append("");
    file.close();
    return q.toUtf8().constData();
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

/*
 * "tiledefs":[
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater1.png",
        "type":"water"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadNorth.png",
        "type":"road"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadEast.png",
        "type":"road"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadCrossing.png",
        "type":"road"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadCornerUR.png",
        "type":"road"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadCornerLL.png",
        "type":"road"
    },
    {
        "img":"../team-triangle-eduapp/assets/Tanks/PNG/DefaultSize/tileWater_roadCornerUL.png",
        "type":"road"
    }
    ]
    */
