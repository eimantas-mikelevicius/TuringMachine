#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

struct rules {
    string sena_bus;
    char senas_simb;
    char naujas_simb;
    char kryptis;
    string nauja_bus;
};

struct rules2 {
    string s_busena;
    char sim1, sim2;
    char n1, n2;
    char k1, k2;
    string nauja_bus;
};

int main(int argc, char* argv[]) {

    vector<rules> TMrules;
    vector<rules2> taisykles2;

    if (argc < 2) {// (1.txt) 2 argumentai
        cout << "Nepateiktas failo argumentas\n";
        return 1;
    }

    ifstream dokumentas(argv[1]);

    if (!dokumentas.is_open()) {
        cout << "Nepavyko atidaryti failo" << endl;
        return 1;
    }

    string head_state = "0";
    string tape;
    int head_pos = 0;
    int kiekjuost = 0;
    int zingsniai = 0;

    string s_busena = "0";
    string pjuost;
    string ajuost;
    int galv1 = 0, galv2 = 0;


    dokumentas >> kiekjuost;

    if (kiekjuost == 1)
    {
        dokumentas >> tape;
        dokumentas >> head_pos;
    }
    else if (kiekjuost == 2)
    {
        dokumentas >> pjuost;
        dokumentas >> ajuost;
        dokumentas >> galv1;
        dokumentas >> galv2;

    }

    if (kiekjuost == 1) {
        rules temp;
        while (dokumentas >> temp.sena_bus
            >> temp.senas_simb
            >> temp.naujas_simb
            >> temp.kryptis
            >> temp.nauja_bus) {
            TMrules.push_back(temp);
        }
    }

    if (kiekjuost == 2) {
        rules2 temp2;
        while (dokumentas >> temp2.s_busena
            >> temp2.sim1
            >> temp2.sim2
            >> temp2.n1
            >> temp2.n2
            >> temp2.k1
            >> temp2.k2
            >> temp2.nauja_bus) {
            taisykles2.push_back(temp2);
        }
    }
    dokumentas.close();

    bool halted = false;
    bool pauze = false;

    if (kiekjuost == 1) {
        while (!halted) {

            // pauze
            if (_kbhit()) {
                char klavisas = _getch();
                if (klavisas == 32) { // space is ASCII
                    pauze = !pauze;
                    if (pauze)
                        cout << "[PAUZE] Paspauskite SPACE, kad testi..." << endl;
                    else
                        cout << "[TESIAMA]" << endl;
                }
            }

            if (pauze) {
                Sleep(50);
                continue;
            }

            bool rule_found = false;
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////
            for (long long i = 0; i < TMrules.size(); i++) {

                if (TMrules[i].sena_bus == head_state &&
                    TMrules[i].senas_simb == tape[head_pos]) {

                    rule_found = true;

                    tape[head_pos] = TMrules[i].naujas_simb;

                    if (TMrules[i].kryptis == 'R' || TMrules[i].kryptis == 'r')
                        head_pos++;
                    else if (TMrules[i].kryptis == 'L' || TMrules[i].kryptis == 'l')
                        head_pos--;

                    head_state = TMrules[i].nauja_bus;

                    // ziuri ar halted ar ne
                    if (head_state == "H" || head_state == "halt" ||
                        head_state == "Halt" || head_state == "HALT" || head_state == "h" || head_state == "x" || head_state == "X") {
                        halted = true;
                        cout << "Programa sekmingai baige darba" << endl;
                        break;
                    }

                    zingsniai++;
                    //begalinis ciklas 
                    if (zingsniai > 1300) {
                        cout << "Galimas begalinis ciklas, ar norite testi? ";
                        string k;
                        cin >> k;
                        if (k == "NE" || k == "ne" || k == "Ne") return 0;
                        zingsniai = 0;
                    }
                   
                    // ekranas
                    system("cls");
                    cout << tape
                        << " || Busena: " << head_state
                        << " || Simbolis: " << tape[head_pos]
                        << " || Zingsnis: " << zingsniai << endl;

                    for (int j = 0; j < (int)tape.size(); j++) {
                        if (j == head_pos) cout << "^";
                        else cout << " ";
                    }
                    cout << endl;
                    //greitis
                    Sleep(2);
                    break;
                }
            }

            if (!rule_found) {
                cout << "Nebera tinkamu taisykliu. Sustojama" << endl;
                break;
            }
        }

    }

    if (kiekjuost == 2) {
        bool halted = false;
        bool pauze = false;

        while (!halted) {

            if (_kbhit()) {
                char klavisas = _getch();
                if (klavisas == 32) { // space is ASCII
                    pauze = !pauze;
                    if (pauze)
                        cout << "[PAUZE] Paspauskite SPACE, kad testi..." << endl;
                    else
                        cout << "[TESIAMA]" << endl;
                }
            }

            if (pauze) {
                Sleep(2);
                continue;
            }

            bool gera_taisykle = false;

            for (size_t i = 0; i < taisykles2.size(); i++) {
                if (taisykles2[i].s_busena == s_busena && taisykles2[i].sim1 == pjuost[galv1] && taisykles2[i].sim2 == ajuost[galv2]) {
                    gera_taisykle = true;

                    pjuost[galv1] = taisykles2[i].n1;
                    ajuost[galv2] = taisykles2[i].n2;

                    if (taisykles2[i].k1 == 'R' || taisykles2[i].k1 == 'r')
                        galv1++;
                    else if (taisykles2[i].k1 == 'L' || taisykles2[i].k1 == 'l')
                        galv1--;

                    if (taisykles2[i].k2 == 'R' || taisykles2[i].k2 == 'r')
                        galv2++;
                    else if (taisykles2[i].k2 == 'L' || taisykles2[i].k2 == 'l')
                        galv2--;

                    s_busena = taisykles2[i].nauja_bus;

                

                    if (s_busena == "done" || s_busena == "wrongInput" || s_busena == "wrongLenght" || s_busena == "emptyInput") {
                        halted = true;
                        cout << "Programa sekmingai baige darba" << endl;
                        break;
                    }

                    zingsniai++;

                    if (zingsniai > 1300) {
                        cout << "Galimas begalinis ciklas. Testi? (TAIP/NE): ";
                        string ats;
                        cin >> ats;
                        if (ats == "NE" || ats == "ne" || ats == "Ne") return 0;
                        zingsniai = 0;
                    }

                    system("cls");
                    cout << pjuost;
                    cout << " - Pirma juosta" << " | Simbolis: " << pjuost[galv1] << endl;
                    for (int j = 0; j < (int)pjuost.size(); j++) {
                        if (j == galv1) cout << "^";
                        else cout << " ";
                    }
                    cout << endl;
                    cout << ajuost;
                    cout << " - Antra juosta" << " | Simbolis: " << ajuost[galv2] << endl;
                    for (int j = 0; j < (int)ajuost.size(); j++) {
                        if (j == galv2) cout << "^";
                        else cout << " ";
                    }
                    cout << endl;
                    cout << "Busena: " << s_busena << " | Zingsnis: " << zingsniai << endl;   

                    Sleep(2);
                    break;
                }
            }
            if (!gera_taisykle) {
                cout << "Nebera tinkamu taisykliu. Sustojama" << endl;
                halted = true;
                break;
            }
          

        }
    }
    return 0;
}

    