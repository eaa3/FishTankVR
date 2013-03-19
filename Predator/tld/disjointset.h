#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include <vector>


namespace tld {

using std::vector;

const int NOT_IN_A_SET = -1;

class DisjointSet
{
    public:
        MATHFUNCSDLL_API DisjointSet(int maxSize);
        MATHFUNCSDLL_API virtual ~DisjointSet();


        vector<int> elements, rank;
        int setCount, elemCount;

        MATHFUNCSDLL_API void makeSet(int i);
        MATHFUNCSDLL_API void unionSets(int i, int j);
        MATHFUNCSDLL_API void linkSets(int i, int j);

        MATHFUNCSDLL_API int findSet(int i);


    protected:
    private:
};

}

#endif // DISJOINTSET_H
