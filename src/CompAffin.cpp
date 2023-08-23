

#include "CompAffin.h"
#include <thread>
#include <rational.h>
#include <LA.h>
#include <numbers.h>

//--------------------------------------------------------
wxFrame *MyFrame=NULL;
std::string Input_1,Input_2;
int errorcomputed;

#ifdef _WIN32
std::string filesep="\\",filedir=val::CurrentHomeDir(),settingsfile=val::CurrentHomeDir()+"\\AppData\\Local\\MVPrograms\\CompAffin\\settings.txt",
			settingsdir = val::CurrentHomeDir()+"\\AppData\\Local\\MVPrograms\\CompAffin",valdir = val::CurrentHomeDir()+"\\AppData\\Local\\CompAffin",
            iconpath = "C:\\gccprogrammes\\LA\\CompAffin\\icon\\affin.xpm",
            alticonpath = val::GetExeDir() + "\\affin.xpm";
#endif // _WIN32
#ifdef __LINUX__
std::string filesep="/", valdir = val::CurrentHomeDir() + "/.config/MVPrograms", settingsdir = valdir + "/CompAffin",
			settingsfile = settingsdir + "/settings.conf",
			iconpath = val::CurrentHomeDir() + "/.local/share/icons/CompAffin/affin.xpm",
            alticonpath = "/home/miguel/gccprogrammes/LA/CompAffin/icon/affin.xpm";
#endif // __LINUX__
#ifdef __APPLE__
std::string filesep="/", valdir = val::CurrentHomeDir() + "/Library/Application Support",
            settingsdir = valdir + "/CompAffin", settingsfile = settingsdir + "/settings.conf",
            iconpath = val::CurrentHomeDir() + "/.local/share/icons/CompAffin/affin.xpm",
            alticonpath = val::GetExeDir() + "/../Resources/affin.xpm";
#endif // __APPLE__

//--------------------------------------------------------

wxDEFINE_EVENT(MY_EVENT, MyThreadEvent);


val::integer sqrt(const val::integer& n)
{
 using namespace val;
 integer a,a1,c,d,b=n;

 while ((d=(b-a))>1) {
	 a1=a+d/integer(2);
	 c=a1*a1;
	 if (c>n) b=std::move(a1);
	 else a=std::move(a1);
 }
 if ((b*b)>n) return a;
 else return b;
}

// sqrt(r) = c * sqrt(ri)
void rationalizedenominator(const val::rational &r, val::rational &c, val::integer &ri)
{
    val::integer one(1);
    c = val::rational(one,r.denominator());
    ri = r.denominator() * r.nominator();
    val::integer b = sqrt(ri);
    if (ri == one) return;
    if (b*b == ri) {
        ri = one;
        c *= b;
        return;
    }
    if (ri.length() < 2) {
        val::integer q;
        for (val::integer p = 2; p < b; p = val::nextprime(p+one)) {
            q = p*p;
            while (ri % q == 0) {
                ri/=q;
                c*=p;
            }
        }
    }
}


void WriteText(const std::string& s,int O)
{
    if (MyFrame==NULL) return;
    MyThreadEvent event(MY_EVENT,IdOutput);

    event.SetOutput(O);
    event.SetMessage(s);
    MyFrame->GetEventHandler()->QueueEvent(event.Clone());
}


void ButtonEnable()
{
    if (MyFrame==NULL) return;

    MyThreadEvent event(MY_EVENT,IdButtonOK);
    MyFrame->GetEventHandler()->QueueEvent(event.Clone());
}


void Error(const char* c)
{
    if (MyFrame==NULL) exit(-1);
    errorcomputed=0;
    MyThreadEvent event(MY_EVENT,IdError);
    event.SetMessage(std::string(c));
    MyFrame->GetEventHandler()->QueueEvent(event.Clone());
    while (!errorcomputed) std::this_thread::yield();
}

// ------------------------------------------------------------



template <>
void makeprimitiv(val::vector<val::rational> &v)
{
    int n = v.dimension();
    if (n < 2) return;
    val::integer ggt , kgv;

    ggt = v(0).nominator(); kgv = v(0).denominator();
    for (int i = 1; i < n; ++i) {
        ggt = val::gcd(ggt, v(i).nominator());
        kgv = val::lcm(kgv, v(i).denominator());
    }
    v *= val::rational(kgv,ggt);
}



template <>
void makeprimitiv(val::matrix<val::rational> &A, int k)
{
    int n = A.numberofcolumns(), m = A.numberofrows(), i ,j;
    val::integer ggt, kgv;
    val::rational r;

    for (i = k; i < m; ++i) {
        ggt = A(i,0).nominator(); kgv = A(i,0).denominator();
        for (j = 1; j < n; ++j) {
            ggt = val::gcd(ggt,A(i,j).nominator());
            kgv = val::lcm(kgv,A(i,j).denominator());
        }
        r = val::rational(kgv,ggt);
        for (j = 0; j < n; ++j) A(i,j) *= r;
    }
}




