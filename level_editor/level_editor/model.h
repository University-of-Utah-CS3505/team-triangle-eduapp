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
    boost::multi_array<int,2> backing;
    std::string path_to_json;
    std::string levelname;//do we check this? or just add it as last name +1?

};

#endif // MODEL_H
