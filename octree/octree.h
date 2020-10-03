#ifndef OCTREE_H
#define OCTREE_H

#include "point.h"
#include <vector>
#include <iostream>
#include <QtDebug>

using namespace std;

#define Top_L_Front 0
#define Top_R_Front 1
#define Bottom_R_Front 2
#define Bottom_L_Front 3
#define Top_L_Bottom 4
#define Top_R_Bottom 5
#define Bottom_R_Back 6
#define Bottom_L_Back 7


class octree
{
public:
    point* punto;
    point *TopLeftFront, *BottomRightBack;
    vector<octree*> children;
    point min,max;

    octree()
    {
        punto = new point();
        min=point(-1,-1,-1);
        max=point(1,1,1);
    }
    octree(point a, point b){
            max = a;
            min = b;

        }
    octree(float x, float y, float z)
    {
        punto = new point(x, y, z);
    }
    octree(float x1, float y1, float z1, float x2, float y2, float z2)
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
        for( int i = Top_L_Front; i <= Bottom_L_Back; ++i)
        {
            children[i] = new octree();
        }
    }
    bool find(float x, float y, float z)
    {
        if(x < TopLeftFront->x || x > BottomRightBack->x ||
           y < TopLeftFront->y || y > BottomRightBack->y ||
           z < TopLeftFront->z || z > BottomRightBack->z)
            return 0;

        float midx = (TopLeftFront->x + BottomRightBack->x) /2;
        float midy = (TopLeftFront->y + BottomRightBack->y) /2;
        float midz = (TopLeftFront->z + BottomRightBack->z) /2;

        float pos = -1;
        if(x <= midx)
        {
            if(y <= midy)
            {
                if(z <= midz)
                {
                    pos = Top_L_Front;
                }
                else
                {
                    pos = Top_L_Bottom;
                }
            }
            else
            {
                if(z <= midz)
                {
                    pos = Bottom_L_Front;
                }
                else
                {
                    pos = Bottom_L_Back;
                }
            }
        }
        else
        {
            if(y <= midy)
            {
                if(z <= midz)
                {
                    pos = Top_R_Front;
                }
                else
                {
                    pos = Top_R_Bottom;
                }
            }
            else
            {
                if(z <= midz)
                {
                    pos = Bottom_R_Front;
                }
                else
                {
                    pos = Bottom_R_Back;
                }
            }
        }
        if(children[pos]->punto == nullptr)
        {// si es nodo de la region
            return children[pos]->find(x, y, z);
        }
        else if(children[pos]->punto->x == -1)
        {// si es un nodo vacio
            return 0;
        }
        else
        {
            if(x == children[pos]->punto->x && y == children[pos]->punto->y
                && z == children[pos]->punto->z)
                return 1;
        }
        return 0;
    }

    void insert ( float x, float y, float z)
    {
        if(x < TopLeftFront->x || x > BottomRightBack->x ||
           y < TopLeftFront->y || y > BottomRightBack->y ||
           z < TopLeftFront->z || z > BottomRightBack->z)
           return;

        float midx = (TopLeftFront->x + BottomRightBack->x) /2;
        float midy = (TopLeftFront->y + BottomRightBack->y) /2;
        float midz = (TopLeftFront->z + BottomRightBack->z) /2;

        float pos = -1;
        if(x <= midx)
        {
            if(y <= midy)
            {
                if(z <= midz)
                {
                    pos = Top_L_Front;
                }
                else
                {
                    pos = Top_L_Bottom;
                }
            }
            else
            {
                if(z <= midz)
                {
                    pos = Bottom_L_Front;
                }
                else
                {
                    pos = Bottom_L_Back;
                }
            }
        }
        else
        {
            if(y <= midy)
            {
                if(z <= midz)
                {
                    pos = Top_R_Front;
                }
                else
                {
                    pos = Top_R_Bottom;
                }
            }
            else
            {
                if(z <= midz)
                {
                    pos = Bottom_R_Front;
                }
                else
                {
                    pos = Bottom_R_Back;
                }
            }
        }

        if(children[pos]-> punto == nullptr)
        {// si es nodo de la region
            children[pos]->insert(x, y, z);
            return;
        }
        else if(children[pos]->punto->x == -1)
        {// si es un nodo vacio
            // if empty node
            delete children[pos];
            children[pos] = new octree(x, y, z);
            return;
        }
        else
        {
            float x_ = children[pos]->punto->x;
            float y_ = children[pos]->punto->y;
            float z_ = children[pos]->punto->z;
            delete children[pos];
            children[pos] = nullptr;

            if(pos == Top_L_Front)
            {
                children[pos] = new octree(TopLeftFront->x, TopLeftFront->y, TopLeftFront->z,
                                        midx, midy, midz);
            }
            else if(pos == Top_R_Front)
            {
                children[pos] = new octree(midx + 1, TopLeftFront->y, TopLeftFront->z,
                                        BottomRightBack->x, midy, midz);
            }
            else if(pos == Bottom_R_Front)
            {
                children[pos] = new octree(midx + 1, midy + 1, TopLeftFront->z,
                                        BottomRightBack->x, BottomRightBack->y, midz);
            }
            else if(pos == Bottom_L_Front)
            {
                children[pos] = new octree(TopLeftFront->x, midy + 1, TopLeftFront->z,
                                        midx, BottomRightBack->y, midz);
            }
            else if(pos == Top_L_Bottom)
            {
                children[pos] = new octree(TopLeftFront->x, TopLeftFront->y, midz + 1,
                                        midx, midy, BottomRightBack->z);
            }
            else if(pos == Top_R_Bottom)
            {
                children[pos] = new octree(midx + 1, TopLeftFront->y, midz + 1,
                                        BottomRightBack->x, midy, BottomRightBack->z);
            }
            else if(pos == Bottom_R_Back)
            {
                children[pos] = new octree(midx + 1, midy + 1, midz + 1,
                                        BottomRightBack->x, BottomRightBack->y, BottomRightBack->z);
            }
            else if(pos == Bottom_L_Back)
            {
                children[pos] = new octree(TopLeftFront->x, midy + 1, midz + 1,
                                        midx, BottomRightBack->y, BottomRightBack->z);
            }
            children[pos]->insert(x_, y_, z_);
            children[pos]->insert(x, y, z);

        }

    }

};


#endif // OCTREE_H
