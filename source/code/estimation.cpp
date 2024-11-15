#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

void monte_carlo_1()
{
    cout << fixed << setprecision(12);
    
    int inside_circle = 0;
    int N = 100000;
    
    uniform_real_distribution<double> unif(-1, 1);
    
    default_random_engine re;
    
    
    for(int i = 0; i < N; i++)
    {
        /*
This is a square
-1 a 1

2 * 2

Area = 4

pi*r2

area circle = pi

*/
        
        double x = unif(re);
        double y = unif(re);
        
        if(x*x + y*y < 1)
            inside_circle++;
    }
    
    double pi = (4.0 * inside_circle) / N;
    cout << "Regular: " << pi << endl;
}

void monte_carlo_stratified()
{
    cout << fixed << setprecision(12);
    
    int inside_circle = 0;
    int sqrt_N = 10000;
    
    uniform_real_distribution<double> unif(0, 1);
    
    default_random_engine re;
    
    
    for(int i = 0; i < sqrt_N; i++)
    {
        for(int j = 0; j < sqrt_N; j++)
        {
            double x = 2*((i + unif(re)) / sqrt_N) - 1;
            double y = 2*((j + unif(re)) / sqrt_N) - 1;
            
            if(x*x + y*y < 1)
                inside_circle++;
        }
    }
    
    /*
N son el total de samples que tomaste y inside circle 
si es diferente

el pdf es el mismo

es uniforme y es uniforme

Es porque es uniforme, osea tu sampleado te deja hacer eso
Hacer esa asumsión!, esta bien!

Siempre y cuando respetes el pdf esta bien!
y cubras todo el espacio de sampleado!

*/
    double pi = (4.0 * inside_circle) / (sqrt_N*sqrt_N);
    cout << "Stratified: " << pi << endl;
}

void uniform_dist()
{
    /*
Es uniforme de 0-2
*/
    int a = 0;
    int b = 2;
    
    uniform_real_distribution<double> unif(a, b);
    
    default_random_engine re;
    
    double sum = 0.0;
    
    int N = 100000;
    
    for (int i = 0; i < N; ++i)
    {
        
        double x = unif(re);
        sum += x*x;
        
    }
    
    cout << fixed << setprecision(12);
    
    double expected_value = sum / N;
    
    
    cout << "I = " << (b-a)*(expected_value) << endl;
    
    /*
They are estimates:
ray_color

The probability of getting a number near zero

1
si siempre pasa ese no pueded pasar otro!

Monte Carlo es sacar el area del cuadrado!
*/
}

class mc_xsquared_constant
{
    private:
    double icd(double prob)
    {
        double sample = 2 * prob;
        return sample;
    }
    
    double pdf(double sample)
    {
        double prob = 0.5;
        return prob;
    }
    
    public:
    void calc_xsquared()
    {
        int a = 0;
        int b = 1;
        
        uniform_real_distribution<double> unif(a, b);
        
        default_random_engine re;
        
        double sum_area = 0.0;
        /*
    En este caso no funciona porque es uniforme!
    It will converge faster!
    Importance sampling!
    */
        int N = 100000;
        
        for (int i = 0; i < N; ++i)
        {
            /*0-2*/
            double x = icd(unif(re));
            /*
    Esto lo convierte a area!
    Estimación de area!
    */
            sum_area += x*x / pdf(x);
            
        }
        
        cout << fixed << setprecision(12);
        
        double expected_area = sum_area / N;
        
        
        cout << "I = " << (expected_area) << endl;
        
    }
};


class mc_xsquared_linear
{
    private:
    double icd(double prob)
    {
        double sample = std::sqrt(4 * prob);
        return sample;
    }
    
    double pdf(double sample)
    {
        double prob = 0.5 * sample;
        return prob;
    }
    
    public:
    void calc_xsquared()
    {
        int a = 0;
        int b = 1;
        
        uniform_real_distribution<double> unif(a, b);
        
        default_random_engine re;
        
        double sum_area = 0.0;
        /*
    En este caso no funciona porque es uniforme!
    It will converge faster!
    Importance sampling!
    */
        int N = 100000;
        
        for (int i = 0; i < N; ++i)
        {
            /*0-2*/
            double x = icd(unif(re));
            /*
    Esto lo convierte a area!
    Estimación de area!
    */
            sum_area += x*x / pdf(x);
            
        }
        
        cout << fixed << setprecision(12);
        
        double expected_area = sum_area / N;
        
        
        cout << "I = " << (expected_area) << endl;
        
    }
};


class mc_xsquared_quadratic
{
    private:
    double icd(double prob)
    {
        double sample = std::pow(8.0 * prob, 1.0/3.0);
        return sample;
    }
    
    double pdf(double sample)
    {
        double prob = (3.0/8.0) * (sample * sample);
        return prob;
    }
    
    public:
    void calc_xsquared()
    {
        int a = 0;
        int b = 1;
        
        uniform_real_distribution<double> unif(a, b);
        
        default_random_engine re;
        
        double sum_area = 0.0;
        /*
    En este caso no funciona porque es uniforme!
    It will converge faster!
    Importance sampling!
    */
        int N = 1;
        
        for (int i = 0; i < N; ++i)
        {
            /*0-2*/
            double x = icd(unif(re));
            /*
    Esto lo convierte a area!
    Estimación de area!
    */
            sum_area += x*x / pdf(x);
            
        }
        
        cout << fixed << setprecision(12);
        
        double expected_area = sum_area / N;
        
        
        cout << "I = " << (expected_area) << endl;
        
    }
};



int main()
{
    //monte_carlo_1();
    //monte_carlo_stratified();
    
    //uniform_dist();
    
    //son probabilidades!
    
    //mc_xsquared_constant x;
    //x.calc_xsquared();
    
    //mc_xsquared_linear x;
    //x.calc_xsquared();
    
    mc_xsquared_quadratic x;
    x.calc_xsquared();
    
    
    
}