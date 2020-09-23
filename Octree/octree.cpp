#include <iostream>
#include <vector>

using namespace std;

#define Top_L_Front 0
#define Top_R_Front 1
#define Bottom_R_Front 2
#define Bottom_L_Front 3
#define Top_L_Bottom 4
#define Top_R_Bottom 5
#define Bottom_R_Back 6
#define Bottom_L_Back 7

struct point 
{
    int x, y, z;
    point(){
        x = 0;
        y = 0;
        z = 0;
    }
    point(int a, int b, int c){
        x = a;
        y = b; 
        z = c;
    }
};

class octree
{
    point* punto;
    point *TopLeftFront, *BottomRightBack;
    vector<octree*> children;

    public:
    octree()
    {
        punto = new point();
    }
    octree(int x, int y, int z)
    {
        punto = new point(x, y, z);
    }
    octree(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        if(x2 < x1 || y2 < y1 || z2 < z1)
        {
            cout<< "datos no validos"<<endl;
            return;
        }
        punto = nullptr;
        TopLeftFront = new point( x1, y1, z1);
        BottomRightBack = new point ( x2, y2, z2);

        children.assign(8, nullptr);
        for( int i = TopLeftFront; i <= BottomRightBack; ++i)
        {
            children[i] = new octree();
        }
    }




};

int main()
{
    cout<<"HEllo world"<<endl;
}