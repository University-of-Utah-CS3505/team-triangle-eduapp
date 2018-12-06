#ifndef MODEL_H
#define MODEL_H
#include <boost/multi_array.hpp>

class model
{
public:
    model(int backing_size);
    model(std::string path_to_json);//load model from json obj.
    int get_item(int x, int y);
    void set_item(int x, int y, int item);
    bool save_model();
    void resize_array(int size);
    void remove_object(int val);
    void add_object(std::string s, int loc1, int loc2 );
    void update_loc1(int obj, int loc1);
    void update_loc2(int obj, int loc2);
    boost::multi_array<int,2> backing;

    std::string path_to_json;
    std::string levelname;//do we check this? or just add it as last name +1?
    std::string findNextLevel();
    std::vector<std::tuple<std::string,int,int>> objects;
    std::vector<std::tuple<std::string,std::string>> tiledefs;

};

#endif // MODEL_H
