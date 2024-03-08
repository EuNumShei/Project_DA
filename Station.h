//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_STATION_H
#define PROJECT1DATASETSMALL_STATION_H
#include <string>
using namespace std;


class Station {
public:
    Station(int id, string code, char type){
        this->id = id;
        this->code = code;
        this->type = type;
    }

    string get_code() {return code;}
    int get_id() {return id;}
    char get_type() {return type;}

    bool operator==(const Station& outro) const{
        return id == outro.id;
    }
protected:
    int id;
    string code;
    char type;
};


#endif //PROJECT1DATASETSMALL_STATION_H
