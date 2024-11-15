/* date = November 12th 2024 8:34 pm */

#ifndef PDF_H
#define PDF_H

class pdf
{
    public:
    virtual float value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};

class cosine_pdf : public pdf 
{
    public:
    cosine_pdf(const vec3& w) :
    Basis(w)
    {
    }
    
    virtual float value(const vec3& direction) const
    {
        float cosine = Dot(Basis.Z, MakeUnitVector(direction));
        if(cosine < 0) cosine = 0;
        return cosine / M_PI;
    }
    
    virtual vec3 generate() const
    {
        return Basis.Transform(random_cosine_direction());
    }
    
    
    private:
    onb Basis;
};


class hitable_pdf : public pdf
{
    public:
    hitable_pdf(hitable *  p, const vec3 & origin) : ptr(p), o(origin) {}
    
    virtual float value(const vec3& direction) const
    {
        
        return ptr->pdf_value(o, direction);
    }
    
    virtual vec3 generate() const
    {
        return ptr->random(o);
    }
    
    vec3 o;
    hitable * ptr;
};


class mixture_pdf : public pdf
{
    public:
    mixture_pdf(shared_ptr<pdf> other1, shared_ptr<pdf> other2) : p1(other1), 
    p2(other2)
    {}
    
    virtual float value(const vec3& direction) const
    {
        return 0.5f * p1->value(direction) + 0.5f * p2->value(direction);
    }
    
    virtual vec3 generate() const
    {
        if(RandNum0ToLessThan1() < 0.5)
        {
            return p1->generate();
        }
        else
        {
            return p2->generate();
        }
    }
    
    shared_ptr<pdf> p1;
    shared_ptr<pdf> p2;
};

#endif //PDF_H
