#include <iostream>
#include <cstring>
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;


class LibrarieExceptie : public exception {
protected:
    string mesaj;
public:
    explicit LibrarieExceptie(const string& msg) : mesaj(msg){}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

// exceptie pentru pret invalid
class PretInvalidExceptie : public LibrarieExceptie {
private:
    float pretGresit;
    string mesajDetaliat;
public:
    explicit PretInvalidExceptie(float pret)
        : LibrarieExceptie("Pret invalid!"), pretGresit(pret) {
        mesajDetaliat = "Eroare! Pretul este invalid: " + to_string(pretGresit) + " RON. Trebuie sa fie pozitiv. ";
    }
    float getPretGresit() const {
        return pretGresit;
    }
    const char* what() const noexcept override{
        return mesajDetaliat.c_str();
    }
};

// exceptie pentru stoc invalid
class StocInvalidExceptie : public LibrarieExceptie {
private:
    int stocGresit;
    string mesajDetaliat;
public:
    explicit StocInvalidExceptie(int stoc)
        : LibrarieExceptie("Stoc invalid"), stocGresit(stoc) {
        mesajDetaliat = "Eroare! Stocul nu poate fi negativ: " + to_string(stocGresit) + ".";
    }

    int getStocGresit() const {
        return stocGresit;
    }

    const char* what() const noexcept override {
        return mesajDetaliat.c_str();
    }
};

// exceptie pentru un produs inexistent
class ProdusNegasitExceptie : public LibrarieExceptie {
private:
    int idCautat;
    string mesajDetaliat;
public:
    explicit ProdusNegasitExceptie(int id)
        : LibrarieExceptie("Produs negasit! "), idCautat(id) {
        mesajDetaliat = "Eroare! Elementul cu ID- ul " + to_string(idCautat) + " nu exista in inventar.";
    }

    int getIDCautat() const {
        return idCautat;
    }
    const char* what() const noexcept override {
        return mesajDetaliat.c_str();
    }
};

// exceptie pentru rating invalid
class RatingInvalidExceptie : public LibrarieExceptie {
private:
    float ratingGresit;
    string mesajDetaliat;
public:
    explicit RatingInvalidExceptie(float rating)
        : LibrarieExceptie("Rating invalid"), ratingGresit(rating) {
        mesajDetaliat = "Eroare! Rating-ul " + to_string(ratingGresit) + " este invalid. Trebuie sa fie intre 0.0 si 10.0";
    }

    float getRatingGresit() const {
        return ratingGresit;
    }

    const char* what() const noexcept override {
        return mesajDetaliat.c_str();
    }
};

// exceptie pentru varsta invalida
class VarstaInvalidaExceptie : public LibrarieExceptie {
private:
    int varstaGresita;
    string mesajDetaliat;
public:
    explicit VarstaInvalidaExceptie(int varsta)
        : LibrarieExceptie("Varsta invalida"), varstaGresita(varsta) {
        mesajDetaliat = "Eroare! Varsta nu poate fi negativa : " + to_string(varstaGresita) + ".";
    }

    int getVarstaGresita() const {
        return varstaGresita;
    }

    const char* what() const noexcept override {
        return mesajDetaliat.c_str();
    }
};

// exceptie pentru telefon invalid
class TelefonInvalidExceptie : public LibrarieExceptie {
private:
    long long telefonGresit;
    string mesajDetaliat;
public:
    explicit TelefonInvalidExceptie(long long tel)
        : LibrarieExceptie("Telefon invalid!"), telefonGresit(tel) {
        mesajDetaliat = "Eroare! Numarul de telefon " + to_string(telefonGresit) + " este invalid (ex: 07XXXXXXXX).";
    }

    long long getTelefonGresit() const {
        return telefonGresit;
    }

    const char* what() const noexcept override {
        return mesajDetaliat.c_str();
    }
};

// singleton
class Logger {
private:
    vector<string> jurnal;

    Logger() {
        jurnal.push_back("Logger initializat.");
    }

public:
    // pentru a nu putea copia
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Singleton Meyers
    static Logger& getInstance() {
        static Logger instanta;
        return instanta;
    }

    void log(const string& mesaj) {
        jurnal.push_back(mesaj);
    }

    void afiseazaJurnal() const {
        cout << "JURNAL LIBRARIE: " << jurnal.size() << " inregistrari" << endl;
        for (const auto& intrare : jurnal) {
            cout << intrare << endl;
        }
    }



};


class IObject {
    static int contor;
    const int id;

protected:
    // constructorul e protected pentru a instantia doar din derivate
    IObject() : id(++contor){}
    IObject(const IObject&) : id(++contor){}

public:
    virtual ~IObject(){}

    int getId() const {
        return id;
    }
    virtual string toString() const = 0;

    friend ostream& operator<<(ostream& os, const IObject& obj) {
        return os << obj.toString();
    }

    bool operator==(const IObject& alt) const noexcept {
        return id == alt.id;
    }

};
int IObject::contor = 0;


class ProdusLibrarie : public IObject {
    // aceasta clasa este abstracta, nu poate fi instantiata
    // ProdusLibrarie produs; va da eroare
    // deoarece clasa contine functii pur virtuale
    // este o interfata pentru clasele Carte si CarteEditieSpeciala


private:
    // modificatorul private ascunde informatiile fata de clasele derivate si de exterior
    // astfel codul de securitate poate fi accesat doar din interiorul clasei
    int codSecuritateIntern = 123;
protected:
    // am folosit protected astfel incat astributele sa fie ascunse din exterior,
    // dar accesibile pentru clasele derivate
    float pret;
    int stoc;
    string taraOrigine;

public:
    // public defineste interfata clasei. Aici sunt metodele, constructorii si
    // destructorul care pot fi apelate din orice parte a programului

