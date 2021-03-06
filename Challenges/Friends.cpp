/*
    ID: 10608
*/

#include <iostream>
#include <vector>

class UF {
    std::vector<int> id;
    std::vector<int> sz;
    public:
        UF(int n) {
            for(int i = 0; i < n + 1; i++) 
            {
                id.push_back(i);
                sz.push_back(1);
            }
        };
    bool connected(int p, int q) {return find(p) == find(q);};
    int find(int p);
    void onion(int p, int q);
    int compSize(int p) {return sz[find(p)];};
};

int UF::find(int p)
{
    int root = p;
    while(root != id[root]) root = id[root];
    while(p != root) 
    {
      int next = id[p];
      id[p] = root;
      p = next;
    }
    return p;
}

void UF::onion(int p, int q)
{
    int pRoot = find(p);
    int qRoot = find(q);
    if(pRoot == qRoot) return;
    if (sz[pRoot] < sz[qRoot]) 
    {
      sz[qRoot] += sz[pRoot];
      id[pRoot] = qRoot;
    } 
    else 
    {
      sz[pRoot] += sz[qRoot];
      id[qRoot] = pRoot;
    }
}

int main()
{
    int cases, citizens, pairs, friend1, friend2, max;
    std::cin >> cases;
    while(cases--)
    {
        max = 0;
        std::cin >> citizens >> pairs;          //Read boundaries for input
        UF uf(citizens);                        //New union-find obj with citizens = n
        for(int i = 0; i < pairs; i++) 
        {
            std::cin >> friend1 >> friend2;     //read a pair
            if(uf.connected(friend1, friend2)) continue; //If they are already connected we can skip the pair
            uf.onion(friend1, friend2);         //Merge the pair
            int size = uf.compSize(friend1);    //Check if the new component is the biggest
            if(size > max) max = size;
            size = uf.compSize(friend2);        //Check for both numbers, maybe unnessecary
            if(size > max) max = size;
        }
        std::cout << max << "\n";
    }
    return 0;
}