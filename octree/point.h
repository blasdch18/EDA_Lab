#ifndef POINT_H
#define POINT_H

class point
{
public:
    float x, y, z;
    point()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    point(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    point(float a,float b){
            x=a;
            y=b;
            z=0.0;
        }
};

#endif // POINT_H
