#include "gap_buffer.h"
#include <stdlib.h>     /* realloc, free, exit, NULL */
#include <stdio.h>
#include <string.h>

gap_buffer::gap_buffer(int size) : _gap_size(size)
{
    if(_buffer){
        free(_buffer);
    }

    _buffer = (char*) malloc(size);

    if(!_buffer){
        return;
    }

    _point = _buffer;
    _gap_start = _buffer;
    _gap_end = _buffer + size;
    _buffer_end = _gap_end;


}

gap_buffer::gap_buffer(const gap_buffer& gb){

    _gap_size = gb._gap_size;

    _buffer = (char*) malloc(gb._buffer_end - gb._buffer);
    strcpy(_buffer, gb._buffer);

    _buffer_end = _buffer +(gb._buffer_end - gb._buffer);
    _gap_start = _buffer +(gb._gap_start - gb._buffer);
    _gap_end = _gap_start + (gb._gap_end - gb._gap_start);
    _point = _buffer + (gb._point - gb._buffer);
}

gap_buffer::~gap_buffer(){
    if (_buffer) free(_buffer);
}

int gap_buffer::buffer_size(){
    return (_buffer_end - _buffer) - (_gap_end - _gap_start);
}

void gap_buffer::move_gap_to_point(){

    if(_point == _gap_start){
        return;
    }

    if(_point == _gap_end){
        _point = _gap_start;
        return;
    }

    if(_point < _gap_start){
        copy_bytes(_point + (_gap_end-_gap_start), _point, _gap_start - _point);
        _gap_end -= (_gap_start - _point);
        _gap_start = _point;
    }else{

        copy_bytes(_gap_start, _gap_end, _point - _gap_end);
        _gap_start += _point - _gap_end;
        _gap_end = _point;
        _point = _gap_start;
    }

}

int gap_buffer::copy_bytes(char* dest, char* source, unsigned int len){

    if(dest == source || len == 0){
        return  1;
    }

    if(source > dest){
        if((source + len ) >= _buffer_end){
            return 0;
        }

        for(; len > 0; len--){
            *(dest++)= *(source++);
        }
    }else{
         source += len;
         dest += len;

         for(; len > 0; len--){
             *(--dest) = *(--source);
         }
    }

    return 1;
}

void gap_buffer::set_point(int offset){

    _point = _buffer+offset;
    if(_point > _gap_start){
        _point +=_gap_end - _gap_start;
    }
}

int gap_buffer::gap_size(){

    return _gap_end - _gap_start;
}

int gap_buffer::point_offset(){

    if(_point > _gap_end){
        return ((_point - _buffer) - (_gap_end - _gap_start));
    }else{
        return _point - _buffer;
    }
}

char gap_buffer::get_char(){

    if(_point == _gap_start){
        _point = _gap_end;
    }
    return *_point;
}

char gap_buffer::previous_char(){

    if(_point == _gap_end){
        _point = _gap_start;
    }

    return *(--_point);
}

void gap_buffer::replace_char(char c){

    if(_point == _gap_start) _point = _gap_end;

    if(_point == _buffer_end){

        expand_buffer(1);
        _buffer_end++;
    }

    *_point = c;
}

char gap_buffer::next_char(){

    if(_point == _gap_start){
        _point = _gap_end;
        return *_point;
    }

    return *(++_point);
}

void gap_buffer::put_char(char c){

    insert_char(c);
    *_point++;
}

void gap_buffer::insert_char(char c){

    if(_point != _gap_start){
        move_gap_to_point();
    }

    if(_gap_start == _gap_end){
        expand_gap(1);
    }

    *(_gap_start++) = c;
}

void gap_buffer::remove_chars(int size){

    if(_point != _gap_start){
        move_gap_to_point();
    }

    _gap_end += size;
}

void gap_buffer::insert_string(char* string, int size){

    move_gap_to_point();
    if(size > _gap_size){
        expand_gap(size);
    }

    do{
        put_char(*(string++));
    }while(size--);
}

void gap_buffer::expand_buffer(unsigned int size){

    if(((_buffer_end-_buffer)+size) > buffer_size()){

        char* original_buffer = _buffer;
        int new_size = (_buffer_end - _buffer) + size + gap_size();

        _buffer = (char*) realloc(_buffer, new_size);

        _point += _buffer - original_buffer;
        _buffer_end += _buffer - original_buffer;
        _gap_start += _buffer - original_buffer;
        _gap_end += _buffer - original_buffer;
    }
}

void gap_buffer::expand_gap(unsigned int size){

    if(size > _gap_size){
        size += _gap_size;
        expand_buffer(size);
        copy_bytes(_gap_end+size, _gap_end, _buffer_end - _gap_end);
        _gap_end += size;
        _buffer_end += size;
    }
}
