#ifndef COMPAFFIN_H_INCLUDED
#define COMPAFFIN_H_INCLUDED

#include <wx/frame.h>
//#include <wx/button.h>
#include <string>
#include <affinspace.h>
#include <val_utils.h>
#include <sstream>
#include <val_filesys.h>


//  -------------------------------------------------------------------------------------

extern wxFrame *MyFrame;
extern std::string Input_1,Input_2,filesep,settingsfile,settingsdir,valdir,iconpath,alticonpath;
extern int errorcomputed;

// --------------------------------------------------------------------------------------

class MyThreadEvent;
wxDECLARE_EVENT(MY_EVENT, MyThreadEvent);


class MyThreadEvent: public wxThreadEvent
{
public:
	MyThreadEvent(wxEventType commandType, int id = 0)
        		:  wxThreadEvent(commandType, id), Output(0) { }

	// You *must* copy here the data to be transported
	MyThreadEvent(const MyThreadEvent& event)
        		:  wxThreadEvent(event) { this->SetMessage(event.GetMessage());this->SetOutput(event.GetOutput()); }

	// Required for sending with wxPostEvent()
	wxEvent* Clone() const { return new MyThreadEvent(*this); }

	//std::string
    wxString GetMessage() const { return message; }
	int GetOutput() const {return Output;}
	//void SetMessage(const std::string &s) {message=s;}
	void SetMessage(const wxString &s) {message=s;}
	void SetOutput(int a) {Output=a;}

private:
	//std::string
    wxString message;
	int Output;
};

enum {IdOutput,IdButtonOK,IdError};

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
void WriteText(const wxString&,int O=0);
void ButtonEnable();
void Error(const char*);
// -------------------------------------------------------------------------------------------


// Rückgabe: 1 falls Eingabetyp vom Typ vector, 2 falls vom Typ Matrix:
int getstringready(std::string &s);

/*
template <class T>
std::string numbertostring(const T& a)
{
    return val::ToString(a);
}

template <class T>
T stringtonumber(const std::string&);


template <class T>
val::matrix<T> stringtomatrix(const std::string&);
*/

template <class T>
std::string ToString(const val::matrix<T>& A);

template <class T>
void makeprimitiv(val::vector<T> &v);

template <class T>
void makeprimitiv(val::matrix<T> &A, int k = 0);


/*
template <class T>
std::string ToString(const val::vector<T>& v);
*/


//  --------------------------------------------------------------------------------------------



/*
template <class T>
val::matrix<T> stringtomatrix(const std::string &s)
{
    val::matrix<T> LES;

    if (s=="") return LES;
    int l=s.length(),first=0,i,j,k,nzeichen=0,m,n;
    std::string zeichen="";

    for (i=0;i<l;i++)
        if (s[i]!='\n' && s[i]!=' ' ) break;
    first=i;
    m=n=0;
    //Bestimme Spaltenzahl n
    for (;i<l;) {
        if (i<l && s[i]=='\n') {break;}
        while (i<l && (s[i]!=' ' && s[i] != '\n' )) i++;
        n++;
        while (i<l && s[i]==' ') i++;
    }
    //Bestimme Spaltenzahl m
    //if (n<=1) {m=0;return LES;}

    for (i=first;i<l;) {
        if (s[i]!=' ' && s[i]!='\n') {
            while (i<l && s[i]!=' ' && s[i]!='\n') i++;
            nzeichen++;
        }
        while (i<l && (s[i]==' ' || s[i] =='\n')) i++;
    }
    if (n==0) return LES;
    m=nzeichen/n;
    if (nzeichen%n!=0) m++;

    LES=val::matrix<T>(m,n);
    LES.make_zero();

    i=j=0;
    for (k=first;k<l;) {
        if (s[k]!=' ' && s[k]!='\n') {
            while (k<l && s[k]!=' ' && s[k]!='\n') {
                zeichen+=s[k];
                k++;
            }
            //LES(i,j)=val::string_to_rational(zeichen);
            LES(i,j)=stringtonumber<T>(zeichen);
            zeichen="";
            j++;
            if (j>=n) {j=0;i++;}
        }
        while (k<l && (s[k]==' ' || s[k] =='\n')) {
               k++;
        }
    }
    return LES;
}
*/


