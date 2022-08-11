#pragma once
#include <vector>
using std::vector;

class Grafo
{
    public:
    typedef size_t vertice;
    explicit Grafo(size_t n):ady(n,vector<bool>(n,false)){}
    size_t numVert() const {return ady.size();}

    const vector<bool>& operator[](vertice v) const {return ady[v];}
    vector<bool>& operator[](vertice v) {return ady[v];}

    private:
    vector<vector<bool>> ady;
};