//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_STATION_H
#define PROJECT1DATASETSMALL_STATION_H
#include <string>
using namespace std;


class Station {
public:
    Station(int id, string code){
        this->id = id;
        this->code = code;
    }

    string get_code() const {return code;}
    int get_id() const {return id;}

    bool operator==(const Station& outro) const{
        return id == outro.id;
    }
protected:
    int id;
    string code;
};


#endif //PROJECT1DATASETSMALL_STATION_H
