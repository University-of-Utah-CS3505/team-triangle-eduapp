#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H


class gap_buffer
{
public:

    static const int _default_gap = 20;

    gap_buffer(int = _default_gap);
    gap_buffer(const gap_buffer& gb);
    ~gap_buffer();
    int buffer_size();
    void move_gap_to_point();
    void set_point(int);
    int  gap_size();
    int point_offset();
    char get_char();
    char previous_char();
    void replace_char(char);
    char next_char();
    void put_char(char);
    void insert_char(char);
    void remove_chars(int);
    void insert_string(char*, int);


private:
    char* _point;
    char* _buffer;
    char* _buffer_end;
    char* _gap_start;
    char* _gap_end;

    unsigned int _gap_size;

    void expand_buffer(unsigned int);
    void expand_gap(unsigned int);
    int copy_bytes(char*, char*, unsigned int);
};

#endif // GAP_BUFFER_H
