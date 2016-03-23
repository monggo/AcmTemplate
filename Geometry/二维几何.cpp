#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double PI = acos(-1.0);
struct Point{
    double x, y;
    Point (double x = 0, double y = 0) : x(x), y(y) { }
    bool operator < (const Point& b) const {
        return x==b.x ? y<b.y : x<b.x;
    }
};
typedef Point Vector;
// 向量+向量=向量，点+向量=点
Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
// 点-点=向量
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x, A.y-B.y); }

// 向量*数=向量
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
// 向量/数=向量
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    else return x<0 ? -1 : 1;
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
// 点积
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
// 长度
double Length(Vector A) { return sqrt(Dot(A, A)); }
// 夹角
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
// 叉积
double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }
// 向量旋转，rad是弧度
Vector Rotate(Vector A, double rad) {
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
// 计算单位法线，确保A不是零向量
Vector Normal(Vector A) {
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
// 两直线交点，确保Cross(v,w)非0
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P-Q;
    double t = Cross(w, u)/Cross(v, w);
    return P+v*t;
}
// 点P到直线AB的距离
double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2))/Length(v1); // 如果不取绝对值，得到的就是有向距离
}
// 点到线段的距离
double DistanceToSegment(Point P, Point A, Point B) {
    if (A == B) return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2))/Length(v1);
}
// 点在直线上的投影
Point GetLineProjection(Point P, Point A, Point B) {
    Vector v = B-A;
    return A+v*(Dot(v, P-A)/Dot(v, v));
}
// 线段相交判定（不含端点）
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
           c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
// 点在线段上判定（不含端点）
bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1-p, a2-p))==0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
// 多边形的有向面积
double PolygonArea(Point *p, int n) {
    double area = 0;
    for (int i = 1; i < n-1; i++)
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}
// 角度换成弧度
double torad(double deg) {
    return deg/180*acos(-1.0);
}
// 凸包
int ConvexHull(Point* p, int n, Point* ch) {
    sort(p, p+n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for (int i = n-2; i >= 0; i--) {
        while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    return m;
}

int dist2(Point A, Point B) {
    return (int)((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
// 旋转卡壳求凸包的直径
int rotatingCalipers(Point* ch, int n)
{
    int q = 1, ans = 0;
    ch[n] = ch[0];
    for (int p = 0; p < n; p++) {
        while(Cross(ch[q+1]-ch[p+1], ch[p]-ch[p+1]) > Cross(ch[q]-ch[p+1], ch[p]-ch[p+1]))
            q = (q+1)%n;
        ans = max(ans, max(dist2(ch[p], ch[q]), dist2(ch[p+1], ch[q+1])));
    }
    return ans;
}
// 直线
struct Line{
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(Point p, Vector v) : p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const Line& L) const {
        return ang < L.ang;
    }
    Point point(double t) {
        return p+v*t;
    }
};
// 点p在有向直线的左边，线上不算
 bool OnLeft(Line L, Point p) {
    return Cross(L.v, p-L.p) > 0;
 }
// 二直线相交。假定交点唯一存在
Point GetIntersection(Line a, Line b) {
    Vector u = a.p-b.p;
    double t = Cross(b.v, u)/Cross(a.v, b.v);
    return a.p+a.v*t;
}
// 半平面交
int HalfplaneIntersection(Line* L, int n, Point* poly) {
    sort(L, L+n);  // 按极角排序
    int first, last;  // 双端队列的第一个元素和最后一个元素
    Point *p = new Point[n];  // p[i]为q[i]和q[i+1]的交点
    Line *q = new Line[n];  // 双端队列
    q[first=last=0] = L[0];  // 双端队列初始化只有一个半平面L[0]
    for (int i = 1; i < n; i++) {
        while (first < last && !OnLeft(L[i], p[last-1])) last--;
        while (first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last-1].v)) < eps) {
            // 两直线平行且同向，取内侧的一个
            last--;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last-1] = GetIntersection(q[last-1], q[last]);
    }
    while (first < last && !OnLeft(q[first], p[last-1])) last--;
    // 删除无用平面（*）
    if (last-first <= 1) return 0; // 空集（**）
    p[last] = GetIntersection(q[last], q[first]); // 计算首尾两个半平面的交点
    // 从deque复制到输出中
    int m = 0;
    for (int i = first; i <= last; i++) poly[m++] = p[i];
    return m;
}



// 圆
struct Circle {
    Point c;
    double r;
Circle(Point c, double r):c(c), r(r) {}
// 通过圆心角求对应圆上的坐标
    Point point(double a) {
        return Point(c.x+cos(a)*r, c.y+sin(a)*r);
    }
};
// 直线和圆的交点
int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol) {
    double a = L.v.x, b = L.p.x-C.c.x, c = L.v.y, d = L.p.y-C.c.y;
    double e = a*a+c*c, f = 2*(a*b+c*d), g = b*b+d*d-C.r*C.r;
    double delta = f*f-4*e*g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f/(2*e);
        sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f-sqrt(delta))/(2*e);
    t2 = (-f+sqrt(delta))/(2*e);
    sol.push_back(L.point(t1));
    sol.push_back(L.point(t2));
}
// 计算向量极角
double angle(Vector v) { return atan2(v.x, v.y); }
// 两圆相交
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
    double d = Length(C1.c - C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r-C2.r) == 0) return -1;
        return 0;
    }
    if (dcmp(C1.r+C2.r-d) < 0) return 0;
    if (dcmp(fabs(C1.r-C2.r)-d) > 0) return 0;
    double a = angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
    Point p1 = C1.point(a-da), p2 = C1.point(a+da);
    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}
