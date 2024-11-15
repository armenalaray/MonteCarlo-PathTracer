//////////////////////////////////////////////////////
//
//Author: Alejandro Armenta
//Date: 2019
//File: pathtracer_random.h
//Company:
//
//(2018-2019) All rights reserved.
//
//////////////////////////////////////////////////////


#ifndef PATHTRACER_RANDOM_H
#define PATHTRACER_RANDOM_H

void SeedInit()
{
	srand((unsigned)time(NULL));
}

float RandNum0ToLessThan1()
{
	// NOTE(Alex): I want a number from 0 <= rand < 1 
	float Result = (float)rand() / (float)((RAND_MAX) + 1);  
	return Result;	
}

vec3 RUVXY()
{
	vec3 Result = vec3(RandNum0ToLessThan1(), RandNum0ToLessThan1(), 0.0f);
	Result.MakeUnitVector();
	return Result;
}


vec3 RandomInUnitDisc()
{
	vec3 Result(1.0,0,0);
	
	while(Result.SquaredLength() >= 1.0)
		Result = ((2.0f * vec3(RandNum0ToLessThan1(), RandNum0ToLessThan1(), 0.0f)) - vec3(1.0f,1.0f,0.0f));
	
	return Result;
}

vec3 RandomInUnitDiscXY()
{
	vec3 Result(1.0,0,0);
	
	while(Result.SquaredLength() >= 1.0)
		Result = ((2.0f * vec3(RandNum0ToLessThan1(), RandNum0ToLessThan1(), 0.0f)) - vec3(1.0f,1.0f,0.0f));
	Result.MakeUnitVector();
	return Result;
}

vec3 RandomInUnitSphere()
{
	vec3 Result(1.0,0,0);
	
	while(Result.SquaredLength() >= 1.0)
		Result = ((2.0f * vec3(RandNum0ToLessThan1(), RandNum0ToLessThan1(), RandNum0ToLessThan1())) - vec3(1.0f,1.0f,1.0f));
	
	return Result;
}


inline vec3 random_cosine_direction()
{
    
    float r1 = RandNum0ToLessThan1();
    float r2 = RandNum0ToLessThan1();
    
    float phi = 2*M_PI*r1;
    
    float z = std::sqrt(1-r2);
    float x = std::cos(phi)*std::sqrt(r2);
    float y = std::sin(phi)*std::sqrt(r2);
    
    return vec3(x,y,z);
}

inline vec3 random_to_sphere(float Radius, float distance_squared)
{
    float r1 = RandNum0ToLessThan1();
    float r2 = RandNum0ToLessThan1();
    
    float cosThetaMax = std::sqrt(1 - (Radius*Radius/distance_squared));
    
    float z = 1 + r2 * (cosThetaMax - 1);
    float x = std::cos(2*M_PI*r1) * std::sqrt(1 - (z*z));
    float y = std::sin(2*M_PI*r1) * std::sqrt(1 - (z*z));
    
    return vec3(x,y,z);
}



#endif