// -------------------------------------------------------------

// Rückgabe: 1 falls Eingabetyp vom Typ vector, 2 falls vom Typ Matrix:
int getstringready(std::string &s)
{

    std::string s1="";
    int i,l =s.length(),type=1;

    for (i=0;i<l;i++)
        if (s[i]=='=' || s[i]=='|') {
            type=2;
            break;
        }
    for (i=0;i<l;i++) {
        if (s[i]!='=' && s[i]!='|' && s[i]!='<' && s[i]!='>') s1+=s[i];
    }
    s=std::move(s1);
    return type;

}



void ComputeProjectionMap(const val::affinspace<val::rational> &A, val::matrix<val::rational> &P, int Output)
{
    if (A.globaldim() == 0 || A.globaldim() > 6) return;


    val::matrix<val::rational> I(A.globaldim()), R;
    val::vector<val::rational> b;
    std::string s = "\nOrthogonale Projektion:\n";

    OrthogonalProjektionMap(A,b,P);
    s += val::ToString(b) + "\n\n" + ::ToString(P);

    I.make_identity();
    R = val::rational(2) * P - I;
    b = A.getPoint() - R * A.getPoint();

    s+= "\n\nSpiegelung:\n";
    s += val::ToString(b) + "\n\n" + ::ToString(R);

    WriteText(s,Output);
}




void ComputeProjections(const val::affinspace<val::rational> &A, const val::matrix<val::rational> &P,
                        const val::affinspace<val::rational> &A1, int toA1)
{
    if (A.globaldim() != A1.globaldim() || A.dimension() <= A1.dimension()) return;

    int n = A1.globaldim(), i;
    val::matrix<val::rational> I(n), R;
    val::vector<val::rational> b,c;

    I.make_identity();
    R = val::rational(2) * P - I;
    b = A.getPoint() - P * A.getPoint();
    c = A.getPoint() - R * A.getPoint();

    std::string s;

    if (toA1) s = "\n\nOrthogonale Projektion von A2 in A1:\n";
    else s = "\n\nOrthogonale Projektion von A1 in A2:\n";
    s += val::ToString(b + P * A1.getPoint());
    if (A1.dimension()>0) s+= "\n + < ";
    else s+="\n";
    for (i = 0; i < A1.dimension(); i++) {
        s+=val::ToString(P * A1.getVspace()(i));
        if (i == A1.dimension() - 1) s+=" >\n";
        else s+="\n        ";
    }
    if (toA1) s += "\nSpiegelung von A2 in A1:\n";
    else s += "\nSpiegelung von A1 in A2:\n";
    s += val::ToString(c + R * A1.getPoint());
    if (A1.dimension()>0) s+= "\n + < ";
    else s+="\n";
    for (i = 0; i < A1.dimension(); i++) {
        s+=val::ToString(R * A1.getVspace()(i));
        if (i == A1.dimension() - 1) s+=" >\n";
        else s+="\n        ";
    }
    WriteText(s);
}




/*
template <>
val::rational stringtonumber(const std::string& s)
{
    return val::FromString<val::rational>(s);
}
*/




//--------------------------------------------------------------
/*
void ComputeAffin(const std::string& Input,int Output)
{
    WriteText(Input,Output);
}
*/

void CompAffinMain(std::string& I_1,std::string& I_2)
{

    int intersects;
    val::affinspace<val::rational> A1,A2;
    val::matrix<val::rational> P1,P2;


    std::thread t(ComputeAffin<val::rational>,std::ref(I_2),std::ref(A2),2);
    ComputeAffin(I_1,A1,1);
    t.join();
    if (A1.globaldim() > 0 && A1.globaldim() < 7) ComputeProjectionMap(A1,P1,1);
    if (A2.globaldim() > 0 && A2.globaldim() < 7) ComputeProjectionMap(A2,P2,2);
    intersects=ComputeIntersection(A1,A2);
    if (!intersects && A1.globaldim()>0 && A2.globaldim()>0) {
        val::vector<val::rational> P,Q;
        val::rational squaredist, c;
        val::integer ri;
        std::string s;

        squaredist=A1.squaredistance(A2,P,Q);
        rationalizedenominator(squaredist,c,ri);

        s = val::ToString(c);
        if (ri != val::integer(1)) s += "*sqrt(" + val::ToString(ri) + ") = " + val::ToString(double(c) * val::sqrt(double(ri)));


        WriteText("\n Abstand d(A1,A2) =  " + s + "\n");
        WriteText("\nLotfusspunkt bei A1:\n" + ToString(P) + "\n");
        WriteText("\nLotfusspunkt bei A2:\n" + ToString(Q));
    }
    if (A1.globaldim() == A2.globaldim()) {
        if (A1.dimension() > A2.dimension()) ComputeProjections(A1,P1,A2,1);
        else if (A1.dimension() < A2.dimension()) ComputeProjections(A2,P2,A1,0);
    }
    ButtonEnable();
}