template <class T>
std::string ToString(const val::matrix<T>& A)
{
    int i,j,k,maxlength=0,*leer=NULL,l,m=A.numberofrows(),n=A.numberofcolumns();
    std:: string s="",help;


    if (n) leer = new int[n];

    for (j=0;j<n;j++) {
        maxlength=0;
        for (i=0;i<m;i++) {
            //help=val::ToString(A[i][j]);
            help = val::ToString(A(i,j));
            l=2*int(help.length());
            if (l && help[0]=='-') l--;
            if (l>maxlength) maxlength=l;
        }
        leer[j]=maxlength;
    }


    for (i=0;i<m;i++) {
        for (j=0;j<n;j++) {
            //help=val::ToString(A[i][j]);
            help = val::ToString(A(i,j));
            l=2*int(help.length());
            if (l && help[0]=='-') l--;
            for (k=0;k<4+leer[j]-l;k++) s+=" ";
            s+=help;
        }
        s+='\n';
    }

    if (leer!=NULL) delete[] leer;
    return s;
}

/*
template <class T>
std::string ToString(const val::vector<T>& v)
{
   std::stringstream ss;//create a stringstream
   ss<<v;//add number to the stream
   return ss.str();
}
*/

// ---------------------------------------------------------------------------------------------


template <class T>
void ComputeAffin(std::string& Input,val::affinspace<T>& A,int Output);

template <class T>
int ComputeIntersection(const val::affinspace<T> &A1,const val::affinspace<T> &A2);

template <class T>
void OrthogonalProjektionMap(const val::affinspace<T> &A,val::vector<T> &b,val::matrix<T> &M);

void ComputeProjectionMap(const val::affinspace<val::rational> &A, val::matrix<val::rational> &P, int Output);

// orthogonal from A1 to A
void ComputeProjections(const val::affinspace<val::rational> &A, const val::matrix<val::rational> &P,
                        const val::affinspace<val::rational> &A1, int toA1);


void CompAffinMain(std::string & I_1,std::string& I_2);


// ---------------------------------------------------------------------


template <class T>
void ComputeAffin(std::string& Input,val::affinspace<T>& A,int Output)
{
    int i,type;

    type=getstringready(Input);
    val::matrix<T> B = val::FromString<val::matrix<T>>(Input); //stringtomatrix<T>(Input);


    //WriteText(ToString(B));

    if (type==2) {
        A=val::affinspace<T>(std::move(B));
    }

    else {
        val::vector<val::vector<T> > V;
        val::movefrommatrixtovector(B,V);
        A=val::affinspace<T>(std::move(V));
        //for (i=0;i<V.dimension();i++) WriteText(ToString(V(i))+"\n");
    }

    //WriteText(val::ToString(B.numberofrows())+"\n");

    int Globaldim=A.globaldim(),Dimension=A.dimension();
    const val::vector<T>& Point=A.getPoint();
    val::matrix<T> LES = A.getLES();
    val::vector<val::vector<T> > Vspace=A.getVspace(), OrthBasis= A.getOrthBasis(), OrthSpace=A.getOrthSpace();
    std::string s="";

    if (Globaldim < 6) {
        for (auto &v : Vspace) ::makeprimitiv(v);
        for (auto &v : OrthBasis) ::makeprimitiv(v);
        for (auto &v : OrthSpace) ::makeprimitiv(v);
        makeprimitiv(LES);
    }

    if (Globaldim==0) return;
    s+="Globaldim = " + val::ToString(Globaldim) + " , dim(A) = "+val::ToString(Dimension)+"\n";
    s+="A = \n" + val::ToString(Point);

    if (Dimension>0) s+= "\n + < ";
    else s+="\n";
    for (i=0;i<Dimension;i++) {
        s += val::ToString(Vspace(i));
        if (i==Dimension-1) s+=" >\n";
        else s+="\n        ";
    }

    s+="\n als LGS : \n" + ::ToString(LES);
    s+="\n Orthogonalbasis von A: \n";
    for (i=0;i<OrthBasis.dimension();i++) s+=val::ToString(OrthBasis(i)) + "\n";

    s+="\n Othogonalraum zu A:\n";
    for (i=0;i<OrthSpace.dimension();i++) s+= val::ToString(OrthSpace(i))+"\n";


    WriteText(s,Output);

}


