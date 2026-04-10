#include "Triangle.h"
#include "Ekran.h"
#include "WorldToScreen.h"
void Trojkat::ustaw(float x1, float y1, float z1,float x2, float y2, float z2,float x3, float y3, float z3) {
a[0] = {x1, y1, z1};
a[1] = {x2, y2, z2};
a[2] = {x3, y3, z3};
}

std::ostream& operator<<(std::ostream& os, const Trojkat& t) {
    for (int i = 0; i < 3; i++)
        os << "Punkt " << i << ": (" << t.a[i].x << ", " << t.a[i].y << ")\n";
    return os;
}

void ConnectTriangle(const Trojkat& t, Ekran& ekran) {
    // Zakładamy, że 't' zawiera już punkty w Clip Space (po mnożeniu macierzy)
    DrawLine3D(t.a[0], t.a[1], ekran);
    DrawLine3D(t.a[1], t.a[2], ekran);
    DrawLine3D(t.a[2], t.a[0], ekran);
}
void Trojkat::Trainglepushback(float zmiana)
{
    for (int i = 0; i < 3; i++)
    {
        a[i].z-=zmiana;
    }
    


}
void TransformByMatrixes(Trojkat& t,Matrix4x4 tab[],int NumberOfTransformation)
{

for (int i = 0; i < 3; i++)
{
    t.a[i]= SetOFTransformation(tab,NumberOfTransformation,t.a[i]);
    
}


}
