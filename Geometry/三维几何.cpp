#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
struct Point3{
    double x, y, z;
    Point3(double x=0, double y=0, double z=0):x(x), y(y), z(z) {}
};

typedef Point3 Vector3;

Vector3 operator + (Vector3 A, Vector3 B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (Vector3 A, Vector3 B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector3 operator * (Vector3 A, double p) { return Vector3(A.x*p, A.y*p, A.z*p); }
Vector3 operator / (Vector3 A, double p) { return Vector3(A.x/p, A.y/p, A.z/p); }

int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    else return x<0 ? -1 : 1;
}

bool operator == (const Point3& A, const Point3& B) {
    if (!dcmp(A.x-B.x) && !dcmp(A.y-B.y) && !dcmp(A.z-B.z)) return true;
    return false;
}

double Dot(Vector3 A, Vector3 B) { return A.x*B.x+A.y*B.y+A.z*B.z; }
double Length(Vector3 A) { return sqrt(Dot(A, A)); }
double Angle(Vector3 A, Vector3 B) { return acos(Dot(A, B)/Length(A)/Length(B)); }
Vector3 Cross(Vector3 A, Vector3 B) {
    return Vector3(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
}
double Area2(Point3 A, Point3 B, Point3 C) {
    return Length(Cross(B-A, C-A));
}
// 点p到平面p0-n的距离，n必须为单位向量
double DistanceToPlane(const Point3& p, const Point3& p0, const Vector3 &n) {
    return fabs(Dot(p-p0, n)); // 如果不取绝对值，得到的是有向距离
}
// 点p在平面p0-n上的投影，n必须为单位向量
Point3 GetPlaneProjection(const Point3& p, const Point3& p0, const Vector3& n) {
    return p-n*Dot(p-p0, n);
}
// 直线p1-p2到平面p0-n的交点，假定交点唯一存在
Point3 LinePlaneIntersection(Point3 p1, Point3 p2, Point3 p0, Vector3 n) {
    Vector3 v = p2-p1;
    double t = (Dot(n, p0-p1)/Dot(n, p2-p1));
    return p1+v*t;
}
// 点p在三角形p0p1p2中
bool PointInTri (Point3 p, Point3 p0, Point3 p1, Point3 p2) {
    double area1 = Area2(p, p0, p1);
    double area2 = Area2(p, p1, p2);
    double area3 = Area2(p, p2, p0);
    return dcmp(area1+area2+area3-Area2(p0, p1, p2)) == 0;
}

// 三角形p0p1p2是否与线段AB相交
bool TriSegIntersection(Point3 p0, Point3 p1, Point3 p2, Point3 A, Point3 B, Point3& p) {
    Vector3 n = Cross(p1-p0, p2-p0);
    if (dcmp(Dot(n, B-A)) == 0) return false;
    else {
        double t = Dot(n, p0-A)/Dot(n, B-A);
        if (dcmp(t) < 0 || dcmp(t-1) > 0) return false;
        p = A+(B-A)*t;
        return PointInTri(p, p0, p1, p2);
    }
}

// 点P到直线AB的距离
double DistanceToLine(Point3 P, Point3 A, Point3 B) {
    Vector3 v1 = B-A, v2 = P-A;
    return Length(Cross(v1, v2))/Length(v1);
}
// 点P到线段AB的距离
double DistanceToSegment(Point3 P, Point3 A, Point3 B) {
    if (A == B) return Length(P-A);
    Vector3 v1 = B-A, v2 = P-A, v3 = P-B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return Length(Cross(v1, v2))/Length(v1);
}
// 返回AB，AC，AD的混合积，它也等于四面体ABCD的有向体积的6倍
double Volume6(Point3 A, Point3 B, Point3 C, Point3 D) {
    return Dot(D-A, Cross(B-A, C-A));
}


struct Face{
    int v[3];
    Vector3 normal(Point3* P) const {
        return Cross(P[v[1]]-P[v[0]], P[v[2]]-P[v[0]]);
    }
    int cansee(Point3* P, int i) const {
        return Dot(P[i]-P[0], normal(P))>0 ? 1 : 0;
    }
};
// 增量法求三维凸包。
// 没有考虑各种特殊情况（如4点共面。实践中，请在调用前对输入点进行微小扰动
vector<Face> CH3D(Point3 *P, int n) {
    vector<Face> cur;
    // 由于已经进行扰动，前三个点不共线
    cur.push_back((Face){{0, 1, 2}});
    cur.push_back((Face){{2, 1, 0}});
    for (int i = 3; i < n; i++) {
        vector<Face> next;
        // 计算每条边"左面"的可见性
        for (int j = 0; j < cur.size(); j++) {
            Face& f = cur[j];
            int res = f.cansee(P, i);
            if (!res) next.push_back(f);
            for (int k = 0; k < 3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
        }
        for (int j = 0; j < cur.size(); j++) {
            for (int k = 0; k < 3; k++) {
                int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
                if (vis[a][b] != vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
                    next.push_back((Face){{a, b, i}});
            }
        }
        cur = next;
    }
    return cur;
}

double rand01() { return rand()/(double)RAND_MAX; }
double randeps() { return (rand01()-0.5)*eps; }
Point3 add_noise(Point3 p) {
    return Point3(p.x+randeps(), p.y+randeps(), p.z+randeps());
}

int main() {
    cout<<hello<<endl;

    return 0;
}