template <class T>
int ComputeIntersection(const val::affinspace<T> &A1,const val::affinspace<T> &A2)
{

    if (A1.globaldim()==0 || A2.globaldim()==0) {return 0;}

    if (A1.globaldim()!=A2.globaldim()) {
        WriteText("Globale Dimensionen sind verschieden.\nKein Vergleich moeglich!",0);
        return 0;
    }


    if (A1.getLES().isempty() || A2.getLES().isempty()) {WriteText("LES empty!");return 0;}


    val::matrix<T> X;
    enum val::affinspace<T>::Intersection_Type Type;

    Type = A1.intersection(A2,X);

    if (Type==val::affinspace<T>::WINDSCHIEF) {
        WriteText(L"Räume sind windschief zueinader!\n");
        return 0;
    }
    else if (Type==val::affinspace<T>::PARALLEL) {
        WriteText(L"Räume sind parallel!\n");
        return 0;
    }
    else if (Type==val::affinspace<T>::DISJOINT) {
        WriteText(L"Räume sind disjunkt!\n");
        return 0;
    }
    else if (Type==val::affinspace<T>::SUBSPACE) {
        WriteText("A1 ist Teilraum von A2\n");
        return 1;
    }
    else if (Type==val::affinspace<T>::SUPSPACE) {
        WriteText("A2 ist Teilraum von A1\n");
        return 1;
    }
    else if (Type==val::affinspace<T>::EQUAL) {
        WriteText(L"Räume sind identisch\n");
        return 1;
    }
    else {
        int i,j,r=X.numberofrows(), n = A1.globaldim();
        wxString s="";
        s+="Schnitt-Raum:\n";
        if (r > 1 && A1.globaldim() < 6) makeprimitiv(X,1);
        for (j=0;j<X.numberofcolumns();j++) s+=val::ToString(X(0,j))+ "  ";

        if (r>1) s+=  "\n + < ";
        for (i=1;i<X.numberofrows();i++) {
            for (j=0;j<X.numberofcolumns();j++) s+="  "+ val::ToString(X(i,j));
            if (i==X.numberofrows()-1) s+="  >\n";
            else s+="\n";
        }
        if (n >= 2 && n <=3 && A1.dimension() != 0 && A1.dimension() != n && A2.dimension() !=0 && A2.dimension() != n) {
            val::vector<T> r1, r2;
            double angle, r12, nr1, nr2;
            if (A1.dimension() == 1) r1 = A1.getVspace()[0];
            else r1 = A1.getOrthSpace()[0];
            if (A2.dimension() == 1) r2 = A2.getVspace()[0];
            else r2 = A2.getOrthSpace()[0];
            r12 = (r1) *  (r2);
            nr1 = (r1) *  (r1); nr2 = (r2) *  (r2);
            //std::cout << r1 << std::endl << r2 << std::endl;
            //std::cout << std::endl << r12 << " , " << nr1 << " , " << nr2 << std::endl;
            angle = val::arccos(val::abs(r12)/val::sqrt(nr1*nr2)) * 180/val::PI;
            angle = val::round(angle,2);
            if (A1.dimension() != A2.dimension()) angle = 90 - angle;
            s += "\nSchnittwinkel: " + val::ToString(angle) + _T("°\n");
        }
        WriteText(s);
        return 1;
    }

    return 1;

}


template <class T>
void OrthogonalProjektionMap(const val::affinspace<T> &A,val::vector<T> &b,val::matrix<T> &M)
{
    if (!A.globaldim()) return;
    const val::vector<val::vector<T> > &B = A.getOrthBasis();
    int n = A.globaldim(), m = A.dimension(), i, j;
    T zero = val::zero_element<T>(), one = val::unity_element<T>();
    val::vector<T> norm_B(m), e(zero,n), y(n);

    M = val::matrix<T>(zero,n,n);
    b = val::vector<T>(zero,n);

    for (i = 0; i < m; ++i) {
        norm_B(i) = val::innerproduct(B(i),B(i));
    }

    // Get Map-Matrix:
    for (i = 0; i < n; ++i) {
        y.make_zero();
        e(i) = one;
        for (j = 0; j < m; ++j) y += (val::innerproduct(e,B(j))/norm_B(j)) * B(j);
        for (j = 0; j < n; ++j) M(j,i) = std::move(y(j));
        e(i) = zero;
    }

    // Get vector b:
    b = A.getPoint() - M * A.getPoint();
}






#endif // COMPAFFIN_H_INCLUDED