    // constructor fara parametri
    ProdusLibrarie(): pret(0.0), stoc(0), taraOrigine("Necunoscut") {
        Logger::getInstance().log("ProdusLibrarie creat cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - Constructor fara parametri" << endl;
    }

    // constructor cu toti parametri
    ProdusLibrarie(float p, int s, const string& tara) {
        if (p < 0)
            throw PretInvalidExceptie(p);
        pret = p;
        if (s < 0)
            throw StocInvalidExceptie(s);
        stoc = s;
        taraOrigine = tara.empty() ? "Necunoscut" : tara;
        Logger::getInstance().log("ProdusLibrarie creat cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - Constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri - pret, stoc
    ProdusLibrarie(float p, int s){
        if (p < 0)
            throw PretInvalidExceptie(p);
        pret = p;
        if (s < 0)
            throw StocInvalidExceptie(s);
        stoc = s;
        taraOrigine = "Necunoscut";
        Logger::getInstance().log("ProdusLibrarie creat cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - Constructor cu parametri - pret, stoc" << endl;
    }

    // constructor cu parametri - pret, taraOrigine
    ProdusLibrarie(float p, const string& tara) :stoc(0){
        if (p < 0)
            throw PretInvalidExceptie(p);
        pret = p;
        taraOrigine = tara.empty() ? "Necunoscut" : tara;
        Logger::getInstance().log("ProdusLibrarie creat cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - Constructor cu parametri - pret, tara origine"<< endl;
    }

    // constructor cu parametri - pret
    ProdusLibrarie(float p): stoc(0), taraOrigine("Necunoscuta") {
        if (p < 0)
            throw PretInvalidExceptie(p);
        pret = p;
        Logger::getInstance().log("ProdusLibrarie creat cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - constructor cu parametri - pret" << endl;
    }

    // constructor de copiere
    ProdusLibrarie(const ProdusLibrarie& p): pret(p.pret), stoc(p.stoc), taraOrigine(p.taraOrigine) {
        Logger::getInstance().log("ProdusLibrarie creat(prin copiere) cu ID-ul : " + to_string(getId()));
        cout << "ProdusLibrarie - Constructor de copiere" << endl;
    }

    // destructor vitrual
    virtual ~ProdusLibrarie() noexcept {
        Logger::getInstance().log("ProdusLibrarie distrus. ID: " + to_string(getId()));
        cout << "ProdusLibrarie - destructor" << endl;
    }

    // operator de atribuire
    ProdusLibrarie& operator=(const ProdusLibrarie& p) {
        if (this != &p) {
            pret = p.pret;
            stoc = p.stoc;
            taraOrigine = p.taraOrigine;
        }
        return *this;
    }

    // getteri si setteri
    //getteri
    float getPret() const {
        return pret;
    }
    int getStoc() const {
        return stoc;
    }
    string getTaraOrigine() const {
        return taraOrigine;
    }

    // setteri
    void setPret(float p) {
       if (p < 0)
           throw PretInvalidExceptie(p);
        pret = p;
    }
    void setStoc(int s) {
        if (s < 0)
            throw StocInvalidExceptie(s);
        stoc = s;
    }
    void setTaraOrigine(const string& tara) {
        taraOrigine = tara;

    }

    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const ProdusLibrarie& p) {
        os << "Pret: " << p.pret << " RON" << endl;
        os << "Stoc curent: " << p.stoc << " bucati" << endl;
        os << "Tara de origine: " << (p.taraOrigine.empty() ? "Necunoscut" : p.taraOrigine) << endl;
        return os;
    }

    // citire
    friend istream& operator>>(istream& is, ProdusLibrarie& p) {
        cout << "Introduceti pretul: ";
        is >> p.pret;
        if (p.pret < 0)
            throw PretInvalidExceptie(p.pret);

        cout << "Introduceti stocul: ";
        is >> p.stoc;
        if (p.stoc < 0)
            throw StocInvalidExceptie(p.stoc);


        cout << "Introduceti tara de origine: ";
        if (is.peek() == '\n')
            is.ignore();
        getline(is, p.taraOrigine);
        return is;
    }


    // operator de indexare []
    string operator[](int index) const {
        switch (index) {
            case 0:
                return taraOrigine;
            case 1:
                return stoc ? "Mai sunt produse in stoc" : "Nu mai sunt produse in stoc";
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }


    // operator ==
    bool operator==(const ProdusLibrarie& p) const {
        return (pret == p.pret) && (stoc == p.stoc);
    }

    // operator <
    bool operator<(const ProdusLibrarie& p) const {
        return pret < p.pret;
    }

    // utilizare ostringstream
    virtual string toString() const {
        ostringstream oss;
        oss << "Pret: " << " RON, Stoc: " << stoc << ", Tara origine: " << taraOrigine;
        return oss.str();
    }

    // nu am inclus operatori matematici in clasa abstracta. aceasta nu poate fi instantiata,
    // motiv pentru care folosirea operatorilor matematici ar fi fost imposibila


    // functii pur virtuale
    virtual string getTipProdus() const = 0;
    virtual bool necesitaImpachetareSpeciala() const = 0;

    virtual void afiseazaDetalii() const {
        cout << "Pret: " << pret << " RON" << endl;
        cout << "Stoc curent: " << stoc << " bucati" << endl;
        cout << "Tara de origine: " << taraOrigine << endl;
    }

};

// cand folosim char* trebuie sa scriem constructorul de copere, operatorul = si destructorul
// pentru a face deep copy si a evita memory leaks.
// cand folosim string nu mai este nevoie de toate aceste elemente deoarece
// clasa string se gestioneaza singura

class Carte : public ProdusLibrarie {
    // Am folosit private pentru a asigura incapsularea datelor.
    // Acestea pot fi modificate strict din metodele clasei, prevening coruperea din exterior
private:

protected:
    string titlu;
    string autor;
    int anPublicare;


public:
    // constructor fara parametri
    Carte() : ProdusLibrarie(), titlu("Necunoscut"), autor("Anonim"), anPublicare(0){
        cout << "Carte - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    Carte(const string& t, const string& a, int an, float pret, int stoc, const string& tara)
    :  ProdusLibrarie(pret, stoc, tara), titlu(t), autor(a), anPublicare(an) {

        if (an <= 0 || an > 2026) {
            throw invalid_argument("Eroare! Anul de publicare trebuie sa fie intre 1 si 2026!");
        }

        cout << "Carte - constructor cu toti parametrii" << endl;

    }

    // constructor cu parametri - titlu si pret
    Carte(const string& t, float pret)
         : ProdusLibrarie(pret), titlu(t), autor("Anonim"), anPublicare(0) {
        cout << "Carte - constructor cu parametri - titlu si pret" << endl;
    }

    // constructor cu parametri - titlu, autor si anPublicare
    Carte(const string& t, const string& a, int an)
        : ProdusLibrarie(), titlu(t), autor(a), anPublicare(an) {
        if (an <= 0 || an > 2026) throw invalid_argument("Eroare! Anul de publicare trebuie sa fie intre 1 si 2026!");
        cout << "Carte - constructor cu parametri - titlu, autor si an publicare" << endl;
    }

    // constructor de copiere
    Carte(const Carte& c)
        : ProdusLibrarie(c), titlu(c.titlu), autor(c.autor), anPublicare(c.anPublicare) {
        cout << "Carte - constructor de copiere" << endl;
    }

    // destructor
    ~Carte() noexcept {
        cout << "Carte - destructor" << endl;
    }

    // operatorul de atribuire
    Carte& operator=(const Carte& c) {
        if (this == &c) return *this;

        ProdusLibrarie::operator=(c);
        titlu = c.titlu;
        autor = c.autor;
        anPublicare = c.anPublicare;

        return *this;
    }

    // getteri si setteri
    // getteri
    string getTitlu() const {
        return titlu;
    }
    string getAutor() const {
        return autor;
    }
    int getAnPublicare() const {
        return anPublicare;
    }


    //setteri
    void setTitlu(const string& nouTitlu) {
        titlu = nouTitlu;
    }
    void setAutor(const string& nouAutor) {
        autor = nouAutor;
    }
    void setAnPublicare(int nouAn) {
        if (nouAn <= 0 || nouAn > 2026)
            throw invalid_argument("Eroare! Anum de publicare trebuie sa fie intre 1 si 2026! ");
        anPublicare = nouAn;
    }

    // foloseste find, length, replace
    void corecteazaTitlu(const string& cuvantGresit, const string& cuvantCorect) {
        size_t pos = titlu.find(cuvantGresit);
        while (pos != string::npos) {
            titlu.replace(pos, cuvantGresit.length(), cuvantCorect);
            pos = titlu.find(cuvantGresit, pos + cuvantCorect.length());
        }
    }

    // foloseste empty, substr, size
    string getInitialeAutor() const {
        if (autor.empty()) return "";

        string initiale = autor.substr(0, 1) + ".";
        size_t spatiu = autor.find(' ');

        if (spatiu != string::npos && spatiu + 1 < autor.size()) {
            initiale += autor.substr(spatiu + 1, 1) + ".";
        }
        return initiale;
    }

    string toString() const override {
        ostringstream oss;
        oss << "Carte [ID=" << getId() << ", Titlu: " << titlu
            << ", Autor: " << autor << ", An: " << anPublicare
            << ", Pret: " << pret << " RON, Stoc: " << stoc << "]";
        return oss.str();
    }


    // operatori de stream

    // citire
    friend istream& operator>>(istream& is, Carte& c) {
        cout << "Introduceti titlul: ";
        if (is.peek() == '\n') // se ignora caracterul newline, daca exista
            is.ignore();
        getline(is, c.titlu);

        cout << "Introduceti autorul: ";
        getline(is, c.autor);

        cout << "Introduceti anul de publicare: ";
        is >> c.anPublicare;
        if (c.anPublicare <= 0 || c.anPublicare > 2026) throw invalid_argument("Eroare! Anul de publicare trebuie sa fie intre 1 si 2026! ");

        is >> (ProdusLibrarie&)c;

        return is; // permite citiri in lant
    }


    // Supraincarcarea operatorilor
    // Operator de indexare
    string operator[](int index) const{
        switch (index) {
            case 0:
                return titlu;
            case 1:
                return autor;
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }

    // Operator++ - prefix - (++carte)
    Carte& operator++() {
        pret += 1.0;
        return *this;
    }
    // Operator ++ - (carte++)
    Carte operator++(int) {
        Carte c(*this);
        ++(*this);
        return c;
    }

    // operatori matematici: + si -
    // Operator +: adaugare la pret
    Carte operator+(float adaos) const {
        Carte res = *this;
        res.pret += adaos;
        if (res.pret < 0)
            throw PretInvalidExceptie(res.pret);
        return res;
    }

    // operator pentru comutativitatea adunarii
    friend Carte operator+(float adaos, const Carte& c);

    // Operator -: scadere din pret
    Carte operator-(float reducere) const{
        Carte res = *this;
        res.pret -= reducere;
        if (res.pret < 0)
            throw PretInvalidExceptie(res.pret);
        return res;
    }
    // operator pentru comutativitatea scaderii
    friend Carte operator-(float valoare, const Carte& c);


    // Operatorul de egalitate ==
    // Verifica daca doua carti au acelasi titlu si autor
    bool operator==(const Carte& c) const {
        return (titlu == c.titlu) && (autor == c.autor);
    }

    // Operatorul <=
    // Compara preturile a doua carti
    bool operator<=(const Carte& c) const {
        return pret <= c.pret;
    }

    // Aplicare discount
    void aplicaDiscount(float procent) {
        if (procent > 0 && procent <= 100) {
            float reducere = (procent / 100.0) * pret;
            pret -= reducere;
            cout << "Noul pret pentru cartea " << titlu << " este " << pret;
        }
        else
            throw invalid_argument("Eroare! Procentul de discount trebuie sa fie intre 0 si 100!");
    }

    string getTipProdus() const override {
        return "Carte Standard";
    }

    bool necesitaImpachetareSpeciala() const override {
        return false;
    }

    void afiseazaDetalii() const override {
        cout << "Titlu: " << titlu << endl;
        cout << "Autor: " << autor << endl;
        cout << "An publicare: " << anPublicare << endl;
        ProdusLibrarie::afiseazaDetalii(); // extind comportamentul functiei din clasa de baza
    }


};


Carte operator+(float adaos, const Carte& c) {
    return c + adaos;
}

Carte operator-(float valoare, const Carte& c) {
    Carte res = c;
    res.setPret(valoare - c.getPret());
    // verific in setPret daca pretul e mai mic decat 0
    return res;
}

// am marcat clasa CarteEditieSpeciala cu final deoarece reprezinta un model final
// in ceea ce priveste cartile si nu ar avea sens sa derivam mai departe din ea.

class CarteEditieSpeciala final : public Carte {
private:
    string materialCoperta;
    bool contineSemnatura;
    int nrIlustratiiExtra;


public:
    // constructor fara parametri
    CarteEditieSpeciala() : Carte(), materialCoperta("Standard"), contineSemnatura(false), nrIlustratiiExtra(0) {
        cout << "CarteEditieSpeciala - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    CarteEditieSpeciala(const string& titlu, const string& autor, int an, float p, int s,
                        const string& tara, const string& material, bool semnatura, int ilustratii)
        : Carte(titlu, autor, an, p, s, tara), contineSemnatura(semnatura), nrIlustratiiExtra(ilustratii) {

        materialCoperta = material.empty() ? "Standard" : material;

        if (nrIlustratiiExtra < 0)
            throw invalid_argument("Eroare! Numarul de ilustratii extra nu poate fi negativ!");

        cout << "CarteEditieSpeciala - Constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri - toti parametrii clasei carte
    CarteEditieSpeciala(const string& titlu, const string& autor, int an, float p, int s, const string& tara)
        : Carte(titlu, autor, an, p, s, tara), materialCoperta("Standard"), contineSemnatura(false), nrIlustratiiExtra(0) {
        cout << "CarteEditieSpeciala - Constructor cu parametri - parametrii clasei carte" << endl;
    }

    //constructor cu parametri - material coperta, contine semnatura, nr ilustratii extra
    CarteEditieSpeciala(const string& material, bool semnatura, int ilustratii)
        : Carte(), contineSemnatura(semnatura), nrIlustratiiExtra(ilustratii) {

        materialCoperta = material.empty() ? "Standard" : material;

        if (nrIlustratiiExtra < 0)
            throw invalid_argument("Eroare! Numarul de ilustratii extra nu poate fi negativ!");
        cout << "CarteEditieSpeciala - Constructor cu parametri - material coperta, contine semnatura, nr ilustratii extra" << endl;
    }

    // constructor de copiere
    CarteEditieSpeciala(const CarteEditieSpeciala& c)
        : Carte(c), materialCoperta(c.materialCoperta), contineSemnatura(c.contineSemnatura), nrIlustratiiExtra(c.nrIlustratiiExtra) {
        cout << "CarteEditieSpeciala - Constructor de copiere" << endl;
    }


    // destructor
    ~CarteEditieSpeciala() noexcept {
        cout << "CarteEditieSpeciala - destructor" << endl;
    }

    // operator de atribuire
    CarteEditieSpeciala& operator=(const CarteEditieSpeciala& c) {
        if (this != &c) {
            Carte::operator=(c);
            materialCoperta = c.materialCoperta;
            contineSemnatura = c.contineSemnatura;
            nrIlustratiiExtra = c.nrIlustratiiExtra;
        }
        return *this;
    }
    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const CarteEditieSpeciala& c) {
        os << (const Carte&)c;
        os << "Material coperta: " << c.materialCoperta << endl;
        os << "Contine semnatura: " << (c.contineSemnatura ? "DA" : "NU") << endl;
        os << "Nr ilustratii extra: " << c.nrIlustratiiExtra << endl;
        return os;
    }

    // citire
    friend istream& operator>>(istream& is, CarteEditieSpeciala& c) {
        is >> (Carte&)c;
        cout << "Introduceti materialul copertii: ";
        if (is.peek() == '\n') {
            is.ignore();
        }
        getline(is, c.materialCoperta);

        cout << "Contine semnatura? (1-DA, 0-NU) ";
        is >> c.contineSemnatura;

        cout << "Cate ilustratii extra contine? ";
        is >> c.nrIlustratiiExtra;
        if (c.nrIlustratiiExtra < 0)
            throw invalid_argument("Eroare! Numarul de ilustratii extra nu poate fi negativ!");
        return is;
    }

    // getteri si setteri
    // getteri
    string getMaterialCoperta() const {
        return materialCoperta;
    }
    bool getContineSemnatura() const {
        return contineSemnatura;
    }
    int getNrIlustratiiExtra() const {
        return nrIlustratiiExtra;
    }

    // setteri
    void setMaterialCoperta(const string& material) {
        materialCoperta = material.empty() ? "Necunoscut" : material;
    }

    void setContineSemnatura(bool semnatura) {
        contineSemnatura = semnatura;
    }

    void setNrIlustratiiExtra(int nr) {
        if (nr < 0) {
            throw invalid_argument("Eroare! Numarul de ilustratii extra nu poate fi negativ!");
        }
        nrIlustratiiExtra = nr;
    }

    // operatorul []
    string operator[](int index) const {
        switch (index) {
            case 0:
                return materialCoperta;
            case 1:
                return (contineSemnatura ? "DA" : "NU");
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }

    // operator ++
    CarteEditieSpeciala& operator++() {
        nrIlustratiiExtra++;
        return *this;
    }
    CarteEditieSpeciala operator++(int) {
        CarteEditieSpeciala temp(*this);
        ++(*this);
        return temp;
    }

    // operatori matematici
    CarteEditieSpeciala operator+(float adaos) const {
        CarteEditieSpeciala res = *this;
        res.setPret(res.getPret() + adaos);
        return res;
    }

    friend CarteEditieSpeciala operator+(float adaos, const CarteEditieSpeciala& c);

    CarteEditieSpeciala operator-(float reducere) const {
        CarteEditieSpeciala res = *this;
        float pretNou  = res.getPret() - reducere;
        res.setPret(pretNou);
        return res;
    }

    // operatorul ==
    bool operator==(const CarteEditieSpeciala& c) const {
        return Carte::operator==(c) && (materialCoperta == c.materialCoperta);
    }

    // operatorul <
    bool operator<(const CarteEditieSpeciala& c) const {
        return Carte::operator<(c);
    }



    // suprascriere
    void afiseazaDetalii() const override {
        Carte::afiseazaDetalii();
        cout << "Material Coperta Editie Speciala: " << materialCoperta << endl;
        cout << "Semnatura: " << (contineSemnatura ? "DA" : "NU") << endl;
        cout << "Nr ilustratii extra: " << nrIlustratiiExtra << endl;
    }

    // concatenare de string uri cu operatorul +
    string toString() const override {
        return Carte::toString() + " | Material: " + materialCoperta +
               " | Semnatura: " + (contineSemnatura ? "DA" : "NU") +
               " | Ilustratii extra: " + to_string(nrIlustratiiExtra);
    }


    string getTipProdus() const override {
        return "Carte Editie Speciala";
    }

    bool necesitaImpachetareSpeciala() const override {
        return true;
    }


    bool estePiesaDeColectieRara() const {
        return contineSemnatura && (nrIlustratiiExtra >= 3);
    }
};

CarteEditieSpeciala operator+(float adaos, const CarteEditieSpeciala& c) {
    return c + adaos;
}



//  CLASA AUTOR

class Autor : public IObject {
private:

    string nume;
    bool contemporan;
    int varsta;
    float ratingMediu;

public:
    // constructor fara parametri
    Autor() :  nume("Anonim"), contemporan(false), varsta(0), ratingMediu(0.0) {
        cout << "Autor - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    Autor(const string& n, bool cont, int v, float rating)
        : nume(n.empty() ? "Anonim" : n), contemporan(cont) {
        if (v < 0) throw VarstaInvalidaExceptie(v);
        varsta = v;

        if (rating < 0.0 || rating > 10.0) throw RatingInvalidExceptie(rating);
        ratingMediu = rating;
    }

    // constructor cu parametri - nume si contemporan
    Autor(const string& n, bool cont)
        : nume(n), contemporan(cont), varsta(0), ratingMediu(0.0) {}

    // constructor cu parametri - nume si rating
    Autor(const string& n, float rating)
        : nume(n), contemporan(false), varsta(0) {
        if (rating < 0 || rating > 10) throw RatingInvalidExceptie(rating);
        ratingMediu = rating;
    }

    // constructor de copiere
    Autor(const Autor& a)
        : nume(a.nume), contemporan(a.contemporan), varsta(a.varsta), ratingMediu(a.ratingMediu) {
        cout << "Autor - constructor de copiere" << endl;
    }

    // destructor
    virtual ~Autor() noexcept {
        // Fara delete[]
        cout << "Autor - destructor" << endl;
    }

    // Operatorul de atribuire
    Autor& operator=(const Autor& a) {
        if (this == &a) return *this;

        nume = a.nume;
        contemporan = a.contemporan;
        varsta = a.varsta;
        ratingMediu = a.ratingMediu;

        return *this;
    }

    string toString() const override {
        ostringstream oss;
        oss << "Nume: " << nume << endl;
        oss << "Contemporan: " << boolalpha << contemporan << endl;
        oss << "Varsta: " << varsta << endl;
        oss << "Rating mediu: " << ratingMediu << endl;
        oss << "ID autor: " << getId() << endl;
        return oss.str();

    }


    // operatori de stream

    // citire
    friend istream& operator>>(istream& is, Autor& a) {

        cout<< "Introduceti numele: ";
        if (is.peek() == '\n')
            is.ignore();
        getline(is, a.nume); // Citire corecta si sigura cu spatii

        cout<< "Este contemporan? (1 pentru DA sau 0 pentru NU): ";
        is >> a.contemporan;

        cout << "Introduceti varsta: ";
        is >> a.varsta;
        if (a.varsta < 0) throw VarstaInvalidaExceptie(a.varsta);

        cout << "Introduceti rating-ul mediu (0.0-10.0): ";
        is >> a.ratingMediu;
        if (a.ratingMediu < 0 || a.ratingMediu > 10) throw RatingInvalidExceptie(a.ratingMediu);

        return is;
    }

    virtual void afiseazaDetalii() const {
        cout << "Nume: " << nume << endl;
        cout << "Contemporan: " << (contemporan ? "DA" : "NU") << endl;
        cout << "Varsta: " << varsta << endl;
        cout << "Rating mediu: " << ratingMediu << endl;
        cout << endl;
    }

    // getteri si setteri
    string getNume() const {
        return nume;
    }
    int getVarsta() const {
        return varsta;
    }
    bool getContemporan() const {
        return contemporan;
    }
    float getRatingMediu() const {
        return ratingMediu;
    }

    // setteri
    void setNume(const string& nouNume) {
        nume = nouNume;
    }
    void setVarsta(int nouVarsta) {
        if (nouVarsta < 0)
            throw VarstaInvalidaExceptie(nouVarsta);
        varsta = nouVarsta;
    }
    void setContemporan(bool status) {
        contemporan = status;
    }
    void setRatingMediu(float nouRating) {
        if (nouRating < 0.0 || nouRating > 10.0)
            throw RatingInvalidExceptie(nouRating);
        ratingMediu = nouRating;
    }

    // operator de indexare
    string operator[](int index) const{
        switch (index) {
            case 0:
                return nume;
            case 1:
                return(contemporan ? "Da" : "Nu");
            default:
                throw out_of_range("Eroare! Index invalid!");
        }

    }

    // operator++
    Autor& operator++() {
        ratingMediu += 1.0;
        if (ratingMediu > 10.0)
            ratingMediu = 10.0;
        return *this;
    }
    Autor operator++(int) {
        Autor a(*this);
        ++(*this);
        return a;
    }

    // operatori matematici: + si -

    Autor operator+(float adaos) const {
        Autor res = *this;
        res.ratingMediu += adaos;
        if (res.ratingMediu > 10.0)
            res.ratingMediu = 10;
        return res;
    }

    friend Autor operator+(float adaos, const Autor& a);

    Autor operator-(float scadere) const {
        Autor res = *this;
        res.ratingMediu -= scadere;
        if (res.ratingMediu < 0.0)
            res.ratingMediu = 0.0;
        return res;
    }

    friend Autor operator-(float val, const Autor& a);

    // operatorul de egalitate ==
    bool operator==(const Autor& a) const {
        return (nume == a.nume) && (varsta == a.varsta);
    }

    // operatorul <
    bool operator<(const Autor& a) const {
        return ratingMediu < a.ratingMediu;
    }

    // Verificare daca autorul este eligibil pentru premiu (este contemporan si rating ul mediu este mai mare sau egal cu 7)
    bool esteEligibilPremiu() const {
        if (contemporan && ratingMediu >= 7) {
            return true;
        }
        return false;
    }

    // metoda virtuala pt verificare
    virtual void afiseazaTip() const {
        cout << "Tip: Autor Nespecific" << endl;
    }

};


Autor operator+(float adaos, const Autor& a) {
    return a + adaos;
}

Autor operator-(float val, const Autor& a) {
    Autor res = a;
    res.setRatingMediu(val - a.getRatingMediu());
    if (res.getRatingMediu() < 0)
        res.setRatingMediu(0);
    return res;
}

// CLASA AUTOR ROMAN
class AutorRoman: virtual public Autor {
private:
    string genRoman;
    int nrRomanePublicate;
    float pretMediuRoman;

public:
    // constructor fara parametri
    AutorRoman() : Autor(), genRoman("Necunoscut"), nrRomanePublicate(0), pretMediuRoman(0.0) {
        cout << "AutorRoman - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    AutorRoman(const string& nume, bool cont, int v, float rating, const string& gen, int nrRomane, float pret)
        : Autor(nume, cont, v, rating), genRoman(gen), nrRomanePublicate(nrRomane) {

        if (nrRomane < 0) throw invalid_argument("Numarul de romane nu poate fi negativ!");
        if (pret < 0) throw PretInvalidExceptie(pret);
        pretMediuRoman = pret;

        cout << "AutorRoman - constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri - nume, contemporan, gen romane
    AutorRoman(const string& nume, bool cont, const string& gen)
        : Autor(nume, cont), genRoman(gen), nrRomanePublicate(0), pretMediuRoman(0.0) {
        cout << "AutorRoman - constructor cu parametri - nume, contemporan, gen romane" << endl;
    }

    // constructor cu parametri - gen romane, nr romane publicate
    AutorRoman(const string& gen, int nr)
        : Autor(), genRoman(gen), pretMediuRoman(0.0) {
        if (nr < 0) throw invalid_argument("Numarul de romane nu poate fi negativ!");
        nrRomanePublicate = nr;
        cout << "AutorRoman - constructor cu parametri - gen romane, nr romane publicate" << endl;
    }

    // Constructor de copiere
    AutorRoman(const AutorRoman& ar)
        : Autor(ar), genRoman(ar.genRoman), nrRomanePublicate(ar.nrRomanePublicate), pretMediuRoman(ar.pretMediuRoman) {
        cout << "AutorRoman - constructor de copiere" << endl;
    }

    // Destructor
    ~AutorRoman() noexcept {
        cout << "AutorRoman - destructor" << endl;
    }

    // Operator de atribuire
    AutorRoman& operator=(const AutorRoman& ar) {
        if (this == &ar) return *this;

        Autor::operator=(ar);
        genRoman = ar.genRoman;
        nrRomanePublicate = ar.nrRomanePublicate;
        pretMediuRoman = ar.pretMediuRoman;
        return *this;
    }

    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const AutorRoman& ar) {
        os << (const Autor&) ar;
        os << "Gen roman: " << ar.genRoman << endl;
        os << "Nr romane publicate: " << ar.nrRomanePublicate << endl;
        os << "Pret mediu roman: " << ar.pretMediuRoman << endl;
        return os;
    }

    // citire
    friend istream& operator>>(istream& is, AutorRoman& ar) {
        is >> (Autor&)ar;
        if (is.peek() == '\n') {
            is.ignore();
        }
        cout << "Introduceti genul romanului: ";
        getline(is, ar.genRoman);

        cout << "Introduceti numarul de romane publicate: ";
        is >> ar.nrRomanePublicate;
        if (ar.nrRomanePublicate < 0) throw invalid_argument("Numarul de romane publicate nu poate fi negativ!");

        cout << "Introduceti pretul mediu al romanelor: ";
        is >> ar.pretMediuRoman;
        if (ar.pretMediuRoman < 0) throw PretInvalidExceptie(ar.pretMediuRoman);

        return is;
    }

    void afiseazaDetalii() const override {
        Autor::afiseazaDetalii(); // Afiseaza datele din baza
        cout << "Gen roman: " << genRoman << endl;
        cout << "Nr romane publicate: " << nrRomanePublicate << endl;
        cout << "Pret mediu roman: " << pretMediuRoman << " RON" << endl;
        cout << endl;
    }

    // setteri si getteri
    // getteri
    string getGenRoman() const {
        return genRoman;
    }
    int getNrRomanePublicate() const {
        return nrRomanePublicate;
    }
    float getPretMediuRoman() const {
        return pretMediuRoman;
    }

    // setteri
    void setGenRoman(const string& nouGen) {
        genRoman = nouGen;
    }
    void setNrRomanePublicate(int nouNr) {
        if (nouNr < 0)
            throw invalid_argument("Numarul de romane nu poate fi negativ!");
        nrRomanePublicate = nouNr;
    }
    void setPretMediuRoman(float pret) {
        if (pret < 0)
            throw PretInvalidExceptie(pret);
        pretMediuRoman = pret;
    }

    // operator de indexare
    string operator[](int index) const {
        switch (index) {
            case 0:
                return getNume();
            case 1:
                return genRoman;
            case 2:
                return getContemporan() ? "Contemporan" : "Non-contemporan";
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }

    // operator ++
    AutorRoman& operator++() {
        nrRomanePublicate++;
        return *this;
    }
    AutorRoman operator++(int) {
        AutorRoman temp(*this);
        ++(*this);
        return temp;
    }

    // operatori matematici
    AutorRoman operator+(float adaos) const {
        AutorRoman res = *this;
        res.pretMediuRoman += adaos;
        if (res.pretMediuRoman < 0)
            throw PretInvalidExceptie(res.pretMediuRoman);
        return res;
    }

    friend AutorRoman operator+(float adaos, const AutorRoman& a);



    AutorRoman operator-(float reducere) const {
        AutorRoman res = *this;
        res.pretMediuRoman -= reducere;
        if (res.pretMediuRoman < 0)
            throw PretInvalidExceptie(res.pretMediuRoman);
        return res;
    }

    // operator ==
    bool operator==(const AutorRoman& ar) const {
        return (getNume() == ar.getNume()) && (genRoman == ar.genRoman);
    }

    // operator <
    bool operator<(const AutorRoman& ar) const {
        return pretMediuRoman < ar.pretMediuRoman;
    }

    void afiseazaTip() const override {
        cout << "Tip: Autor de romane, gen roman:  " << genRoman << endl;
    }

    void aplicaReducere(float procent) {
        if (procent > 0 && procent <= 100) {
            float val = (procent / 100.0) * pretMediuRoman;
            *this = *this - val;
            cout << "A fost aplicata o reducere de " << procent << "% (" << val << " ). " <<
                "Noul pret este de " << pretMediuRoman << " RON. " << endl;
        }
        else
            throw invalid_argument("Procentul trebuie sa fie intre 0 si 100");
    }


};

AutorRoman operator+(float adaos, const AutorRoman& a) {
    return a + adaos;
}

// CLASA AUTOR POET
class AutorPoet : virtual public Autor {
private:
    string stilPoetic;
    int nrPoeziiPublicate;
    float pretMediuPoezie;

public:
    // constructor fara parametri
    AutorPoet() : Autor(), stilPoetic("Necunoscut"), nrPoeziiPublicate(0), pretMediuPoezie(0.0) {
        cout << "AutorPoet - contructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    AutorPoet(const string& nume, bool cont, int v, float rating,
              const string& stil, int nrPoezii, float pret)
        : Autor(nume, cont, v, rating), nrPoeziiPublicate(nrPoezii) {

        stilPoetic = stil.empty() ? "Necunoscut" : stil;

        if (nrPoezii < 0) throw invalid_argument("Numarul de poezii trebuie sa fie pozitiv");
        if (pret < 0) throw PretInvalidExceptie(pret);

        pretMediuPoezie = pret;
        cout << "AutorPoet - constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri - nume, contemporan si stil
    AutorPoet(const string& nume, bool cont, const string& stil)
        : Autor(nume, cont), stilPoetic(stil.empty() ? "Necunoscut" : stil), nrPoeziiPublicate(0), pretMediuPoezie(0.0) {
        cout << "AutorPoet - constructor cu parametri - nume, contemporan, stil" << endl;
    }

    // constructor cu parametri - nume, rating, nrpoeziipublicate
    AutorPoet(const string& nume, float rating, int nr)
        : Autor(nume, rating), stilPoetic("Necunoscut"), pretMediuPoezie(0.0) {

        if (nr < 0) throw invalid_argument("Numarul de poezii nu poate fi negativ!");
        nrPoeziiPublicate = nr;
        cout << "AutorPoet - constructor cu parametri - nume, rating si nr poezii publicate" << endl;
    }

    // constructor de copiere
    AutorPoet(const AutorPoet& ap)
        : Autor(ap), stilPoetic(ap.stilPoetic), nrPoeziiPublicate(ap.nrPoeziiPublicate), pretMediuPoezie(ap.pretMediuPoezie) {
        cout << "AutorPoet - constructor de copiere" << endl;
    }

    // destructor
    ~AutorPoet() noexcept {
        cout << "AutorPoet - destructor" << endl;
    }

    // operator de atribuire
    AutorPoet& operator=(const AutorPoet& ap) {
        if (this == &ap) return *this;

        Autor::operator=(ap);
        stilPoetic = ap.stilPoetic;
        nrPoeziiPublicate = ap.nrPoeziiPublicate;
        pretMediuPoezie = ap.pretMediuPoezie;
        return *this;
    }

    // setteri si getteri
    // getteri
    string getStilPoetic() const {
        return stilPoetic;
    }
    int getNrPoeziiPublicate() const {
        return nrPoeziiPublicate;
    }
    float getPretMediuPoezie() const {
        return pretMediuPoezie;
    }

    // setteri
    void setStilPoetic(const string& nouStil) {
        stilPoetic = nouStil;
    }
    void setNrPoeziiPublicate(int nr) {
        if (nr < 0)
            throw invalid_argument("Numarul de poezii nu poate fi negativ!");
        nrPoeziiPublicate = nr;
    }
    void setPretMediuPoezie(float pret) {
        if (pret < 0)
            throw PretInvalidExceptie(pret);
        pretMediuPoezie = pret;
    }

    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const AutorPoet& ap) {
        os << (const Autor&)ap;
        os << "Stil poetic: " << ap.stilPoetic << endl;
        os << "Nr. poezii publicste: " << ap.nrPoeziiPublicate << endl;
        os << "Pret mediu poezie: " << ap.pretMediuPoezie << " RON" << endl;
        return os;
    }

    // citire
    friend istream& operator>>(istream& is, AutorPoet& ap) {
        is >> (Autor&)ap;
        if (is.peek() == '\n')
            is.ignore();
        cout << "Inroduceti stilul poetic (ex: Sonete, Vers Liber): ";
        getline(is, ap.stilPoetic);

        cout << "Introduceti numarul de poezii publicate: ";
        is >> ap.nrPoeziiPublicate;
        if (ap.nrPoeziiPublicate < 0)
            throw invalid_argument("Numarul de poaezii nu poate fi negativ!");

        cout << "Introduceti pretul mediu al unei carti de poezii: ";
        is >> ap.pretMediuPoezie;
        if (ap.pretMediuPoezie < 0)
            throw PretInvalidExceptie(ap.pretMediuPoezie);

        return is;
    }

    void afiseazaDetalii() const override {
        Autor::afiseazaDetalii();
        cout << "Stil poetic: " << stilPoetic << endl;
        cout << "Nr poezii publicate: " << nrPoeziiPublicate << endl;
        cout << "Pret mediu poezie: " << pretMediuPoezie << " RON" << endl;
        cout << endl;
    }

    // operator de indexare
    string operator[](int index) const {
        switch (index) {
            case 0:
                return getNume();
            case 1:
                return stilPoetic;
            case 2:
                return getContemporan() ? "Contemporan" : "Non-contemporan";
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }

    // operator ++
    AutorPoet& operator++() {
        nrPoeziiPublicate++;
        return *this;
    }

    AutorPoet operator++(int) {
        AutorPoet temp(*this);
        ++(*this);
        return temp;
    }

    // operatori matematici
    AutorPoet operator+(float adaos) const {
        AutorPoet res = *this;
        res.pretMediuPoezie += adaos;
        if (res.pretMediuPoezie < 0)
            throw PretInvalidExceptie(res.pretMediuPoezie);
        return res;
    }

    friend AutorPoet operator+(float adaos, const AutorPoet& a);



    AutorPoet operator-(float reducere) const {
        AutorPoet res = *this;
        res.pretMediuPoezie -= reducere;
        if (res.pretMediuPoezie < 0)
            throw PretInvalidExceptie(res.pretMediuPoezie);
        return res;
    }


    // operator ==
    bool operator==(const AutorPoet& ap) const {
        return (getNume() == ap.getNume())  && (stilPoetic == ap.stilPoetic);
    }

    // operatot <
    bool operator<(const AutorPoet& ap) const {
        return pretMediuPoezie < ap.pretMediuPoezie;
    }

    // polimorfism
    void afiseazaTip() const override {
        cout << "Tip: AUTOR DE POEZII (" << stilPoetic << ")" << endl;
    }

    void aplicaReducere(float procent) {
        if (procent > 0 && procent <= 100) {
            float val = (procent / 100.0) * pretMediuPoezie;
            *this = *this - val;
            cout << "A fost aplicata o reducere de " << procent << "% (" << val << " ). " <<
                "Noul pret este de " << pretMediuPoezie << " RON. " << endl;
        }
        else
            throw invalid_argument("Procentul de reducere trebuie sa fie intre 0 si 100!");
    }

};

AutorPoet operator+(float adaos, const AutorPoet& a) {
    return a + adaos;
}

// Clasa AutorUniversal mosteneste prin doua cai clasa Autor, anume prin
// AutorRoman si AutorPoet. Daca nu am folosi mostenire cu virtual public
// am avea doua copii ale clasei Autor in AutorUniversal.


// CLASA AUTOR UNIVERSAL
class AutorUniversal : public AutorRoman, public AutorPoet {
private:
    string edituraPrincipala;
    bool laureatInternational;
    int nrLimbiTraduse;

public:
    // constructor fara parametri
    AutorUniversal() : Autor(), AutorRoman(), AutorPoet(),
    edituraPrincipala("Necunoscuta"), laureatInternational(false), nrLimbiTraduse(0) {
        cout << "AutorUniversal - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    AutorUniversal(const string& nume, bool cont, int v, float rating,
                   const string& gen, int nrRomane, float pretRoman,
                   const string& stil, int nrPoezii, float pretPoezie,
                   const string& editura, bool laureat, int nrLimbi)
        : Autor(nume, cont, v, rating),
          AutorRoman(nume, cont, v, rating, gen, nrRomane, pretRoman),
          AutorPoet(nume, cont, v, rating, stil, nrPoezii, pretPoezie),
          edituraPrincipala(editura.empty() ? "Necunoscuta" : editura),
          laureatInternational(laureat) {

        if (nrLimbi < 0) throw invalid_argument("Numarul de limbi nu poate fi negativ!");
        nrLimbiTraduse = nrLimbi;
        cout << "AutorUniversal - constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri - 1
    AutorUniversal(const string& nume, bool cont, const string& gen, const string& stil, const string& editura)
        : Autor(nume, cont), AutorRoman(nume, cont, gen), AutorPoet(nume, cont, stil),
          edituraPrincipala(editura), laureatInternational(false), nrLimbiTraduse(0) {
        cout << "AutorUniversal - constructor" << endl;
    }

    // constructor cu parametri - 2
    AutorUniversal(const string& nume, float rating, const string& editura, int nrLimbi)
        : Autor(nume, rating), AutorRoman("Necunoscut", 0), AutorPoet(nume, rating, 0),
          edituraPrincipala(editura), laureatInternational(false) {

        if (nrLimbi < 0) throw invalid_argument("Numarul de limbi nu poate fi negativ!");
        nrLimbiTraduse = nrLimbi;
        cout << "AutorUniversal - constructor cu parametri" << endl;
    }

    // constructor de copiere
    AutorUniversal(const AutorUniversal& au)
        : Autor(au), AutorRoman(au), AutorPoet(au),
          edituraPrincipala(au.edituraPrincipala), laureatInternational(au.laureatInternational), nrLimbiTraduse(au.nrLimbiTraduse) {
        cout << "AutorUniversal - constructor de copiere" << endl;
    }

    // destructor
    ~AutorUniversal() noexcept {
        cout << "AutorUniversal - destructor" << endl;
    }

    // operator de atribuire
    AutorUniversal& operator=(const AutorUniversal& au) {
        if (this != &au) {
            AutorRoman::operator=(au);
            AutorPoet::operator=(au);

            edituraPrincipala = au.edituraPrincipala;
            laureatInternational = au.laureatInternational;
            nrLimbiTraduse = au.nrLimbiTraduse;
        }
        return *this;
    }

    // setteri si getteri
    // getteri
    string getEdituraPrincipala() const {
        return edituraPrincipala;
    }
    bool getLaureatInternational() const {
        return laureatInternational;
    }
    int getNrLimbiTraduse() const {
        return nrLimbiTraduse;
    }

    // setteri
    void setEdituraPrincipala(const string& editura) {
        edituraPrincipala = editura;
    }
    void setLaureatInternational(bool status) {
        laureatInternational = status;
    }
    void setNrLimbiTraduse(int nr) {
        if (nr < 0)
            throw invalid_argument("Numarul de limbi nu poate fi negativ!");
        nrLimbiTraduse = nr;
    }

    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const AutorUniversal& au) {
        os << (const AutorRoman&)au;
        os << "Stil poetic: " << au.getStilPoetic() << endl;
        os << "Nr poezii: " << au.getNrPoeziiPublicate() << endl;
        os << "Editura principala: " << au.getEdituraPrincipala() << endl;
        os << "Laureat international: " << (au.laureatInternational ? "DA" : "NU");
        os << "Tradus in: " << au.nrLimbiTraduse << " limbi" << endl;
        return os;
    }

    // citire
    friend istream& operator>>(istream& is, AutorUniversal& au) {
        is >> (AutorRoman&)au;
        string buffer;
        cout << "Introduceti stilul poetic: ";
        if (is.peek() == '\n') is.ignore();
        getline(is, buffer);
        au.setStilPoetic(buffer);

        int nrPoezii;
        cout << "Introduceti numarul de poezii: ";
        is >> nrPoezii;
        au.setNrPoeziiPublicate(nrPoezii);

        float pret;
        cout << "Introduceti pret mediu poezie: ";
        is >> pret;
        au.setPretMediuPoezie(pret);

        cout << "Introduceti editura principala: ";
        if (is.peek() == '\n') is.ignore();
        getline(is, buffer);
        au.setEdituraPrincipala(buffer);

        cout << "Este laureat international? (1 - DA, 0 - NU) ";
        is >> au.laureatInternational;

        cout << "In cate limbi este tradus? ";
        is >> au.nrLimbiTraduse;
        if (au.nrLimbiTraduse < 0)
            throw invalid_argument("Numarul de limbi nu poate fi negativ!");

        return is;
    }

    void afiseazaDetalii() const override {
        AutorRoman::afiseazaDetalii(); // Apeleaza pe cea din AutorRoman
        cout << "Stil poetic: " << getStilPoetic() << endl;
        cout << "Nr poezii: " << getNrPoeziiPublicate() << endl;
        cout << "Editura principala: " << getEdituraPrincipala() << endl;
        cout << "Laureat international: " << (getLaureatInternational() ? "DA" : "NU") << endl;
        cout << "Tradus in: " << getNrLimbiTraduse() << " limbi" << endl;
        cout << endl;
    }

    // operator []
    string operator[](int index) const {
        switch (index) {
            case 0:
                 return getNume();
            case 1:
                return edituraPrincipala;
            default:
                throw out_of_range("Eroare! Index invalid!");
        }
    }

    // operator ++
    AutorUniversal& operator++() {
        nrLimbiTraduse++;
        return *this;
    }
    AutorUniversal operator++(int) {
        AutorUniversal c(*this);
        nrLimbiTraduse++;
        return c;
    }

    // operatori matematici
    AutorUniversal operator+(int limbiNoi) const {
        AutorUniversal rez = *this;
        rez.nrLimbiTraduse += limbiNoi;
        if (rez.nrLimbiTraduse < 0) throw invalid_argument("Numarul de limbi nu poate fi negativ!");
        return rez;
    }

    friend AutorUniversal operator+(int limbiNoi, const AutorUniversal& au);

    AutorUniversal operator-(int limbiPierdute) const {
        AutorUniversal rez = *this;
        rez.nrLimbiTraduse -= limbiPierdute;
        if (rez.nrLimbiTraduse < 0)
            throw invalid_argument("Numarul de limbi nu poate fi negativ!");
        return rez;
    }

    // operatorul ==
    bool operator==(const AutorUniversal& au) const {
        return AutorRoman::operator==(au) && AutorPoet::operator==(au) && (nrLimbiTraduse == au.nrLimbiTraduse);
    }

    // operatorul <
    bool operator<(const AutorUniversal& au) const {
        return nrLimbiTraduse < au.nrLimbiTraduse;
    }


    void afiseazaTip() const override {
        cout << "Tip: AUTOR UNIVERSAL (Scrie romane si poezii)" << endl;
    }

    int getTotalLucrariPublicate() {
        return getNrRomanePublicate() + getNrPoeziiPublicate();
    }

};

AutorUniversal operator+(int limbiNoi, const AutorUniversal& au) {
    return au + limbiNoi;
}



// CLASA CLIENT
class Client : public IObject {
private:

    string nume;
    char tipClient; // Premium(P) sau Standand(S)
    bool abonatNewsletter;
    int varsta;
    long long numarTelefon;

public:
    // constructor fara parametri
    Client() : nume("Anonim"), tipClient('S'), abonatNewsletter(false), varsta(0), numarTelefon(0) {}

    // constructor cu toti parametrii
    Client(const string& n, char tip, bool abonat, int v, long long nr)
        :  nume(n), abonatNewsletter(abonat) {

        if (tip != 'p' && tip != 'P' && tip != 's' && tip != 'S')
            throw invalid_argument("Tip client invalid! (P pentru Premium, S pentru Standard)");
        tipClient = tip;

        if (v < 0) throw VarstaInvalidaExceptie(v);
        varsta = v;

        if (nr < 700000000 || nr > 799999999) throw TelefonInvalidExceptie(nr);
        numarTelefon = nr;
    }

    // constructor cu parametri - nume si telefon
    Client(const string& n, long long nr)
        :  nume(n), tipClient('S'), abonatNewsletter(false), varsta(0), numarTelefon(nr) {

        if (nr < 700000000 || nr > 799999999) throw TelefonInvalidExceptie(nr);
    }

    // Constructor cu parametri - nume si varsta
    Client(const string& n, int v)
        :  nume(n), tipClient('S'), abonatNewsletter(false), varsta(v), numarTelefon(0) {

        if (v < 0) throw VarstaInvalidaExceptie(v);
    }

    // Constructor de copiere
    Client(const Client& c)
        :  nume(c.nume), tipClient(c.tipClient),
          abonatNewsletter(c.abonatNewsletter), varsta(c.varsta), numarTelefon(c.numarTelefon) {}

    // Destructor
    ~Client() noexcept{
    }

    // Operator de atribuire
    Client& operator=(const Client& c) {
        if (this == &c) return *this;

        nume = c.nume;
        tipClient = c.tipClient;
        abonatNewsletter = c.abonatNewsletter;
        varsta = c.varsta;
        numarTelefon = c.numarTelefon;

        return *this;
    }

    string toString() const override {
        ostringstream oss;
        oss << "Client [ID=" << getId() << ", Nume: " << nume
            << ", Tip: " << tipClient << ", Newsletter: " << (abonatNewsletter ? "DA" : "NU")
            << ", Varsta: " << varsta << ", Telefon: " << numarTelefon << "]";
        return oss.str();
    }

    // operatori de stream

    // citire
    friend istream& operator>>(istream& is, Client& c) {
        cout << "Introduceti numele: ";
        if (is.peek() == '\n') is.ignore();
        getline(is, c.nume); // Citire corecta a numelui, inclusiv daca e format din mai multe cuvinte

        cout << "Introduceti tipul de client ('p' pentru Premium sau 's' pentru Standard): ";
        is >> c.tipClient;
        if (c.tipClient != 'p' && c.tipClient != 'P' && c.tipClient != 's' && c.tipClient != 'S')
            throw invalid_argument("Tip client invalid!");

        cout << "Clientul este abonat la newsletter? (1 pentru DA sau 0 pentru NU): ";
        is >> c.abonatNewsletter;

        cout << "Introduceti varsta: ";
        is >> c.varsta;
        if (c.varsta < 0) throw VarstaInvalidaExceptie(c.varsta);

        cout << "Introduceti numarul de telefon (07XXXXXXXX): ";
        is >> c.numarTelefon;
        if (c.numarTelefon < 700000000 || c.numarTelefon > 799999999) throw TelefonInvalidExceptie(c.numarTelefon);

        return is;
    }

    // setteri si getteri
    // getteri
    string getNume() const {
        return nume;
    }

    char getTipClient() const {
        return tipClient;
    }

    bool getAbonatNewsletter() const {
        return abonatNewsletter;
    }

    int getVarsta() const {
        return varsta;
    }

    long long getNumarTelefon() const {
        return numarTelefon;
    }


    // setteri
    void setNume(const string& nouNume) {
        nume = nouNume;
    }
    void setTipClient(char nouTip) {
        if (nouTip == 'p' || nouTip == 's'|| nouTip == 'P' || nouTip == 'S'){
            tipClient = nouTip;
            Logger::getInstance().log("Clientul cu ID-ul " + to_string(getId()) + " si-a schimbat tipul de client in tip  " + ((tipClient == 'p' || tipClient == 'P') ? "PREMIUM" : "STANDARD"));
        }
        else
            throw invalid_argument("Tip client invalid!  Poate fi doar P sau S");
    }

    void setAbonatNewsletter(bool nouAbonament) {
        abonatNewsletter = nouAbonament;
    }

    void setVarsta(int nouVarsta) {
        if (nouVarsta < 0)
            throw VarstaInvalidaExceptie(nouVarsta);
        varsta = nouVarsta;
    }

    void setNumarTelefon(long long nouTelefon) {
        if (nouTelefon >= 700000000 && nouTelefon < 800000000)
            numarTelefon = nouTelefon;
        else
            throw TelefonInvalidExceptie(nouTelefon);
    }

    // Supraincarcarea operatorilor

    // operatorul de indexare
    string operator[](int index) const {
        switch (index) {
            case 0:
                return nume;
            case 1:
                return ((tipClient == 'p' || tipClient == 'P' )? "Premium" : "Standard");
            default:
                throw out_of_range("Index invalid!");
        }
    }


    // operator ++
    Client& operator++() {
        varsta += 1;
        return *this;
    }
    Client operator++(int) {
        Client c(*this);
        ++(*this);
        return c;
    }

    // operatori matematici: + si -
    // Operatorul + (adaugare ani la varsta)
    Client operator+(int ani) const {
        Client res = *this;
        res.varsta += ani;
        if (res.varsta < 0)
            throw VarstaInvalidaExceptie(res.varsta);
        return res;
    }

    friend Client operator+(int ani, const Client& c);

    // Operatorul - (scadere ani)
    Client operator-(int dif) const{
        Client res = *this;
        res.varsta -= dif;
        if (res.varsta < 0)
            throw VarstaInvalidaExceptie(res.varsta);
        return res;

    }

    friend Client operator-(int ani, const Client& c);

    // operatorul de egalitate ==
    // Verifica daca doi clienti au acelasi nume si numar de telefon
    bool operator==(const Client& c) const{
        return (nume == c.nume) && (numarTelefon == c.numarTelefon);
    }

    // operatorul >
    // Verifica daca un client are o varsta mai mare decat altul
    bool operator>(const Client& c) const {
        return varsta > c.varsta;
    }

    // Verifica daca un client este fidel (este abonat la newsletter si are un abonament premium)
    bool esteClientfidel() const {
        return (abonatNewsletter == true) && (tipClient == 'P' || tipClient == 'p');
    }


};



Client operator+(int ani, const Client& c) {
    return c + ani;
}

Client operator-(int ani, const Client& c) {
    Client res = c;
    res.setVarsta(ani - c.getVarsta());
    return res;
}

// CLASA DATA
class Data {
private:
    int zi;
    int luna;
    int an;

public:
    // constructor fara parametri
    Data() : zi(1), luna(1), an(2000) {
        cout << "Data - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    Data(int z, int l, int a): an(a) {
        if (z < 1 || z > 31)
            throw invalid_argument("Ziua introdusa este invalida!");
        zi = z;
        if (l< 1 || l > 12)
            throw invalid_argument("Luna introdusa este invalida!");
        luna = l;
        cout << "Data - constructor cu toti parametrii" << endl;
    }

    // constructor cu parametri
    Data(int z, int l) : an(2026) {
        if (z < 1 || z > 31)
            throw invalid_argument("Ziua introdusa este invalida!");
        zi = z;
        if (l< 1 || l > 12)
            throw invalid_argument("Luna introdusa este invalida!");
        luna = l;
        cout << "Data - constructor cu parametri - zi si luna" << endl;
    }

    // constructor cu parametri
    Data(int z) :  luna(1), an(2026) {
        if (z < 1 || z > 31)
            throw invalid_argument("Ziua introdusa este invalida!");
        zi = z;
        cout << "Data - constructor cu parametri - zi" << endl;
    }

    // constructor pt parsare string in data
    Data(const string& dataFormatata) {
        if (dataFormatata.size() == 10 && dataFormatata[2] == '/' && dataFormatata[5] == '/') {
            try {
                zi = stoi(dataFormatata.substr(0, 2));
                luna = stoi(dataFormatata.substr(3, 2));
                an = stoi(dataFormatata.substr(6, 4));
            } catch (const exception& e) {
                throw invalid_argument("Eroare la parsarea datelor cu stoi!");
            }
        } else {
            throw invalid_argument("Format data invalid. Introduceti DD/MM/YYYY.");
        }
        cout << "Data - constructor de parsare din string" << endl;
    }

    // constructcor de copiere
    Data(const Data& d):
    zi(d.zi), luna(d.luna), an(d.an) {
        cout << "Data - constructor de copiere" << endl;
    }

    bool esteAnBisect() const {
        return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
    }

    // destructor
    ~Data() noexcept{
        cout << "Data - destructor" << endl;
    }

    // operator de atribuire
    Data& operator=(const Data& d) {
        if (this != &d) {
            zi = d.zi;
            luna = d.luna;
            an = d.an;
        }
        return *this;
    }

    // setteri si getteri
    // getteri
    int getZi() const {
        return zi;
    }
    int getLuna() const {
        return luna;
    }
    int getAn() const {
        return an;
    }
    // setteri
    void setZi(int z) {
        if (z < 1 || z > 31)
            throw invalid_argument("Ziua introdusa este invalida!");
        zi = z;
    }
    void setLuna(int l) {
        if (l < 1 || l > 12)
            throw invalid_argument("Luna introdusa este invalida!");
        luna = l;
    }
    void setAnul(int a) {
        an = a;
    }

    // operatori de stream
    // afisare
    friend ostream& operator<<(ostream& os, const Data& d) {
        os << (d.zi < 10 ? "0" : "") << d.zi << "/" << (d.luna < 10 ? "0" : "")
        << d.luna << "/" << d.an;
        return os;
    }

    //citire
    friend istream& operator>>(istream& is, Data& d) {
        cout << "Introduceti ziua: "; is >> d.zi;
        if (d.zi < 1 || d.zi > 31)
            throw invalid_argument("Ziua introdusa este invalida!");
        cout << "Introduceti luna: "; is >> d.luna;
        if (d.luna < 1 || d.luna > 12)
            throw invalid_argument("Luna introdusa este invalida!");
        cout << "Introduceti anul: "; is >> d.an;
        return is;
    }

    // operatorul de indexare []
int operator[](int index) const {
    switch (index) {
        case 0:
            return zi;
        case 1:
            return luna;
        case 2:
            return an;
        default:
            throw out_of_range("Index invalid!");
    }
}

    // operatorul ++
    Data& operator++() {
        zi++;
        return *this;
    }
    Data operator++(int) {
        Data temp = *this;
        zi++;
        return temp;
    }

    // operatori matematici
    Data operator+(int zile) const {
        Data t = *this;
        t.zi += zile;
        return t;
    }
    friend Data operator+(int zile, const Data& d);


    Data operator-(int zile) const {
        Data t = *this;
        t.zi -= zile;
        return t;
    }

    // operatorul ==
    bool operator==(const Data& d) const {
        return (zi == d.zi) && (luna == d.luna) && (an == d.an);
    }

    // operatorul <
    bool operator<(const Data& d) const {
        if (an != d.an)
            return an < d.an;
        if (luna != d.luna)
            return luna < d.luna;
        return zi < d.zi;
    }

    string toString() const {
        return (zi < 10 ? "0" : "") + to_string(zi) + "/" +
               (luna < 10 ? "0" : "") + to_string(luna) + "/" +
               to_string(an);
    }


};

Data operator+(int zile, const Data& d) {
    return d + zile;
}


// CLASA COMANDA
class Comanda : public IObject {
private:

    Data dataEmiterii;
    vector<int> idCartiComandate;
    float pretTotal;
    bool livrata;

public:
    // constructor fara parametri
    Comanda() :  dataEmiterii(), pretTotal(0.0),
                livrata(false) {
        cout << "Comanda - constructor fara parametri" << endl;
    }

    // constructor cu toti parametrii
    Comanda(const Data& d,const vector<int>& ids,float total, bool status)
        :  dataEmiterii(d), idCartiComandate(ids), livrata(status) {

        cout << "Comanda - constructor cu toti parametrii" << endl;
        if (total < 0)
            throw PretInvalidExceptie(total);
        pretTotal = total;

    }

    // constructor cu parametri - data
    Comanda(int z, int l, int a) :dataEmiterii(z, l, a) ,pretTotal(0.0),
    livrata(false) {
        cout << "Comanda - constructor cu parametri - data" << endl;
    }

    // constructor cu parametri - data si pret
    Comanda(int z, int l, int a, float pret)
        : dataEmiterii(z, l, a) , livrata(false) {
        cout << "Comanda - constructor cu parametri - data si pret" << endl;
        if (pret < 0)
            throw PretInvalidExceptie(pret);
        pretTotal = pret;
    }

    // contructor de copiere
    Comanda(const Comanda& c)
    : dataEmiterii(c.dataEmiterii),
      idCartiComandate(c.idCartiComandate), pretTotal(c.pretTotal), livrata(c.livrata) {
        cout << "Comanda - constructor de copiere" << endl;
        // Vectorul apeleaza automat constructorul sau de copiere
    }

    // destructor
    ~Comanda() noexcept{
        // nu mai e nevoie de delete[]
        cout << "Comanda - destructor" << endl;
    }

    // operator de atribuire =
    Comanda& operator=(const Comanda& c) {
        if (this== &c)
            return *this;

        dataEmiterii = c.dataEmiterii;
        pretTotal = c.pretTotal;
        livrata = c.livrata;
        idCartiComandate = c.idCartiComandate;
        return *this;
    }


    // operatori de stream
    // citire
    friend istream& operator>>(istream& is, Comanda& c) {
        cout << "Introduceti data comenzii: " << endl;
        is >> c.dataEmiterii;

        int nrCarti;
        cout << "Introduceti numarul de carti: ";
        is >> nrCarti;
        if (nrCarti < 0)
            throw invalid_argument("Numarul de carti nu poate fi negativ!");

        c.idCartiComandate.clear();

        if (nrCarti > 0) {
            for (int i = 0; i < nrCarti; i++) {
                int id;
                cout << "Introduceti ID carte " << i + 1 << ": ";
                is >> id;
                c.idCartiComandate.push_back(id);
            }
        }
        cout << "Pret total: ";
        is >> c.pretTotal;
        if (c.pretTotal < 0)
            throw PretInvalidExceptie(c.pretTotal);
        cout << " este livrata? (Introduceti 1 pentru DA sau 0 pentru NU)";
        is >> c.livrata;

        return is;
    }

    string toString() const {
        string cartiStr = "";
        for (int id : idCartiComandate) cartiStr += to_string(id) + " ";
        return "Comanda [ID: " + to_string(getId()) + "] | Data: " + dataEmiterii.toString() +
               " | Carti(ID): [" + cartiStr + "] | Total: " + to_string(pretTotal) + " RON" +
               " | Livrata: " + (livrata ? "DA" : "NU");
    }

    // getteri si setteri
    // getteri
    int getNrCarti() const {
        return idCartiComandate.size();
    }
    float getPretTotal() const {
        return pretTotal;
    }
    bool getLivrata() const {
        return livrata;
    }
    Data getDataComanda() const {
        return dataEmiterii;
    }
    const vector<int>& getIdCartiComandate() const {
        return idCartiComandate;
    }
    // setteri
    void setPretTotal(float nouPret) {
        if (nouPret < 0)
            throw PretInvalidExceptie(nouPret);
        pretTotal = nouPret;
    }
    void setLivrata(bool status) {
        livrata = status;
        Logger::getInstance().log("Comanda cu ID-ul: " + to_string(getId()) + "si-a schimbat statusul in : " + (status? "LIVRATA" : "NELIVRATA"));
    }
    void setDataComanda(Data nouData) {
        dataEmiterii = nouData;
    }
    void setIdCartiComandate(const vector<int>& noileIdUri) {
        idCartiComandate = noileIdUri;
    }

    // operator de indexare
    int operator[](int index) const{
        if (index < 0 || index >= idCartiComandate.size())
            throw out_of_range("Index invalid!");
        return idCartiComandate[index];
    }

    // operator ++
    Comanda& operator++() {
        pretTotal += 15.0;
        return *this;
    }
    Comanda operator++(int) {
        Comanda c(*this);
        pretTotal += 15.0;
        return c;
    }

    // operatori matematici
    // operatorul +: se adauga un id nou
    Comanda operator+(int nouId) const {
        Comanda c = *this;
        c.idCartiComandate.push_back(nouId);
        return c;
    }
    friend Comanda operator+(int id, const Comanda& c) {
        return c + id;
    }

    // operatorul * : aplicarea unui multiplicator
    Comanda operator*(float factor) const {
        if (factor <= 0) {
            throw invalid_argument("Eroare! Factorul de multiplicare trebuie sa fie pozitiv!");
        }
        Comanda c = *this;
        c.pretTotal *= factor;
        return c;
    }
    friend Comanda operator*(float factor, const Comanda& c) {
        return c * factor;
    }

    // operatorul de egalitate ==
    bool operator==(const Comanda& c) const{
        if (!(dataEmiterii == c.dataEmiterii))
           return false;
        if (pretTotal != c.pretTotal)
            return false;
        if (livrata != c.livrata)
            return false;
        if (idCartiComandate != c.idCartiComandate)
            return false;
        return true;
    }

    // operatorul <
    bool operator<(const Comanda& c) const {
        return pretTotal < c.pretTotal;
    }

    void calculeazaTimpLivrare() const {
        if (livrata) {
            cout << "Comanda a fost deja livrata. " << endl;
        }
        else {
            int zileTimpLivrare = idCartiComandate.size()/5 + 1;
            cout << "Timpul estimat de livrare pentru comanda " << getId() << " este de " << zileTimpLivrare << " zile." << endl;
        }
    }
};

// clasa abstracta pentru ambalaj
class IAmbalaj {
public:
    virtual ~IAmbalaj(){}
    virtual void impacheteaza() const = 0;
};

// familia eco
class AmbalajEco : public IAmbalaj {
public:
    void impacheteaza() const override{
        cout << "Comanda impachetata in ambalaj reciclat" << endl;
    }
};

// familia premium
class AmbalajPremium : public IAmbalaj {
public:
    void impacheteaza() const override {
        cout << "Comanda impachetata in ambalaj premium" << endl;
    }
};

//  clasa abstracta pentru metoda de livrare
class ILivrare {
public:
    virtual ~ILivrare(){}
    virtual void expediaza() const = 0;
};

// familia eco
class LivrareEco : public ILivrare {
public:
    void expediaza() const override {
        cout << "Livrare standard prin posta" << endl;
    }
};

// familia premium
class LivrarePremium: public ILivrare {
    public:
    void expediaza() const override {
        cout << "Livrare prin curierat rapid" << endl;
    }
};

class IFabricaProcesare {
public:
    virtual ~IFabricaProcesare(){}
    virtual IAmbalaj* creeazaAmbalaj() const = 0;
    virtual ILivrare* creeazaLivrare() const = 0;
};

// fabrica eco
class FabricaEco : public IFabricaProcesare {
public:
    IAmbalaj* creeazaAmbalaj() const override {
        return new AmbalajEco();
    }
    ILivrare* creeazaLivrare() const override {
        return new LivrareEco();
    }
};

// fabrica premium
class FabricaPremium : public IFabricaProcesare {
public:
    IAmbalaj* creeazaAmbalaj() const override{
        return new AmbalajPremium();
    }
    ILivrare* creeazaLivrare() const override {
        return new LivrarePremium();
    }
};


// clientul fabricii
class ProcesareComanda {
private:
    IFabricaProcesare* fabrica;

public:
    ProcesareComanda(IFabricaProcesare* f) : fabrica(f){}

    void setFabrica(IFabricaProcesare* f) {
        fabrica = f;
    }

    void proceseazaLot(const list<int>& idComenzi) const {

        for_each(idComenzi.begin(), idComenzi.end(), [this](int id) {
            cout << endl << "Procesare Comanda cu ID-ul: " << id << endl;

            IAmbalaj* ambalaj = fabrica->creeazaAmbalaj();
            ILivrare* livrare = fabrica->creeazaLivrare();

            ambalaj->impacheteaza();
            livrare->expediaza();

            delete ambalaj;
            delete livrare;
        });
    }
};


class MeniuLibrarie {
private:
    // folosesc list pentru produse pentru ca avem complexitatea
    // O(1) la stergeri cand stim de pe ce pozitie stergem
    list<ProdusLibrarie*> inventarProduse;

    // folosesc vector pentru autori pentru ca avem  O(1) la accesarea prin index
    vector<Autor*> listaAutori;

    // folosesc  map pentru clienti pentru ca avem
    // cautare, adaugare si stergere in O(log n), fiind o cheie unica pentru fiecare
    map<int, Client*> listaClienti;

    vector<Comanda*> listaComenzi;
public:
    // constructor
    MeniuLibrarie(){}

    // destructor
    ~MeniuLibrarie() noexcept{
        for (auto p : inventarProduse) delete p;
        for (auto a : listaAutori) delete a;
        // structured bindings pentru a dezaloca pointerii din map
        for (auto const& [id, c] : listaClienti) delete c;
        for (auto c : listaComenzi) delete c;

        inventarProduse.clear();
        listaAutori.clear();
        listaClienti.clear();
        listaComenzi.clear();
    }

    void adaugaProdus() {
        int optiuneTip;
        cout << "Ce tip de produs doriti sa adaugati?" << endl;
        cout << "1 - Carte Standard" << endl;
        cout << "2 - Carte Editie Speciala" << endl;
        cout << "Optiune: ";
        cin >> optiuneTip;

        ProdusLibrarie* nou = nullptr;

        switch (optiuneTip) {
            case 1: {
                Carte* c = new Carte();
                cin >> *c;
                nou = c;
                break;
            }
            case 2: {
                CarteEditieSpeciala* cs = new CarteEditieSpeciala();
                cin >> *cs;
                nou = cs;
                break;
            }
            default: {
                throw out_of_range("Eroare! Optiune invalida!");
            }
        }
        inventarProduse.push_back(nou);
        cout << "Produs adaugat cu succes! ID: " << nou->getId() << endl;
    }

    void afiseazaProduse() const {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse in inventar. ");
        }
        int i = 1;
        // algoritmul for_each
        for_each(inventarProduse.begin(), inventarProduse.end(), [&i](ProdusLibrarie* p) {
            cout << "Produsul " << i++ << endl;
            // late binding
            cout << "Tip produs:(metoda virtuala) " << p->getTipProdus() << endl;
         //   const std::type_info& tipReal = typeid(*inventarProduse[i]);
        //    cout << "(cu typeinfo) Tipul real al obiectului este: " << tipReal.name() << endl;
            cout << "(typeid): " << typeid(*p).name() << endl;
            p->afiseazaDetalii();
            cout << "Impachetare speciala: " << (p->necesitaImpachetareSpeciala() ? "DA" : "NU") << endl;
            cout << "ID identificare: " << p->getId() << endl;

            CarteEditieSpeciala* cs = dynamic_cast<CarteEditieSpeciala*>(p);
            if (cs != nullptr) {
                if (cs->estePiesaDeColectieRara()) {
                    cout << "Acest produs este o piesa de colectie rara" << endl;
                }
            }
            cout << endl;
        });
    }

    void modificaProdus() {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse inregistrate pentru modificare!");
        }
        int id;
        cout << "Introduceti ID-ul produsului de modificat: ";
        cin >> id;

        // algoritmul find_if
        auto it = find_if(inventarProduse.begin(), inventarProduse.end(), [id](ProdusLibrarie* p) {
            return p->getId() == id;
        });

        if (it == inventarProduse.end())
            throw ProdusNegasitExceptie(id);
        ProdusLibrarie* prod = *it;

        // Folosesc dynamic_cast pentru a identifica tipul real al obiectului stocat in
        // pointerul de tip baza, anume carte sau carte editie speciala.
        // dynamic_cast verifica la runtime validitatea conversiei, prevenind accesarea memoriei obiectului
        // daca nu este de tipul dorit.
        // static_cast ar fi fortat conversia.

        CarteEditieSpeciala* cs = dynamic_cast<CarteEditieSpeciala*>(prod);
        Carte* c = dynamic_cast<Carte*>(prod);

        int optiune;
        do {
            cout << "\nMODIFICARE PRODUS (ID: " << prod->getId() << ")" << endl;
            cout << "1 - Modifica Pret" << endl;
            cout << "2 - Modifica Stoc" << endl;
            cout << "3 - Modifica Tara Origine" << endl;

            if (c != nullptr) {
                cout << "4 - Modifica Titlu" << endl;
                cout << "5 - Modifica Autor" << endl;
                cout << "6 - Modifica An Publicare" << endl;
            }

            if (cs != nullptr) {
                cout << "7 - Modifica Material Coperta" << endl;
                cout << "8 - Modifica Status Semnatura" << endl;
                cout << "9 - Modifica Nr. Ilustratii Extra" << endl;
            }

            cout << "0 - Inapoi la meniul principal" << endl;
            cout << "Introdu opriunea: ";
            cin >> optiune;
            try {
                switch (optiune) {
                    case 1: {
                        float p;
                        cout << "Introdu pretul nou: ";
                        cin >> p;
                        prod->setPret(p);
                        break;
                    }
                    case 2: {
                        int s;
                        cout << "Introdu stocul nou ";
                        cin >> s;
                        prod->setStoc(s);
                        break;
                    }
                    case 3: {
                        string nouaTara;
                        cout << "Introdu noua tara de origine: ";
                        if (cin.peek() == '\n')
                            cin.ignore();
                        getline(cin, nouaTara);
                        prod->setTaraOrigine(nouaTara);
                        break;
                    }
                    case 4: {
                        if (c) {
                            string nouTitlu;
                            cout << "Introdu noul titlu: ";
                            if (cin.peek() == '\n')
                                cin.ignore();
                            getline(cin, nouTitlu);
                            c->setTitlu(nouTitlu);
                        }
                        break;
                    }
                    case 5: {
                        if (c) {
                            string nouAutor;
                            cout << "Introduceti noul autor: ";
                            if (cin.peek() == '\n')
                                cin.ignore();
                            getline(cin, nouAutor);
                            c->setAutor(nouAutor);
                        }
                        break;
                    }
                    case 6: {
                        if (c) {
                            int an;
                            cout <<  "Introduceti noul an de publicare: ";
                            cin >> an;
                            c->setAnPublicare(an);
                        }
                        break;
                    }
                    case 7: {
                        if (cs) {
                            string nouMaterial;
                            cout << "Introduceti noul material pentru coperta: ";
                            if (cin.peek() == '\n')
                                cin.ignore();
                            getline(cin, nouMaterial);
                            cs->setMaterialCoperta(nouMaterial);
                        }
                        break;
                    }
                    case 8: {
                        if (cs) {
                            bool semnatura;
                            cout << "Contine semnatura? (1 - DA, 0 - NU)";
                            cin >> semnatura;
                            cs->setContineSemnatura(semnatura);
                        }
                        break;
                    }
                    case 9: {
                        if (cs) {
                            int nr;
                            cout <<"Introduceti noul nr de ilustratii extra: ";
                            cin >> nr;
                            cs->setNrIlustratiiExtra(nr);
                        }
                        break;
                    }
                    case 0:
                        break;
                    default:
                        throw out_of_range("Eroare! Optiune invalida!");
                }
            }
            catch (PretInvalidExceptie& e) {
                cout << endl << "PRET INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (StocInvalidExceptie& e) {
                cout << endl << "STOC INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (ProdusNegasitExceptie& e) {
                cout << endl << "PRODUS NEGASIT" << endl;
                cout << e.what() << endl;
            }

            catch (RatingInvalidExceptie& e) {
                cout << endl << "RATING INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (VarstaInvalidaExceptie& e) {
                cout << endl << "VARSTA INVALIDA" << endl;
                cout << e.what() << endl;
            }

            catch (TelefonInvalidExceptie& e) {
                cout << endl << "TELEFON INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (LibrarieExceptie& e) {
                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                cout << e.what() << endl;
            }
            catch (invalid_argument& e) {
                cout << endl << "INVALID ARGUMENT" << endl;
                cout << e.what() << endl;
            }

            catch (out_of_range& e) {
                cout << endl << "OUT OF RANGE" << endl;
                cout << e.what() << endl;
            }

            catch (runtime_error& e) {
                cout << endl << "EROARE DE RULARE" << endl;
                cout << e.what() << endl;
            }

            catch (...) {
                cout << endl << "EROARE NECUNOSCUTA" << endl;
            }
        } while (optiune != 0);

    }

    void stergeProdus() {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse!");
        }
        int id;
        cout << "Introduceti ID-ul produsului de sters: ";
        cin >> id;
        bool gasit = false;

        // metoda remove_if combinata cu lambda
        inventarProduse.remove_if([id, &gasit](ProdusLibrarie* p) {
            if (p->getId() == id) {
                delete p;
                gasit = true;
                return true;
            }
            return false;
        });

        if (!gasit)
            throw ProdusNegasitExceptie(id);
        else
            cout << "Produs sters cu succes!" << endl;
    }

    void aplicaDiscountProdus() {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse pentru a aplica discount.");
        }
        int id;
        cout <<"Introduceti ID-ul produsului la care doriti sa aplicati produsul: ";
        cin >> id;

        auto it = find_if(inventarProduse.begin(), inventarProduse.end(), [id](ProdusLibrarie* p) {
            return p->getId() == id;
        });
        if (it == inventarProduse.end()) {
            throw ProdusNegasitExceptie(id);
        }

        Carte* c = dynamic_cast<Carte*>(*it);

        if (c != nullptr) {
            float procent;
            cout << "Introduceti procentul de discount (ex 20 pentru 20%): ";
            cin >> procent;

            c->aplicaDiscount(procent);
            cout << endl;
        }
            else {
                cout << "Discountul poate fi aplicat doar pentru Carti!" << endl;
            }


    }

    void sorteazaProduseDupaPret() {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse inregistrate pentru sortare!");
        }
        inventarProduse.sort([](ProdusLibrarie* a, ProdusLibrarie* b) {
            return a->getPret() < b->getPret();
        });
        cout << "Produsele au fost sortate crescator dupa pret!" << endl;
        afiseazaProduse();
    }

    void filtreazaProduseInStoc() const {
        if (inventarProduse.empty()) {
            throw runtime_error("Nu exista produse inregistrate!");
        }
        cout << "Produse disponibile in stoc: " << endl;
        int nr = 0;
        for_each(inventarProduse.begin(), inventarProduse.end(), [&nr](ProdusLibrarie* p) {
            if (p->getStoc() > 0) {
                cout << "- [ID: " << p->getId() << "] " << p->getTipProdus()
                     << " | Stoc: " << p->getStoc() << " | Pret: " << p->getPret() << " RON" << endl;
                nr++;
            }
        });
        if (nr == 0)
            cout << "Nu exista niciun produs in stoc. " << endl;
    }

    void proceseazaComenzi() {
        if (listaComenzi.empty()) {
            throw runtime_error("Nu exista comenzi inregistrate!");
        }

        list<int> lotComenzi;
        for_each(listaComenzi.begin(), listaComenzi.end(), [&lotComenzi](Comanda* c) {
            if (!c->getLivrata()) {
                lotComenzi.push_back(c->getId());
            }
        });

        if (lotComenzi.empty()) {
            cout << "Toate comenzile sunt deja livrate!" << endl;
            return;
        }

        cout << endl << "Avem " << lotComenzi.size() << " comenzi nelivrate. Alegeti metoda de procesare a lotului:" << endl;
        cout << "1 - Familia ECO (Ambalaj reciclat, Livrare posta)" << endl;
        cout << "2 - Familia PREMIUM (Ambalaj premium, Curierat rapid)" << endl;
        cout << "Optiune: ";

        int tip;
        cin >> tip;

        IFabricaProcesare* fabrica = nullptr;
        if (tip == 1) {
            fabrica = new FabricaEco();
        } else if (tip == 2) {
            fabrica = new FabricaPremium();
        } else {
            throw invalid_argument("Optiune de familie invalida! Trebuie sa fie 1 sau 2.");
        }

        ProcesareComanda procesator(fabrica);
        procesator.proceseazaLot(lotComenzi);

        for_each(listaComenzi.begin(), listaComenzi.end(), [](Comanda* c) {
            c->setLivrata(true);
        });

        delete fabrica;
        cout << "Toate comenzile din lot au fost procesate cu succes!" << endl;
    }


    void adaugaAutor() {
        cout << "Adaugare autor" << endl;
        cout << "1 - Autor nespecializat" << endl;
        cout << "2 - Autor poezii" << endl;
        cout << "3 - Autor romane" << endl;
        cout << "4 - Autor Universal" << endl;
        cout << "Introduceti cifra corespunzatoare tipului autorului: ";

        int tip;
        cin >> tip;
        Autor* nou = nullptr;

        switch (tip) {
            case 1: {
                Autor* a = new Autor;
                cin >> *a;
                nou = a;
                break;
            }
            case 2: {
                AutorRoman* ar = new AutorRoman;
                cin >> *ar;
                nou = ar;
                break;
            }
            case 3: {
                AutorPoet *ap = new AutorPoet;
                cin >> *ap;
                nou = ap;
                break;
            }
            case 4: {
                AutorUniversal* au = new AutorUniversal;
                cin >> *au;
                nou = au;
                break;
            }
            default: {
                throw out_of_range("Eroare! Optiune invalida!");
            }
        }

        listaAutori.push_back(nou);
        cout << "Autor adaugat cu ID " << nou->getId() << endl;
        }

    void afiseazaAutori() const {
        if (listaAutori.empty()) {
            throw runtime_error("Nu exista autori inregistrati. ");
        }
        cout << "LISTA AUTORI" << endl;
        for (auto a : listaAutori) {
            a->afiseazaTip();
            a->afiseazaDetalii();
            AutorUniversal* au = dynamic_cast<AutorUniversal*>(a);
            if (au) cout << "Total lucrari: " << au->getTotalLucrariPublicate() << endl;


        }
    }

    void modificaAutor(){
        if (listaAutori.empty()) {
            throw runtime_error("Nu exista autori inregistrati");
        }
        int id;
        cout << "Introduceti ID-ul autorului de modificat: ";
        cin >> id;
        // algoritmul find_if
        auto it = find_if(listaAutori.begin(), listaAutori.end(), [id](Autor* a)
           { return a->getId() == id; });
        if (it == listaAutori.end())
            throw ProdusNegasitExceptie(id);

        Autor* a = *it;

        int optiuneModificare;
        do {
            cout << "MODIFICARE AUTOR: " << a->getNume() << endl;
            cout << endl << "Introduceti cifra specifica optiunii dorite, apoi apasati ENTER." << endl << endl;
            cout << "1 - Modifica toate informatiile" << endl;
            cout << "2 - Modifica numele" << endl;
            cout << "3 - Modifica statusul (contemporan)" << endl;
            cout << "4 - Modifica varsta" << endl;
            cout << "5 - Modifica rating-ul mediu" << endl;
            cout << "0 - Inapoi" << endl;
            cout << "Alege optiunea: "<< endl;
            cin >> optiuneModificare;
            try {
                switch (optiuneModificare) {
                    case 1: {
                        cout << "Introduceti noile date pentru autor: " << endl;
                        cin >> *a;
                        cout << "Toate informatiile au fost actualizate!" << endl;
                        break;
                    }
                    case 2: {
                        string nouNume;
                        cout << "Introduceti noul nume: ";
                        if (cin.peek() == '\n')
                            cin.ignore();
                        getline(cin, nouNume);
                        a->setNume(nouNume);
                        cout << "Nume actualizat!" << endl;
                        break;
                    }
                    case 3: {
                        bool contemporan;
                        cout << "Este contemporan? (Introduceti 1 pentru DA sau 0 pentru NU): ";
                        cin >> contemporan;
                        a->setContemporan(contemporan);
                        cout << "Status actualizat!" << endl;
                        break;
                    }
                    case 4: {
                        int varsta;
                        cout << "Introduceti noua varsta: ";
                        cin >> varsta;
                        a->setVarsta(varsta);
                        cout << "Varsta actualizata!" << endl;
                        break;
                    }
                    case 5: {
                        float rating;
                        cout << "Introduceti noul rating: (0.0 - 10.0) ";
                        cin >> rating;
                        a->setRatingMediu(rating);
                        cout << "Rating actualizat!" << endl;
                        break;
                    }
                    case 0 : {
                        cout << "Inapoi la submeniul autori..." << endl;
                        break;
                    }
                    default:
                        throw out_of_range("Eroare! Optiune invalida!");
                }
            }
            catch (PretInvalidExceptie& e) {
                cout << endl << "PRET INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (StocInvalidExceptie& e) {
                cout << endl << "STOC INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (ProdusNegasitExceptie& e) {
                cout << endl << "PRODUS NEGASIT" << endl;
                cout << e.what() << endl;
            }

            catch (RatingInvalidExceptie& e) {
                cout << endl << "RATING INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (VarstaInvalidaExceptie& e) {
                cout << endl << "VARSTA INVALIDA" << endl;
                cout << e.what() << endl;
            }

            catch (TelefonInvalidExceptie& e) {
                cout << endl << "TELEFON INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (LibrarieExceptie& e) {
                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                cout << e.what() << endl;
            }
            catch (invalid_argument& e) {
                cout << endl << "INVALID ARGUMENT" << endl;
                cout << e.what() << endl;
            }

            catch (out_of_range& e) {
                cout << endl << "OUT OF RANGE" << endl;
                cout << e.what() << endl;
            }
            catch (runtime_error& e) {
                cout << endl << "EROARE DE RULARE" << endl;
                cout << e.what() << endl;
            }
            catch (...) {
                cout << endl << "EROARE NECUNOSCUTA" << endl;
            }

        } while (optiuneModificare != 0);

    }


    void stergeAutor() {
        if (listaAutori.empty()) {
            throw runtime_error("Nu exista autori inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul autorului de sters: ";
        cin >> id;

        bool gasit = false;
        for (auto& a : listaAutori) {
            if (a->getId() == id) {
                delete a;
                a = nullptr;
                gasit = true;
            }
        }
        if(!gasit)
            throw ProdusNegasitExceptie(id);

        //algoritm erase-remove_if folosit pentru vector
        listaAutori.erase(remove_if(listaAutori.begin(), listaAutori.end(), [](Autor* a) {
            return a == nullptr;
        }), listaAutori.end());
        cout << "Autor sters!" << endl;

    }

    void verificaEligibilitateAutor() const{
        if (listaAutori.empty()) {
            throw runtime_error("Nu exista autori inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul autorului: ";
        cin >> id;
        auto it = find_if(listaAutori.begin(), listaAutori.end(), [id](Autor* a) {
            return a->getId() == id;
        });
        if (it == listaAutori.end()) {
            throw ProdusNegasitExceptie(id);
        }
        if ((*it)->esteEligibilPremiu())
            cout << (*it)->getNume() << " ESTE eligibil!" << endl;
        else
            cout << (*it)->getNume() << " NU este eligibil." << endl;
    }

    void aplicaReducereAutor() {
        if (listaAutori.empty()) {
            throw runtime_error("Nu exista autori inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul autorului pentru care doriti sa aplicati reducerea: ";
        cin >> id;
        int index = -1;
        auto it = find_if(listaAutori.begin(), listaAutori.end(), [id](Autor* a) {
            return a->getId() == id;
        });
        if (it == listaAutori.end())
            throw ProdusNegasitExceptie(id);

        AutorRoman* ar = dynamic_cast<AutorRoman*>(*it);
        AutorPoet* ap = dynamic_cast<AutorPoet*>(*it);
        AutorUniversal* au = dynamic_cast<AutorUniversal*>(*it);

        if (ar != nullptr || ap != nullptr || au != nullptr) {
            float procent;
            cout << "Introduceti procentul de reducere (0-100): ";
            cin >> procent;
            if (au != nullptr) {
                cout << "Pentru sectiunea romane: ";
                au->AutorRoman::aplicaReducere(procent);
                cout << "Pret final: " << au->getPretMediuRoman() << " RON" << endl;

                cout << "Pentru sectiunea poezii: ";
                au->AutorPoet::aplicaReducere(procent);
                cout << "Pret final: " << au->getPretMediuPoezie() << " RON" << endl;
            }
            else if (ap != nullptr) {
                cout << "Pentru sectiunea poezii: ";
                ap->AutorPoet::aplicaReducere(procent);
                cout << "Pret final: " << au->getPretMediuPoezie() << " RON" << endl;
            }
            else if (ar != nullptr) {
                cout << "Pentru sectiunea romane: ";
                ar->AutorRoman::aplicaReducere(procent);
                cout << "Pret final: " << au->getPretMediuRoman() << " RON" << endl;
            }
        }
        else {
            throw invalid_argument("Reducerea se poate aplica doar pentru autori de romane, poeti sau scriitori universali!");
        }
    }


    void adaugaClient() {
        Client* nou = new Client();
        cin >> *nou;

        // inserare in map O(log n)
        listaClienti.insert({
            nou->getId(), nou});
        cout << "Client adaugat cu ID " << nou->getId() << endl;
    }

    void afiseazaClienti() const {
        if (listaClienti.empty()) throw runtime_error("Nu exista clienti inregistrati!");
        // iterare map cu structured bindings
        for (const auto& [id, c] : listaClienti) {
            cout << *c << endl;
        }
    }

    void modificaClient() {
        if (listaClienti.empty()) {
            throw runtime_error("Nu exista clienti inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul clientului de modificat: ";

        cin >> id;
        auto it = listaClienti.find(id);
        if (it == listaClienti.end())
            throw ProdusNegasitExceptie(id);
        Client* c = it->second;

        int optiuneModificare;
        do {
            cout << "MODIFICARE CLIENT: " << c->getNume() << endl;
            cout << endl << "Introduceti cifra corespunzatoare optiunii dorite apoi apasati ENTER." << endl << endl;
            cout << "1 - Modifica toate informatiile" << endl;
            cout << "2 - Modifica numele" << endl;
            cout << "3 - Modifica tipul de client (P - premium / S - standard)" << endl;
            cout << "4 - Modifica Statusul abonamentului la newsletter(1 - activ, 0 - inactiv)" << endl;
            cout << "5 - Modifica varsta" << endl;
            cout << "6 - Modifica numarul de telefon" << endl;
            cout << "0 - Iesire" << endl;
            cout << "Alege optiunea: ";
            cin >> optiuneModificare;

            try {
                switch (optiuneModificare) {
                    case 1: {
                        cout << "Introduceti noile date pentru client: " << endl;
                        cin >> *c;
                        cout << "Toate informatiile au fost actualizate! " << endl;
                        break;
                    }
                    case 2: {
                        string nouNume;
                        cout << "Introduceti noul nume: ";
                        if (cin.peek() == '\n')
                            cin.ignore();
                        getline(cin, nouNume);
                        c->setNume(nouNume);
                        cout << "Nume actualizat! ";
                        break;
                    }
                    case 3: {
                        char tip;
                        cout << "Introduceti tipul de client (Introduceti p pentru premium sau s pentru standard): ";
                        cin >> tip;
                        c->setTipClient(tip);
                        cout << "Tip client actualizat!" << endl;
                        break;
                    }
                    case 4: {
                        bool abonament;
                        cout << "Clientul este abonat la newsletter? (Introduceti 1 pentru DA sau 0 pentru NU)" << endl;
                        cin >> abonament;
                        c->setAbonatNewsletter(abonament);
                        cout << "Status abonament actualizat!" << endl;
                        break;
                    }
                    case 5: {
                        int varsta;
                        cout << "Introduceti noua varsta: ";
                        cin >> varsta;
                        c->setVarsta(varsta);
                        cout << "Varsta actualizata!" << endl;
                        break;
                    }
                    case 6: {
                        long long telefon;
                        cout << "Introduceti noul numar de telefon: ";
                        cin >> telefon;
                        c->setNumarTelefon(telefon);
                        cout << "Numar de telefon actualizat! " << endl;
                        break;
                    }
                    case 0: {
                        cout << "Inapoi la submeniul clienti..." << endl;
                        break;
                    }
                    default:
                        throw out_of_range("Eroare! Optiune invalida!");
                }
            }
            catch (PretInvalidExceptie& e) {
                cout << endl << "PRET INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (StocInvalidExceptie& e) {
                cout << endl << "STOC INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (ProdusNegasitExceptie& e) {
                cout << endl << "PRODUS NEGASIT" << endl;
                cout << e.what() << endl;
            }

            catch (RatingInvalidExceptie& e) {
                cout << endl << "RATING INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (VarstaInvalidaExceptie& e) {
                cout << endl << "VARSTA INVALIDA" << endl;
                cout << e.what() << endl;
            }

            catch (TelefonInvalidExceptie& e) {
                cout << endl << "TELEFON INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (LibrarieExceptie& e) {
                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                cout << e.what() << endl;
            }
            catch (invalid_argument& e) {
                cout << endl << "INVALID ARGUMENT" << endl;
                cout << e.what() << endl;
            }

            catch (out_of_range& e) {
                cout << endl << "OUT OF RANGE" << endl;
                cout << e.what() << endl;
            }

            catch (runtime_error& e) {
                cout << endl << "EROARE DE RULARE" << endl;
                cout << e.what() << endl;
            }

            catch (...) {
                cout << endl << "EROARE NECUNOSCUTA" << endl;
            }

        } while (optiuneModificare != 0);
    }

    void stergeClient() {
        if (listaClienti.empty()) {
            throw runtime_error("Nu exista clienti inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul clientului de sters: ";
        cin >> id;
        auto it = listaClienti.find(id);
        if (it != listaClienti.end()) {
            delete it->second;
            listaClienti.erase(it);
            cout << "Client sters!" << endl;
        } else {
            throw ProdusNegasitExceptie(id);
        }
    }

    void verificaFidelitateClient() const{
        if (listaClienti.empty()) {
            throw runtime_error("Nu exista clienti inregistrati!");
        }
        int id;
        cout << "Introduceti ID-ul clientului: ";
        cin >> id;
        auto it = listaClienti.find(id);
        if (it != listaClienti.end()) {
            if (it->second->esteClientfidel())
                cout << it->second->getNume() << " e fidel!" << endl;
            else cout << it->second->getNume() << " nu e fidel." << endl;
        } else
            throw ProdusNegasitExceptie(id);
    }

    void adaugaComanda() {
        if (inventarProduse.empty()) throw runtime_error("Nu exista carti in inventar!");
        Data data; cout << "Data (ZZ LL AAAA): "; cin >> data;
        bool status; cout << "Livrata(1/0): "; cin >> status;

        vector<int> tempID;
        float pret = 0.0;
        char adaugaCarte;

        do {
            int id; cout << "ID carte: "; cin >> id;
            auto it = find_if(inventarProduse.begin(), inventarProduse.end(), [id](ProdusLibrarie* p){ return p->getId() == id; });

            if (it != inventarProduse.end()) {
                Carte* carteGasita = dynamic_cast<Carte*>(*it);
                if (carteGasita != nullptr) {
                    int cantitate;
                    cout << carteGasita->getTitlu() << " - " << carteGasita->getPret() << " RON. Cantitate: ";
                    cin >> cantitate;
                    if (cantitate > 0) {
                        for (int k = 0; k < cantitate; k++) tempID.push_back(id);
                        pret += (carteGasita->getPret() * cantitate);
                        cout << "Adaugate!" << endl;
                    } else throw invalid_argument("Cantitate invalida!");
                } else cout << "ID-ul apartine unui produs care nu e carte!" << endl;
            } else throw ProdusNegasitExceptie(id);

            cout << "Pret curent: " << pret << "\nAlta carte? (d/n): "; cin >> adaugaCarte;
        } while (adaugaCarte == 'd' || adaugaCarte == 'D');

        if (!tempID.empty()) {
            Comanda* nou = new Comanda(data, tempID, pret, status);
            listaComenzi.push_back(nou);
            cout << "Comanda inregistrata! ID: " << nou->getId() << endl;
        } else throw invalid_argument("Comanda nula!");
    }

    void afiseazaComenzi() {
        if (listaComenzi.empty()) {
            throw runtime_error("Nu exista comenzi inregistrate!");
        }
        for (auto c : listaComenzi) cout << *c << endl;
    }

    void modificaComanda() {
        if (listaComenzi.empty()) {
            throw runtime_error("Nu exista comenzi inregistrate. ");
        }
        int id;
        cout << "Introduceti ID-ul comenzii de modificat!";
        cin >> id;

        auto it = find_if(listaComenzi.begin(), listaComenzi.end(), [id](Comanda* c) {
            return c->getId() == id;
        });
        if(it == listaComenzi.end())
            throw ProdusNegasitExceptie(id);
        Comanda* c = *it;

        int optiuneModificare;
        do {
            cout << "Modificare Comanda cu ID-ul: " << c->getId() << endl;
            cout << endl << "Introduceti cifra corespunzatoare optiunii dorite, apoi apasati ENTER." << endl << endl;
            cout << "1 - Modifica data comenzii" << endl;
            cout << "2 - Modifica statusul comenzii" << endl;
            cout << "3 - Aplica taxa de livrare urgenta (+15 RON)" << endl;
            cout << "0 - Inapoi" << endl;
            cout << "Introdu optiunea : ";
            cin >> optiuneModificare;


            try {
                switch (optiuneModificare) {
                    case 1: {
                        Data dataNoua;
                        cout << "Introduceti noua data: (ZZ/LL/AAAA): ";
                        cin >> dataNoua;
                        c->setDataComanda(dataNoua);
                        cout << "Data comenzii a fost actualizata! ";
                        break;
                    }
                    case 2: {
                        bool status;
                        cout << "Este livrata? (Introduceti 1 pentru DA sau 0 pentru NU): ";
                        cin >> status;
                        c->setLivrata(status);
                        cout << "Status livrare actualizat!" << endl;
                        break;
                    }
                    case 3: {
                        ++(*c);
                        cout << "Taxa aplicata! Noul pret: " << c->getPretTotal() << " RON." << endl;
                        break;
                    }
                    case 0:
                        cout << "Inapoi la submeniul comenzi..." << endl;
                        break;
                    default:
                        throw out_of_range("Eroare! Optiune invalida!");
                }
            }
            catch (PretInvalidExceptie& e) {
                cout << endl << "PRET INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (StocInvalidExceptie& e) {
                cout << endl << "STOC INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (ProdusNegasitExceptie& e) {
                cout << endl << "PRODUS NEGASIT" << endl;
                cout << e.what() << endl;
            }

            catch (RatingInvalidExceptie& e) {
                cout << endl << "RATING INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (VarstaInvalidaExceptie& e) {
                cout << endl << "VARSTA INVALIDA" << endl;
                cout << e.what() << endl;
            }

            catch (TelefonInvalidExceptie& e) {
                cout << endl << "TELEFON INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (LibrarieExceptie& e) {
                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                cout << e.what() << endl;
            }
            catch (invalid_argument& e) {
                cout << endl << "INVALID ARGUMENT" << endl;
                cout << e.what() << endl;
            }

            catch (out_of_range& e) {
                cout << endl << "OUT OF RANGE" << endl;
                cout << e.what() << endl;
            }

            catch (runtime_error& e) {
                cout << endl << "EROARE DE RULARE" << endl;
                cout << e.what() << endl;
            }

            catch (...) {
                cout << endl << "EROARE NECUNOSCUTA" << endl;
            }

        } while (optiuneModificare != 0);
    }



    void stergeComanda() {
        if (listaComenzi.empty()) {
            throw runtime_error("Nu exista comenzi inregistrate!");
        }
        int id;
        cout << "Introduceti ID-ul comenzii de sters: ";
        cin >> id;
        bool gasit = false;
        for (auto& c : listaComenzi) {
            if (c->getId() == id)
                { delete c; c = nullptr; gasit = true; }
        }
        if(!gasit)
            throw ProdusNegasitExceptie(id);

        listaComenzi.erase(remove_if(listaComenzi.begin(), listaComenzi.end(), [](Comanda* c) {
            return c == nullptr;
        }), listaComenzi.end());
        cout << "Comanda stearsa!" << endl;
    }

    void estimeazaLivrareComanda() const{
        if (listaComenzi.empty()) {
            throw runtime_error("Nu exista comenzi inregistrate.");
        }
        int id;
        cout << "Introduceti ID-ul comenzii: ";
        cin >> id;
        auto it = find_if(listaComenzi.begin(), listaComenzi.end(), [id](Comanda* c) {
            return c->getId() == id;
        });
        if(it != listaComenzi.end())
            (*it)->calculeazaTimpLivrare();
        else
            throw ProdusNegasitExceptie(id);
    }

    void afiseazaStatisticiMagazin() const {
        cout << endl << "Statistici magazin: " << endl;
        // algoritmul count_if
        int nrPremium = count_if(listaClienti.begin(), listaClienti.end(), [](const auto& pereche) {
            return pereche.second->getTipClient() == 'P' || pereche.second->getTipClient() == 'p';
        });
        cout << "> Numar clienti PREMIUM in magazin: " << nrPremium << endl;

        // algoritmul any_of
        bool comenziRestante = any_of(listaComenzi.begin(), listaComenzi.end(), [](Comanda* c) {
            return !c->getLivrata();
        });
        cout << "> Status Comenzi: " << (comenziRestante ? "AVETI COMENZI NELIVRATE!" : "Toate comenzile sunt la zi.") << endl;

    }

    void pornesteMeniu() {
        int optiunePrincipala;
        do {
            cout << endl << "GESTIUNE LIBRARIE" << endl;
            cout << endl << "Apasati tasta corespunzatoare optiunii dorite, iar apoi ENTER." << endl << endl;
            cout << "1 - Gestiune carti" << endl;
            cout << "2 - Gestiune autori" << endl;
            cout << "3 - Gestiune clienti" << endl;
            cout << "4 - Gestiune comenzi" << endl;
            cout << "5 - Statistici magazin" << endl;
            cout << "6 - Afiseaza jurmal" << endl;
            cout << "0 - Iesire" << endl;
            cout << "Alege categoria: ";
            cin >> optiunePrincipala;

            try {
                switch (optiunePrincipala) {
                    case 1: {
                        int optiune;
                        do {
                            cout << endl << "SUBMENIU CARTI" << endl;
                            cout << endl << "Apasati tasta corespunzatoare optiunii dorite, iar apoi ENTER." << endl << endl;
                            cout << "1 - Adauga carte" << endl;
                            cout << "2 - Afiseaza carti " << endl;
                            cout << "3 - Modifica  carte" << endl;
                            cout << "4 - Sterge carte" << endl;
                            cout << "5 - Aplica discount pentru o carte" << endl;
                            cout << "6 - Sortewaza cartile dupa pret" << endl;
                            cout << "7 - Filtreaza cartile - doar cele in stoc" << endl;
                            cout << "0 - Iesire" << endl;
                            cout << "Introdu optiunea: ";
                            cin >> optiune;

                            switch (optiune) {
                                case 1: adaugaProdus();
                                    break;
                                case 2: afiseazaProduse();
                                    break;
                                case 3: modificaProdus();
                                    break;
                                case 4: stergeProdus();
                                    break;
                                case 5: aplicaDiscountProdus();
                                    break;
                                case 6: sorteazaProduseDupaPret();
                                    break;
                                case 7:
                                    filtreazaProduseInStoc();
                                    break;
                                case 0: cout << "Iesire...";
                                    break;
                                default: throw out_of_range("Eroare! Optiune invalida!");
                            }
                        } while (optiune != 0);
                        break;
                    }
                    case 2: {
                        int optiune;
                        do {
                            cout << endl << "SUBMENIU AUTORI" << endl;
                            cout << endl << "Apasati tasta corespunzatoare optiunii dorite, iar apoi ENTER." << endl << endl;
                            cout << "1 - Adauga autor" << endl;
                            cout << "2 - Afiseaza autori" << endl;
                            cout << "3 - Modifica autor " << endl;
                            cout << "4 - Sterge autor" << endl;
                            cout << "5 - Verifica eligibilitate premiu" << endl;
                            cout << "6 - Aplica reducere pentru pretul mediu" << endl;
                            cout << "0 - Inapoi" << endl;
                            cout << "Introdu optiunea: " ;
                            cin >> optiune;

                            try {
                                switch (optiune) {
                                    case 1: adaugaAutor();
                                        break;
                                    case 2: afiseazaAutori();
                                        break;
                                    case 3: modificaAutor();
                                        break;
                                    case 4: stergeAutor();
                                        break;
                                    case 5: verificaEligibilitateAutor();
                                        break;
                                    case 6: aplicaReducereAutor();
                                        break;
                                    case 0: cout << "Iesire";
                                        break;
                                    default: throw out_of_range("Eroare! Optiune invalida!");
                                }
                            }
                            catch (PretInvalidExceptie& e) {
                                cout << endl << "PRET INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (StocInvalidExceptie& e) {
                                cout << endl << "STOC INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (ProdusNegasitExceptie& e) {
                                cout << endl << "PRODUS NEGASIT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (RatingInvalidExceptie& e) {
                                cout << endl << "RATING INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (VarstaInvalidaExceptie& e) {
                                cout << endl << "VARSTA INVALIDA" << endl;
                                cout << e.what() << endl;
                            }

                            catch (TelefonInvalidExceptie& e) {
                                cout << endl << "TELEFON INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (LibrarieExceptie& e) {
                                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                                cout << e.what() << endl;
                            }
                            catch (invalid_argument& e) {
                                cout << endl << "INVALID ARGUMENT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (out_of_range& e) {
                                cout << endl << "OUT OF RANGE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (runtime_error& e) {
                                cout << endl << "EROARE DE RULARE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (...) {
                                cout << endl << "EROARE NECUNOSCUTA" << endl;
                            }
                        } while (optiune != 0);
                        break;
                    }
                    case 3: {
                        int optiune;
                        do {
                            cout << endl << "SUBMENIU CLIENTI" << endl;
                            cout << endl << "Apasati tasta corespunzatoare optiunii dorite, iar apoi ENTER." << endl << endl;
                            cout << "1 - Adauga client" << endl;
                            cout << "2 - Afiseaza clienti" << endl;
                            cout << "3 - Modifica client" << endl;
                            cout << "4 - Sterge client" << endl;
                            cout << "5 - Verifica fidelitate client" << endl;
                            cout << "0 - Inapoi" << endl;
                            cout << "Alege optiunea: ";
                            cin >> optiune;

                            try {
                                switch (optiune) {
                                    case 1: adaugaClient();
                                        break;
                                    case 2: afiseazaClienti();
                                        break;
                                    case 3: modificaClient();
                                        break;
                                    case 4: stergeClient();
                                        break;
                                    case 5: verificaFidelitateClient();
                                        break;
                                    case 0: cout << "Iesire" << endl;
                                        break;
                                    default: throw out_of_range("Eroare! Optiune invalida!");
                                }
                            }
                            catch (PretInvalidExceptie& e) {
                                cout << endl << "PRET INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (StocInvalidExceptie& e) {
                                cout << endl << "STOC INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (ProdusNegasitExceptie& e) {
                                cout << endl << "PRODUS NEGASIT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (RatingInvalidExceptie& e) {
                                cout << endl << "RATING INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (VarstaInvalidaExceptie& e) {
                                cout << endl << "VARSTA INVALIDA" << endl;
                                cout << e.what() << endl;
                            }

                            catch (TelefonInvalidExceptie& e) {
                                cout << endl << "TELEFON INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (LibrarieExceptie& e) {
                                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                                cout << e.what() << endl;
                            }
                            catch (invalid_argument& e) {
                                cout << endl << "INVALID ARGUMENT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (out_of_range& e) {
                                cout << endl << "OUT OF RANGE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (runtime_error& e) {
                                cout << endl << "EROARE DE RULARE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (...) {
                                cout << endl << "EROARE NECUNOSCUTA" << endl;
                            }
                        } while (optiune != 0);
                        break;
                    }
                    case 4: {
                        int optiune;
                        do {
                            cout << endl << "SUBMENIU COMENZI" << endl;
                            cout << endl << "Apasati tasta corespunzatoare optiunii dorite, iar apoi ENTER." << endl << endl;
                            cout << "1 - Adauga comanda" << endl;
                            cout << "2 - Afiseaza comenzi" << endl;
                            cout << "3 - Modifica o comanda" << endl;
                            cout << "4 - Sterge comanda" << endl;
                            cout << "5 - Estimeaza timp de livrare" << endl;
                            cout << "6 - Proceseaza comenzile nelivrate" << endl;
                            cout << "0 - Inapoi" << endl;
                            cout << "Alege optiunea: ";
                            cin >> optiune;
                            try {
                                switch (optiune) {
                                    case 1: adaugaComanda();
                                        break;
                                    case 2: afiseazaComenzi();
                                        break;
                                    case 3: modificaComanda();
                                        break;
                                    case 4: stergeComanda();
                                        break;
                                    case 5: estimeazaLivrareComanda();
                                        break;
                                    case 6:
                                        proceseazaComenzi();
                                        break;
                                    case 0: cout << "Iesire" << endl;
                                        break;
                                    default:
                                        throw out_of_range("Eroare! Optiune invalida!");
                                }
                            }
                            catch (PretInvalidExceptie& e) {
                                cout << endl << "PRET INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (StocInvalidExceptie& e) {
                                cout << endl << "STOC INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (ProdusNegasitExceptie& e) {
                                cout << endl << "PRODUS NEGASIT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (RatingInvalidExceptie& e) {
                                cout << endl << "RATING INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (VarstaInvalidaExceptie& e) {
                                cout << endl << "VARSTA INVALIDA" << endl;
                                cout << e.what() << endl;
                            }

                            catch (TelefonInvalidExceptie& e) {
                                cout << endl << "TELEFON INVALID" << endl;
                                cout << e.what() << endl;
                            }

                            catch (LibrarieExceptie& e) {
                                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                                cout << e.what() << endl;
                            }
                            catch (invalid_argument& e) {
                                cout << endl << "INVALID ARGUMENT" << endl;
                                cout << e.what() << endl;
                            }

                            catch (out_of_range& e) {
                                cout << endl << "OUT OF RANGE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (runtime_error& e) {
                                cout << endl << "EROARE DE RULARE" << endl;
                                cout << e.what() << endl;
                            }

                            catch (...) {
                                cout << endl << "EROARE NECUNOSCUTA" << endl;
                            }
                        } while (optiune != 0);
                        break;
                    }
                    case 5: {
                        afiseazaStatisticiMagazin();
                        break;
                    }
                    case 6: {
                        Logger::getInstance().afiseazaJurnal();
                        break;
                    }
                    case 0:
                        cout << "Inchidere program" << endl;
                        break;
                    default:
                        throw out_of_range("Eroare! Optiune invalida!");
                }
            }
            catch (PretInvalidExceptie& e) {
                cout << endl << "PRET INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (StocInvalidExceptie& e) {
                cout << endl << "STOC INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (ProdusNegasitExceptie& e) {
                cout << endl << "PRODUS NEGASIT" << endl;
                cout << e.what() << endl;
            }

            catch (RatingInvalidExceptie& e) {
                cout << endl << "RATING INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (VarstaInvalidaExceptie& e) {
                cout << endl << "VARSTA INVALIDA" << endl;
                cout << e.what() << endl;
            }

            catch (TelefonInvalidExceptie& e) {
                cout << endl << "TELEFON INVALID" << endl;
                cout << e.what() << endl;
            }

            catch (LibrarieExceptie& e) {
                cout <<  endl << "EXCEPTIE LIBRARIE" << endl;
                cout << e.what() << endl;
            }
            catch (invalid_argument& e) {
                cout << endl << "INVALID ARGUMENT" << endl;
                cout << e.what() << endl;
            }

            catch (out_of_range& e) {
                cout << endl << "OUT OF RANGE" << endl;
                cout << e.what() << endl;
            }

            catch (runtime_error& e) {
                cout << endl << "EROARE DE RULARE" << endl;
                cout << e.what() << endl;
            }

            catch (...) {
                cout << endl << "EROARE NECUNOSCUTA" << endl;
            }

        } while (optiunePrincipala != 0);


        }


};

template<typename T, int N>
class Colectie {
private:
    T* elemente;
    int nrElemente;

public:
    // constructor
    Colectie(): nrElemente(0) {
        elemente = new T[N];
    }

    // constructor de copiere
    Colectie(const Colectie& c) {
        nrElemente = c.nrElemente;
        elemente = new T[N];

        for (int i = 0; i < nrElemente; i++) {
            elemente[i] = c.elemente[i];
        }
    }

    // operator =
    Colectie& operator=(const Colectie& c) {
        if (this != &c) {
            delete[] elemente;
            nrElemente = c.nrElemente;
            elemente = new T[N];
            for (int i = 0; i < nrElemente; i++) {
                elemente[i] = c.elemente[i];
            }
        }
            return *this;
    }

    // destructor
    ~Colectie() {
        delete[] elemente;
    }

    // adaugare element
    void adauga(const T& elem) {
        if (nrElemente >= N) {
            throw overflow_error("Eroare! Colectia este plina!");
        }
        elemente[nrElemente++] = elem;
    }

    // stergea ultimului element
    void sterge() {
        if (nrElemente <= 0) {
            throw underflow_error("Eroare! Colectia este goala!");
        }
        nrElemente--;
    }

    // operator []
    T& operator[](int index) {
        if (index < 0 || index >= nrElemente) {
            throw out_of_range("Index invalid!");
        }
        return elemente[index];
    }

    // operator[] constant
    const T& operator[](int index) const {
        if (index < 0 || index >= nrElemente) throw out_of_range("Index invalid!");
        return elemente[index];
    }

    int getNrElemente() const {
        return nrElemente;
    }

    int size() const {
        return nrElemente;
    }

    // afisare colectie
    void afiseaza() const {
        if (nrElemente == 0) {
            cout << "Colectia este goala!" << endl;
            return;
        }
        for (int i = 0; i < nrElemente; i++) {
            cout << elemente[i] << endl;
        }
    }

    // metoda template in clasa template
    template<typename U>
    void copiazaDinAltaColectie(const Colectie<U, N>& sursa) {
        if (sursa.size() > N) {
            throw overflow_error("Sursa are prea multe elemente.");
        }
        delete[] elemente;
        nrElemente = 0;
        for (int i = 0; i < sursa.size(); i++) {
            try {
                elemente[nrElemente++] = static_cast<T>(sursa[i]);
            }
            catch (const exception& e) {
                throw runtime_error("Eroare la conversie de tip");
            }
        }

    }
};

// functie template pentru sortare
template<typename T>
void sorteaza(vector<T>& v) {
    if (v.empty())
        return;
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[i]) {
                T aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

// specializarea functiei pt clasa Client pentru a putea avea sortare alfabetica
template<>
void sorteaza<Client>(vector<Client>& v) {
    if (v.empty())
        return;
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j].getNume() < v[i].getNume()) {
                Client aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

// functie template pentru cautare
template<typename T>
int cautaElement(const vector<T>& v, const T& element) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == element) {
            return i;
        }
    }
    return -1;
}

void demonstreazaStackUnwinding() {
    try {
        {
            Carte c("Maytreyi", 50.0);
            throw PretInvalidExceptie(-10.5);
        }
        cout << endl << "mesaj" << endl;
    } catch (const PretInvalidExceptie& e) {
        cout << "Exceptie prinsa: " << e.what() << endl;
    }
}


int main() {

    // demosntratie pentru constructori si destructori - mostenire si compunere
 //   CarteEditieSpeciala c1;
 //   Comanda com1(15, 5, 2026);

    // late binding
 //   CarteEditieSpeciala c2("Maitreyi", "Mircea Eliade", 1933, 50.0, 20, "Romania", "Piele naturala", true, 3);
 //   ProdusLibrarie* pb = &c2;
 //   cout << pb->getTipProdus() << endl;

    // destructor
 //   delete pb;

    // pentru a demonstra stack unwinding
    // exceptia este propagata pana este prinsa si sunt apelati toti destructorii obiectelor in ordine inversa
    demonstreazaStackUnwinding();

    Carte carte1("Ion", "Rebreanu", 1920, 45, 10, "Romania");
    Carte carte2("Morometii", "Preda", 1955, 50, 7, "Romania");
    Carte carte3("Baltagul", "Sadoveanu", 1930, 39, 5, "Romania");

    Client client1("Ana", 'P', true, 22, 712345678);
    Client client2("Maria", 'S', false, 30, 723456789);
    Client client3("George", 'P', true, 27, 734567891);

    // demonstratie utilizare template-uri
    Colectie<Carte, 5> colectieCarti;

    try {

        colectieCarti.adauga(carte1);
        colectieCarti.adauga(carte2);

        colectieCarti.afiseaza();

    }
    catch (exception& e) {
        cout << e.what() << endl;
    }

    // testare functie template - sortare

    vector<Carte> vectorCarti = { carte1, carte2, carte3 };

    sorteaza(vectorCarti);

    cout << "\nCarti sortate crescator dupa pret:\n";
    for (const auto& c : vectorCarti) {
        cout << c << endl;
    }

    // testare clasa template - cautare
    int poz = cautaElement(vectorCarti,  carte2);

    if (poz != -1) {
        cout << "Cartea a fost gasita pe pozitia: " << poz << endl;
    }
    else {
        cout << "Cartea nu exista!" << endl;
    }


    vector<Client> vectorClienti = { client1, client2, client3 };

    sorteaza(vectorClienti);

    cout << "\nClienti sortati alfabetic dupa nume:\n";
    for (const auto& c : vectorClienti) {
        cout << c << endl;
    }


    // demonstratie singleton
    Logger::getInstance().log("testare in main");
    // Logger logger2;
    // Logger logger3 = Logger::getInstance();
    Logger::getInstance().afiseazaJurnal();


    // demonstratie abstract factory
    FabricaEco fabricaEco;
    FabricaPremium fabricaPremium;

    list<int> lotComenzi = { 101, 102 };
    ProcesareComanda procesator(&fabricaEco);
    cout << "procesare eco" << endl;
    procesator.proceseazaLot(lotComenzi);

    procesator.setFabrica(&fabricaPremium);
    cout << "procesare premium" << endl;
    procesator.proceseazaLot(lotComenzi);




    MeniuLibrarie librariaMea;
    librariaMea.pornesteMeniu();
    return 0;
}


