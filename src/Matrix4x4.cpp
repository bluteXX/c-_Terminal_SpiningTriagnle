#include "Matrix4x4.h"

Matrix4x4 Multiply(const Matrix4x4 &a, const Matrix4x4 &b) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Matrix4x4 PerspectiveMatrix(float l, float r, float b, float t, float n, float f) {
    Matrix4x4 mat{};

    mat.m[0][0] = 2 * n / (r - l);
    mat.m[0][1] = 0;
    mat.m[0][2] = (r + l) / (r - l);
    mat.m[0][3] = 0;

    mat.m[1][0] = 0;
    mat.m[1][1] = 2 * n / (t - b);
    mat.m[1][2] = (t + b) / (t - b);
    mat.m[1][3] = 0;

    mat.m[2][0] = 0;
    mat.m[2][1] = 0;
    mat.m[2][2] = (f + n) / (f - n);      // znak zmieniony z minus na plus
    mat.m[2][3] = -(2 * f * n) / (f - n); // zostaje minus

    mat.m[3][0] = 0;
    mat.m[3][1] = 0;
    mat.m[3][2] = 1;  // odwrócone z -1
    mat.m[3][3] = 0;

    return mat;
}

Matrix4x4 RotateYMatrixCenter(float angleRad, Punkt center) {
            // Translacja do środka obiektu (przesunięcie ujemne)
            Matrix4x4 T1{};
            T1.m[0][0] = 1; T1.m[1][1] = 1; T1.m[2][2] = 1; T1.m[3][3] = 1;
            T1.m[0][3] = -center.x;
            T1.m[1][3] = -center.y;
            T1.m[2][3] = -center.z;

            // Rotacja wokół osi Y
            Matrix4x4 R{};
            float c = cos(angleRad);
            float s = sin(angleRad);
            R.m[0][0] = c;  R.m[0][1] = 0; R.m[0][2] = s; R.m[0][3] = 0;
            R.m[1][0] = 0;  R.m[1][1] = 1; R.m[1][2] = 0; R.m[1][3] = 0;
            R.m[2][0] = -s; R.m[2][1] = 0; R.m[2][2] = c; R.m[2][3] = 0;
            R.m[3][0] = 0;  R.m[3][1] = 0; R.m[3][2] = 0; R.m[3][3] = 1;

            // Translacja z powrotem
            Matrix4x4 T2{};
            T2.m[0][0] = 1; T2.m[1][1] = 1; T2.m[2][2] = 1; T2.m[3][3] = 1;
            T2.m[0][3] = center.x;
            T2.m[1][3] = center.y;
            T2.m[2][3] = center.z;

            // Łączna macierz: T2 * R * T1
            return Multiply(Multiply(T2, R), T1);
}

Matrix4x4 TranslationMatrix(float tx, float ty, float tz)
{
    Matrix4x4 mat{};

    // zerujemy wszystkie elementy
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            mat.m[i][j] = 0.0f;

    // jedynki na diagonali
    mat.m[0][0] = 1.0f;
    mat.m[1][1] = 1.0f;
    mat.m[2][2] = 1.0f;
    mat.m[3][3] = 1.0f;

    // translacja w ostatniej kolumnie
    mat.m[0][3] = tx;
    mat.m[1][3] = ty;
    mat.m[2][3] = tz;

    return mat;
}

Punkt MultiplyXvector(const Matrix4x4& mat, const Punkt p) {


    Punkt out;
    out.x = mat.m[0][0]*p.x + mat.m[0][1]*p.y + mat.m[0][2]*p.z + mat.m[0][3];
    out.y = mat.m[1][0]*p.x + mat.m[1][1]*p.y + mat.m[1][2]*p.z + mat.m[1][3];
    out.z = mat.m[2][0]*p.x + mat.m[2][1]*p.y + mat.m[2][2]*p.z + mat.m[2][3];
    out.w = mat.m[3][0]*p.x + mat.m[3][1]*p.y + mat.m[3][2]*p.z + mat.m[3][3];
    return out;
}


Punkt SetOFTransformation(Matrix4x4 MatrixTab[],int NumberOfTransformation,Punkt p)
{
    Punkt OUT=p;
    for ( int i=0; i<NumberOfTransformation; i++)
    {
        
        OUT=MultiplyXvector(MatrixTab[i],OUT);
    }

    return OUT;
    
}