// 过p到圆的切线
int getTangents(Point p, Circle C, Vector* v) {
    Vector u = C.c-p;
    double dist = Length(u);
    if (dist < C.r) return 0;
    else if (dcmp(dist-C.r) == 0) {
        v[0] = Rotate(u, PI/2);
        return 1;
    } else {
        double ang = asin(C.r/dist);
        v[0] = Rotate(u, -ang);
        v[1] = Rotate(u, ang);
        return 2;
    }
}
// 两圆的公切线。返回切线的条数，-1表示无穷条切线
// a[i]和b[i]分别是第i条切线在圆A和圆B上的切点
int getTangents(Circle A, Circle B, Point* a, Point* b) {
    int cnt = 0;
    if (A.r < B.r) { swap(A, B); swap(a, b); }
    int d2 = (A.c.x-B.c.x)*(A.c.x-B.c.x)+(A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff = A.r-B.r;
    int rsum = A.r+B.r;
    if (d2 < rdiff*rdiff) return 0;
    double base = atan2(B.c.y-A.c.y, B.c.x-A.c.x);
    if (d2 == 0 && A.r == B.r) return -1;
    if (d2 == rdiff*rdiff) {
        a[cnt] = A.point(base); b[cnt] = B.point(base); cnt++;
        return 1;
    }
    double ang = acos((A.r-B.r)/sqrt(d2));
    a[cnt] = A.point(base+ang); b[cnt] = B.point(base+ang); cnt++;
    a[cnt] = A.point(base-ang); b[cnt] = B.point(base-ang); cnt++;
    if (d2 == rsum*rsum) {
        a[cnt] = A.point(base); b[cnt] = B.point(PI+base); cnt++;
    }
    else if (d2 > rsum*rsum) {
        double ang = acos((A.r+B.r)/sqrt(d2));
        a[cnt] = A.point(base+ang); b[cnt] = B.point(PI+base+ang); cnt++;
        a[cnt] = A.point(base-ang); b[cnt] = B.point(PI+base-ang); cnt++;
    }
    return cnt;
}
// 三角形的外接圆
Circle CircumscribedCircle(Point p1, Point p2, Point p3) {
    double Bx = p2.x-p1.x, By = p2.y-p1.y;
    double Cx = p3.x-p1.x, Cy = p2.y-p1.y;
    double D = 2*(Bx*Cy-By*Cx);
    double cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D+p1.x;
    double cy = (Bx*(Cx*Cx+Cy*Cy)-Cy*(Bx*Bx+By*By))/D+p1.y;
    Point p = Point(cx, cy);
    return Circle(p, Length(p1-p));
}
// 三角形的内切圆
Circle InscricedCircle(Point p1, Point p2, Point p3) {
    double a = Length(p2-p3);
    double b = Length(p3-p1);
    double c = Length(p1-p2);
    Point p = (p1*a+p2*b+p3*c)/(a+b+c);
    return Circle(p, DistanceToLine(p, p1, p2));
}
