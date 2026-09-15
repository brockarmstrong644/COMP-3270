#include <iostream> 

#include <fstream> 

#include <cmath> 

#include <chrono> 

using namespace std; 

double ComputePower(double x, int n) {  

if (n == 0)  

return 1.0;  

if (n == 1)  

return x; 

double pow = ComputePower(x, n / 2); 
 
if ((n & 1) == 0) 
    return pow * pow; 
else 
    return x * pow * pow; 
  

} 

int main() { ofstream f("data.csv"); 

 if (!f.is_open()) {  

cerr << "Failed to open file" << endl; 

 return 1; 

 } 

f << "n,T(n)/g1(n),T(n)/g2(n),T(n)/g3(n)" << endl; 
 
long L = 1000000; 
for (long n = 7500; n <= L; n += 100) { 
    auto start = chrono::high_resolution_clock::now(); 
    ComputePower(0.75, n); 
    auto stop = chrono::high_resolution_clock::now(); 
 
    double T_n = chrono::duration_cast<chrono::nanoseconds>(stop - start).count(); 
 
    double log2_n = log2((double)n); 
    double g1 = 0.5 * n * log2_n; 
    double g2 = 7.0 * log2_n; 
    double g3 = 2.0 * n * n; 
 
    f << n << "," << scientific << T_n / g1 << "," << T_n / g2 << "," << T_n / g3 << endl; 
} 
f.close(); 
cout << "Data collection complete. Saved to data.csv" << endl; 
return 0; 

} 