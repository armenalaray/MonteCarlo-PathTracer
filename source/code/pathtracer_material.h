//////////////////////////////////////////////////////
//
//Author: Alejandro Armenta
//Date: 2019
//File: pathtracer_material.h
//Company:
//
//(2018-2019) All rights reserved.
//
//////////////////////////////////////////////////////


#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

/*
Porque ese ray 
*/
struct scatter_record
{
    ray specular_ray;
    bool is_specular;
    vec3 attenuation;
    shared_ptr<pdf> pdf_ptr;
};

class material
{
	public:
	virtual bool Scatter(const ray& RayIn, const hit_record& HRec, scatter_record & SRec) const
    {
        return false;
    }
    
    virtual float Scattering_Pdf(const ray& RayIn, const hit_record & Rec, const ray & Scattered) const
    {
        return false;
    }
    
    virtual vec3 Emit(const ray& RayIn, const hit_record& rec, float u, float v, vec3 p) const 
    {
        return vec3(0,0,0);
    }
    
    virtual ~material();
};

material::~material(){}

class isotropic : public material
{
	public:
	shared_ptr<texture> Albedo;
	isotropic(shared_ptr<texture> Albedo_) : Albedo(Albedo_) {};
	virtual bool Scatter(const ray& RayIn, const hit_record& Rec, vec3& Attenuation, ray& Scattered) const
	{
		Scattered = ray(Rec.p, RandomInUnitSphere());
		Attenuation = Albedo->Value(Rec.u, Rec.v, Rec.p);
		return true;
	}
};

class lambertian : public material
{
	public:
	shared_ptr<texture> albedo;
	lambertian(shared_ptr<texture> albedo_) : albedo(albedo_) {}
	~lambertian() {};
    
    virtual bool Scatter(const ray& RayIn, const hit_record& HRec, scatter_record & SRec) const
    {
        SRec.is_specular = false;
        SRec.attenuation = albedo->Value(HRec.u, HRec.v, HRec.p);
        SRec.pdf_ptr = make_shared<cosine_pdf>(HRec.Normal);
        return true;
    }
    
    
    virtual float Scattering_Pdf(const ray& RayIn, const hit_record & Rec, const ray & Scattered) const
    {
        float cosine = Dot(Rec.Normal, MakeUnitVector(Scattered.Direction));
        if(cosine < 0) cosine = 0;
        return cosine / M_PI;
    }
};


class metal : public material
{
	public:
	vec3 albedo;
	float Fuzz;
	
	metal(const vec3& albedo_, const float f ) : albedo(albedo_), Fuzz(f) {}
	~metal(){};
    
    virtual bool Scatter(const ray& RayIn, const hit_record& HRec, scatter_record & SRec) const
    {
		vec3 reflected = Reflect(MakeUnitVector(RayIn.Direction), HRec.Normal); 
        SRec.specular_ray = ray(HRec.p, reflected + Fuzz * RandomInUnitSphere(), RayIn.Time);
		SRec.attenuation = albedo;
		SRec.is_specular = true;
        SRec.pdf_ptr = 0;
		return true;
	}
};

class dielectric : public material
{
	public:
	float ior;
	
	dielectric(const float ior_) : ior(ior_) {}
	~dielectric(){}
    
    virtual bool Scatter(const ray& RayIn, const hit_record& HRec, scatter_record & SRec) const
	{
		
#if 0
		vec3 outward_normal;
		vec3 reflected = Reflect(RayIn.Direction, Rec.Normal);
		
		float ni_over_nt;
		Attenuation = vec3(1.0f,1.0f,1.0f);
		
		vec3 refracted;
		float reflect_prob;
		float cosine;
		
		if(Dot(RayIn.Direction, Rec.Normal) > 0)
		{
			
			outward_normal = -Rec.Normal;
			ni_over_nt = ior;
			cosine = ior * Dot(RayIn.Direction, Rec.Normal) / RayIn.Direction.Length();
		}
		else
		{
			
			outward_normal = Rec.Normal;
			ni_over_nt = 1.0f / ior;
			cosine = -Dot(RayIn.Direction, Rec.Normal) / RayIn.Direction.Length();
		}
		
		if(ShirleysRefract(RayIn.Direction, outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = ShirleysSchlick(cosine, ior);
		}
		else
		{
			Scattered = ray(Rec.p, reflected);
			reflect_prob = 1.0f;
		}
		
		if(RandNum0ToLessThan1() < reflect_prob)
		{
			Scattered = ray(Rec.p, reflected);
		}
		else
		{
			Scattered = ray(Rec.p, refracted);
			
		}
		return true;
#else
        SRec.is_specular = true;
        SRec.pdf_ptr = 0;
		SRec.attenuation = vec3(1.0, 1.0, 1.0);
		
        
        
		vec3 Reflected = Reflect(MakeUnitVector(RayIn.Direction), HRec.Normal); 
        
		float RefProb = Fresnel(RayIn.Direction, HRec.Normal, 1.0f, ior);
		
		vec3 Transmitted;
		if(RefProb < 1.0f)
		{
			Refract(RayIn.Direction, HRec.Normal, 1.0f, ior, Transmitted);
			//RefProb = Schlick(RayIn.Direction, HRec.Normal, 1.0f, ior);
		}
		
		if(RandNum0ToLessThan1() < RefProb)
		{
			SRec.specular_ray = ray(HRec.p, Reflected, RayIn.Time);
		}
		else
		{
			SRec.specular_ray = ray(HRec.p, Transmitted, RayIn.Time);			
		}
        
		return true;
#endif
        
	}
};

class diffuse_light : public material
{
	public:
	shared_ptr<texture> Emitted;
	diffuse_light(shared_ptr<texture> Emitted_) : Emitted(Emitted_){};
	virtual bool Scatter(const ray& RayIn, const hit_record& Rec, vec3& attenuation, ray& Scattered) const 
	{ 
		return false; 
	}
	
	virtual vec3 Emit(const ray& RayIn, const hit_record& rec, float u, float v, vec3 p) const
	{
        if(Dot(rec.Normal, RayIn.Direction))
        {
            return Emitted->Value(u,v,p);
        }
        else
        {
            return vec3(0,0,0);
        }
    }
    
    ~diffuse_light() {};
};


#endif


