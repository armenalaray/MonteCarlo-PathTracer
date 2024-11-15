/* date = November 12th 2024 6:13 pm */

#ifndef ONB_H
#define ONB_H

class onb
{
    public:
    onb(const vec3 & n)
    {
        Z = MakeUnitVector(n);
        vec3 A = (fabs(Z.x) > 0.9)? vec3(0,1,0) : vec3(1,0,0);
        
        Y = Cross(Z,A);
        
        X = Cross(Z,Y);
        
    }
    
    vec3 Transform(const vec3 & v) const
    {
        return X * v.x + Y * v.y + Z * v.z;
    }
    
    vec3 X;
    vec3 Y;
    vec3 Z;
};

#endif //ONB_H
