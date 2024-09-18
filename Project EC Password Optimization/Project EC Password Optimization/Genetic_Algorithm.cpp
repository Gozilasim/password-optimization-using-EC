#include <iostream>
#include <cstdlib>
#include <ctime>
#include<cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <windows.h>
#include <winnt.h>
#include <fstream>
#include <cstring>
#include<vector>
#include <set>


void char_calc();
void initilaise();
void print();
void evaluation();
void fitness();
void linearRankingSelection();
void CrossOver();
void Mutation();
void survivalSelection();
void copyChromosome();
void calculateAverageFitness();
void recordBestFitness();
void ExportToCSVFile();

using namespace std;

const int POP_SIZE = 10;
const int GENE = 8;
char chromosome[POP_SIZE][GENE];
int total_charcs = 0;
const int Max_Generation =10 ;
double chromosomeWeights[POP_SIZE];
double chromosomePowers[POP_SIZE];
int characteristics[POP_SIZE];
double fitness_fx[POP_SIZE];
vector<double> AvgFitness;  
vector<double> BestFitness;

std::random_device rd;
std::mt19937 gen(rd());

ofstream averageNbestFitnessFile;
ofstream bestChromosomeFile;




const char englishDigits[] = "1234567890";
//uppercaseGreek = Α Β Γ Δ Ε Ζ Η Θ Ι Κ Λ Μ Ν Ξ Ο Π Ρ Σ Τ Υ Φ Χ Ψ Ω
const char uppercaseGreek[] = u8"\u0391\u0392\u0393\u0394\u0395\u0396\u0397\u0398\u0399\u039A\u039B\u039C\u039D\u039E\u039F\u03A0\u03A1\u03A3\u03A4\u03A5\u03A6\u03A7\u03A8\u03A9";
//lowercaseGreek = α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ σ τ υ φ χ ψ ω
const char lowercaseGreek[] = u8"\u03B1\u03B2\u03B3\u03B4\u03B5\u03B6\u03B7\u03B8\u03B9\u03BA\u03BB\u03BC\u03BD\u03BE\u03BF\u03C0\u03C1\u03C3\u03C4\u03C5\u03C6\u03C7\u03C8\u03C9";
const char uppercaseEnglish[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char lowercaseEnglish[] = "abcdefghijklmnopqrstuvwxyz";
const char symbols[] = "!@#$%^&*()_+-={}[]|\\:;<>,.?/~";
//uppercaseCyrillic = А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х 	Ц Ч Ш Щ Ъ Ы Ь Э Ю Я
const char uppercaseCyrillic[] = u8"\u0410\u0411\u0412\u0413\u0414\u0415\u0401\u0416\u0417\u0418\u0419\u041A\u041B\u041C\u041D\u041E\u041F\u0420\u0421\u0422\u0423\u0424\u0425\u0426\u0427\u0428\u0429\u042A\u042B\u042C\u042D\u042E\u042F";
//lowercaseCyrillic = а б в г д е ё ж з и й к л м н о п р с т у ф х 	ц ч ш щ ъ ы ь э ю я
const char lowercaseCyrillic[] = u8"\u0430\u0431\u0432\u0433\u0434\u0435\u0451\u0436\u0437\u0438\u0439\u043A\u043B\u043C\u043D\u043E\u043F\u0440\u0441\u0442\u0443\u0444\u0445\u0446\u0447\u0448\u0449\u044A\u044B\u044C\u044D\u044E\u044F";

string chromosme_Name[POP_SIZE][GENE];

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 
    bestChromosomeFile.open("Best_Chromosome.txt");
    
    SetConsoleTextAttribute(hConsole, 1);
    char_calc();
    cout << "\nInitialize :\n";
    initilaise();
    print();
    for (int gen = 0; gen < Max_Generation; gen++) {

        print();
        
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\n\nGeneration " << gen + 1 << ": " << endl;
        cout << "\nEvaluation :";
        evaluation();
        fitness();
        calculateAverageFitness();
        recordBestFitness();

        for (int i = 0; i < POP_SIZE / 2; i++) {
            SetConsoleTextAttribute(hConsole, 3);
            cout << "\nParent Selection";
            linearRankingSelection();
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\nCrossOver:\n";
            CrossOver();
            SetConsoleTextAttribute(hConsole, 5);
            cout << "\nMutation:\n";
            Mutation();
            SetConsoleTextAttribute(hConsole, 6);
            cout << "\nSurvivalSelection:\n";
            survivalSelection();

        }

        SetConsoleTextAttribute(hConsole, 8);
        cout << "\n\nCopyChromosome:\n";
        copyChromosome();
        
    }
    SetConsoleTextAttribute(hConsole, 7);


    bestChromosomeFile.close();
    ExportToCSVFile();
}




void char_calc()         // to get the total number of all charaters
{
    int a = size(englishDigits);
    int b = size(uppercaseGreek);
    int  c = size(lowercaseGreek);
    int d = size(uppercaseEnglish);
    int e = size(lowercaseEnglish);
    int f = size(uppercaseCyrillic);
    int g = size(lowercaseEnglish);
    int h = size(symbols);
    int total_ch = a + b + c + d + e + f + g + h;
    total_charcs = total_ch;


}

void initilaise()
{

    for (int k = 0; k < POP_SIZE; k++)
    {
        for (int i = 0; i < GENE; i++) {
            int arrayChoice = std::uniform_int_distribution<int>(0, 7)(gen);

            switch (arrayChoice) {
            case 0:
                chromosome[k][i] = englishDigits[std::rand() % 10];
                break;
            case 1:
                chromosome[k][i] = uppercaseCyrillic[std::rand() % 33];
                break;
            case 2:
                chromosome[k][i] = uppercaseGreek[std::rand() % 24];
                break;
            case 3:
                chromosome[k][i] = lowercaseGreek[std::rand() % 24];
                break;
            case 4:
                chromosome[k][i] = uppercaseEnglish[std::rand() % 26];
                break;
            case 5:
                chromosome[k][i] = lowercaseEnglish[std::rand() % 26];
                break;
            case 6:
                chromosome[k][i] = symbols[std::rand() % 30];
                break;
            case 7:
                chromosome[k][i] = lowercaseCyrillic[std::rand() % 33];
                break;
            }
        }
    }


}

float english = 4;
float cyrillic = 4;
float greek = 4;
float uppecase = 2;
float lowercase = 1;
float symbols_c = 7;
float digit = 8;

int count[POP_SIZE][GENE];

void print()
{
    for (int k = 0; k < POP_SIZE; k++)
    {
        cout << "Chromosome " << k << ": ";
        for (int i = 0; i < GENE; i++) {
            cout << chromosome[k][i];
        }
        cout << endl;
    }
}


// english = 3
// cyricllic = 4
// greek = 5
// + ((len - n) * 3) uppercase
// + ((len - n) * 2) lowercase
// +(n*4) numbers
// +(n*6) symbols

void evaluation()
{
    for (int i = 0; i < POP_SIZE; i++) {
        cout << "\nChromosome " << i << ":  ";
        

        for (int k = 0; k < GENE; k++) {
            cout << chromosome[i][k];
        }
        cout << endl;

        for (int j = 0; j < GENE; j++) {
            char currentChar = chromosome[i][j];

            if (strchr(englishDigits, currentChar) != nullptr) {
                chromosme_Name[i][j] = "Digit";
            }
            else if (strchr(uppercaseCyrillic, currentChar) != nullptr) {
                chromosme_Name[i][j] = "UpperCaseCyrillic";
            }
            else if (strchr(uppercaseGreek, currentChar) != nullptr) {
                chromosme_Name[i][j] = "uppercaseGreek";
            }
            else if (strchr(lowercaseGreek, currentChar) != nullptr) {
                chromosme_Name[i][j] = "lowercaseGreek";
            }
            else if (strchr(uppercaseEnglish, currentChar) != nullptr) {
                chromosme_Name[i][j] = "uppercaseEnglish";
            }
            else if (strchr(lowercaseEnglish, currentChar) != nullptr) {
                chromosme_Name[i][j] = "lowercaseEnglish";
            }
            else if (strchr(symbols, currentChar) != nullptr) {
                chromosme_Name[i][j] = "symbols";
            }
            else if (strchr(lowercaseCyrillic, currentChar) != nullptr) {
                chromosme_Name[i][j] = "lowercaseCyrillic";
            }
        }
    }

    for (int i = 0; i < POP_SIZE; i++) {
        double chromosomeWeight = 0.0;
        double chromosomePower = 0.0;
        int countDigit = 0;
        int countUpperCaseCyrillic = 0;
        int countUppercaseGreek = 0;
        int countLowercaseGreek = 0;
        int counntUppercaseEnglish = 0;
        int countLowercaseEnglish = 0;
        int countSymbols = 0;
        int countLowercaseCyrillic = 0;
        int countLowercase = 0;
        int countUppercase = 0;

        for (int j = 0; j < GENE; j++) {
            if (chromosme_Name[i][j] == "Digit") {
                countDigit += 1;
            }
            else if (chromosme_Name[i][j] == "UpperCaseCyrillic") {
                countUpperCaseCyrillic += 1;
                countUppercase += 1;
            }
            else if (chromosme_Name[i][j] == "uppercaseGreek") {
                countUppercaseGreek += 1;
                countUppercase += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseGreek") {
                countLowercaseGreek += 1;
                countLowercase += 1;
            }
            else if (chromosme_Name[i][j] == "uppercaseEnglish") {
                counntUppercaseEnglish += 1;
                countUppercase += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseEnglish") {
                countLowercaseEnglish += 1;
                countLowercase += 1;
            }
            else if (chromosme_Name[i][j] == "symbols") {
                countSymbols += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseCyrillic") {
                countLowercaseCyrillic += 1;
                countLowercase += 1;
            }

        }
        cout << "\n" << countDigit << " " << countUpperCaseCyrillic << " " << countUppercaseGreek << " " << countLowercaseGreek << " " << counntUppercaseEnglish << " " << countLowercaseEnglish << " " << countSymbols << " " << countLowercaseCyrillic<< " " << countLowercase <<" " << countUppercase << endl;

        if (countDigit > 2) {
            digit = 4;
        }
        else {
            digit = 8;
        }
        if (countUpperCaseCyrillic > 2 || countLowercaseCyrillic >2) {
            cyrillic = 1.7;
        }
        else {
            cyrillic = 4;
        }

        if (countUppercaseGreek > 2 || countLowercaseGreek >2) {
            greek = 1.5;
        }
        else {
            greek = 4;
        }


        if (counntUppercaseEnglish > 2 || countLowercaseEnglish >2) {
            english = 1.6;
        }
        else {
            english = 4;
        }

        if (countSymbols > 3) {
            symbols_c = 3.7;
        }
        else {
            symbols_c = 7;
        }
        if (countUppercase > 4) {
            uppecase = 1.5;
        }
        else {
            uppecase = 2;
        }
        if (countLowercase > 4) {
            lowercase = 0.5;
        }
        else {
            lowercase = 1;
        }

    
        for (int j = 0; j < GENE; j++) {
            char currentChar = chromosome[i][j];

       
            if (strchr(englishDigits, currentChar) != nullptr) {
                cout << "Digit (" << currentChar << "):\t\t\tIndividual weight: " << digit <<
                    "\tPower: " << digit << endl;
                chromosomeWeight += digit;
                chromosomePower += digit;
                //chromosme_Name[i][j] = "Digit";
               
            }
            else if (strchr(uppercaseCyrillic, currentChar) != nullptr) {
                cout << "Uppercase Cyrillic (" << currentChar << "):\t\tIndividual weight: " << cyrillic << 
                    "\tPower: " << cyrillic * uppecase << endl;
                chromosomeWeight += cyrillic;
                chromosomePower += cyrillic * uppecase;
                //chromosme_Name[i][j] = "UpperCaseCyrillic";
            }
            else if (strchr(uppercaseGreek, currentChar) != nullptr) {
                cout << "Uppercase Greek (" << currentChar << "):\t\tIndividual weight: " << greek 
                << "\tPower: " << greek * uppecase << endl;
                chromosomeWeight += greek;
                chromosomePower += greek * uppecase;
                //chromosme_Name[i][j] = "uppercaseGreek";
            }
            else if (strchr(lowercaseGreek, currentChar) != nullptr) {
                cout << "Lowercase Greek (" << currentChar << "):\t\tIndividual weight: " << greek << 
                "\tPower: " << greek * lowercase << endl;
                chromosomeWeight += greek;
                chromosomePower += greek * lowercase;
                //chromosme_Name[i][j] = "lowercaseGreek";
            }
            else if (strchr(uppercaseEnglish, currentChar) != nullptr) {
                cout << "Uppercase English (" << currentChar << "):\t\tIndividual weight: " << english << 
                "\tPower: " << english * uppecase << endl;
                chromosomeWeight += english;
                chromosomePower += english * uppecase;
                //chromosme_Name[i][j] = "uppercaseEnglish";
            }
            else if (strchr(lowercaseEnglish, currentChar) != nullptr) {
                cout << "Lowercase English (" << currentChar << "):\t\tIndividual weight: " << english <<
                "\tPower: " << english * lowercase << endl;
                chromosomeWeight += english;
                chromosomePower += english * lowercase;
                //chromosme_Name[i][j] = "lowercaseEnglish";
            }
            else if (strchr(symbols, currentChar) != nullptr) {
                cout << "Symbol (" << currentChar << "):\t\t\tIndividual weight: " << symbols_c <<
                 "\tPower: " << symbols_c << endl;
                chromosomeWeight += symbols_c;
                chromosomePower += symbols_c;
                //chromosme_Name[i][j] = "symbols";
            }
            else if (strchr(lowercaseCyrillic, currentChar) != nullptr) {
                cout << "Lowercase Cyrillic (" << currentChar << "):\t\tIndividual weight: " << cyrillic << 
                "  Power: " << cyrillic * lowercase << endl;
                chromosomeWeight += cyrillic;
                chromosomePower += cyrillic * lowercase;
                //chromosme_Name[i][j] = "lowercaseCyrillic";
            }
        }

        chromosomeWeights[i] = chromosomeWeight;
        chromosomePowers[i] = chromosomePower;
        cout << "\nTotal Weight: " << chromosomeWeight << endl;
        cout << "Total Power: " << chromosomePower << endl;
    }


}


void fitness()
{

    std::set<std::string> uniqueStrings;
    for (int i = 0; i < POP_SIZE; i++)
    {

        for (int j = 0; j < GENE; j++) {
            uniqueStrings.insert(chromosme_Name[i][j]);
        }

        int uniqueCount = uniqueStrings.size();
        cout << "|||||||||||||||||||||||Size " << uniqueCount;
        characteristics[i] = uniqueCount;
        uniqueStrings.clear();
    }

    /*
    for (int i = 0; i < POP_SIZE; i++)
    {
        int countDigit = 0;
        int countUpperCaseCyrillic = 0;
        int countUppercaseGreek = 0;
        int countLowercaseGreek = 0;
        int counntUppercaseEnglish = 0;
        int countLowercaseEnglish = 0;
        int countSymbols = 0;
        int countLowercaseCyrillic = 0;

        for (int j = 0; j < GENE; j++) {
            if (chromosme_Name[i][j] == "Digit") {
                countDigit += 1;
            }
            else if (chromosme_Name[i][j] == "UpperCaseCyrillic") {
                countUpperCaseCyrillic += 1;
            }
            else if (chromosme_Name[i][j] == "uppercaseGreek") {
                countUppercaseGreek += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseGreek") {
                countLowercaseGreek += 1;
            }
            else if (chromosme_Name[i][j] == "uppercaseEnglish") {
                counntUppercaseEnglish += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseEnglish") {
                countLowercaseEnglish += 1;
            }
            else if (chromosme_Name[i][j] == "symbols") {
                countSymbols += 1;
            }
            else if (chromosme_Name[i][j] == "lowercaseCyrillic") {
                countLowercaseCyrillic += 1;
            }

        }
        
    }
    */
        /*
        if (characteristics[i] <= 2) {
            
            if (countDigit >= 3 || countSymbols >= 3 || countUpperCaseCyrillic >= 3 || countUppercaseGreek >= 3 || countLowercaseGreek >= 3 || counntUppercaseEnglish >= 3 || countLowercaseEnglish >= 3 || countLowercaseCyrillic >= 3) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.8) + ((characteristics[i] / 8) * 0.8);
            }
            else if ((countUpperCaseCyrillic >= 5 || countLowercaseCyrillic >= 5) && (countDigit < 5 || countSymbols < 5 || countUppercaseGreek < 5 || countLowercaseGreek < 5 || counntUppercaseEnglish < 5 || countLowercaseEnglish < 5)) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.2) + ((characteristics[i] / 8) * 0.2);
            }

            
        }
        else if (characteristics[i] > 2 && characteristics[i] <= 4) {
            if (countDigit >= 3 || countSymbols >= 3 || countUpperCaseCyrillic >= 3 || countUppercaseGreek >= 3 || countLowercaseGreek >= 3 || counntUppercaseEnglish >= 3 || countLowercaseEnglish >= 3 || countLowercaseCyrillic >= 3) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.8) + ((characteristics[i] / 8) * 0.8);
            }
            else if ((countUpperCaseCyrillic >= 5 || countLowercaseCyrillic >= 5) && (countDigit < 5 || countSymbols < 5 || countUppercaseGreek < 5 || countLowercaseGreek < 5 || counntUppercaseEnglish < 5 || countLowercaseEnglish < 5)) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.4) + ((characteristics[i] / 8) * 0.4);
            }
        }
        else if (characteristics[i] > 4 && characteristics[i] <= 6) {
            if (countDigit >= 3 || countSymbols >= 3 || countUpperCaseCyrillic >= 3 || countUppercaseGreek >= 3 || countLowercaseGreek >= 3 || counntUppercaseEnglish >= 3 || countLowercaseEnglish >= 3 || countLowercaseCyrillic >= 3) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.6) + ((characteristics[i] / 8) * 0.6);
            }
            else if ((countUpperCaseCyrillic >= 5 || countLowercaseCyrillic >= 5) && (countDigit < 5 || countSymbols < 5 || countUppercaseGreek < 5 || countLowercaseGreek < 5 || counntUppercaseEnglish < 5 || countLowercaseEnglish < 5)) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.2) + ((characteristics[i] / 8) * 0.2);
            }
        }
        else if (characteristics[i] > 6 && characteristics[i] <= 8) {
            if (countDigit >= 3 || countSymbols >= 3 || countUpperCaseCyrillic >= 3 || countUppercaseGreek >= 3 || countLowercaseGreek >= 3 || counntUppercaseEnglish >= 3 || countLowercaseEnglish >= 3 || countLowercaseCyrillic >= 3) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.8) + ((characteristics[i] / 8) * 0.8);
            }
            else if ((countUpperCaseCyrillic >= 5 || countLowercaseCyrillic >= 5) && (countDigit < 5 || countSymbols < 5 || countUppercaseGreek < 5 || countLowercaseGreek < 5 || counntUppercaseEnglish < 5 || countLowercaseEnglish < 5)) {
                fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.8) + ((characteristics[i] / 8) * 0.8);
            }
        }

        
    }
    

    */
    for (int i = 0; i < POP_SIZE; i++) {
        if (characteristics[i] == 1) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.2) + ((characteristics[i] / 8) * 0.2);
        }
        else if (characteristics[i] == 2) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.3) + ((characteristics[i] / 8) * 0.3);
        }
        else if (characteristics[i] == 3) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.4) + ((characteristics[i] / 8) * 0.4);
        }
        else if (characteristics[i] == 4) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.5) + ((characteristics[i] / 8) * 0.5);
        }
        else if (characteristics[i] == 5) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.6) + ((characteristics[i] / 8) * 0.6);
        }
        else if (characteristics[i] == 6) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.65) + ((characteristics[i] / 8) * 0.65);
        }
        else if (characteristics[i] == 7) {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.7) + ((characteristics[i] / 8) * 0.7);
        }
        else {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.75) + ((characteristics[i] / 8) * 0.75);
        }
       
        

  
       /*

        if (chromosomePowers[i] > 100)//above moderate strength
        {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.5) + ((characteristics[i] / 8) * 0.5);
        }
        else
        {
            fitness_fx[i] = ((chromosomePowers[i] / 117) * 0.3) + ((characteristics[i] / 8) * 0.3);

        }
        */

    }
    for (int i = 0; i < POP_SIZE; i++)
    {
        cout << "\nChromosome " << i << "\ttotal weights: " << chromosomeWeights[i] <<"\ttotal power: "<<chromosomePowers[i] << "\t\tFitness : " << fitness_fx[i] << endl;
    }
}



/*
//Tournament Selection
char parent[2][GENE];

void parentSelection() {

    int player1, player2, player3;
    int indexParents[2];

    for (int i = 0; i < 2; i++) {

        player1 = rand() % POP_SIZE;            // Random select numbner for player 1

        do {
            player2 = rand() % POP_SIZE;            // Random select numbner for player 2
        } while (player1 == player2);

        do {
            player3 = rand() % POP_SIZE;            // Random select numbner for player 3
        } while (player3 == player2 && player3 == player1);


        if (fitness_fx[player1] >= fitness_fx[player2] && fitness_fx[player1] >= fitness_fx[player3]) {
            indexParents[i] = player1;
        }
        else if (fitness_fx[player2] >= fitness_fx[player1] && fitness_fx[player2] >= fitness_fx[player3]) {
            indexParents[i] = player2;
        }
        else {
            indexParents[i] = player3;
        }

        cout << "\n\t Player's index: " << player1 << " vs " << player2 << " vs " << player3;
        cout << "\n\t Fitness: " << fitness_fx[player1] << " vs " << fitness_fx[player2] << " vs " << fitness_fx[player3];
        cout << "\n\t Winner " << i << ": player " << indexParents[i] << endl;

    }

    for (int i = 0; i < 2; i++) {
        cout << "\n\tParent :" << i + 1 << "\t";
        for (int j = 0; j < GENE; j++) {
            parent[i][j] = chromosome[indexParents[i]][j];
            cout << parent[i][j];
        }
        cout << endl;
    }


}

*/


//linear ranking selection
const double pmin = 0.1;
const double pmax = 0.9;
int ranks[POP_SIZE];      // used for ranking the chromosome according the fitness function
char parent[2][GENE];       // parent data structure

void linearRankingSelection() {



    for (int i = 0; i < POP_SIZE; i++) {
        ranks[i] = i;
    }

    // based on ascending method
    std::sort(ranks, ranks + POP_SIZE, [](int a, int b) {
        return fitness_fx[a] < fitness_fx[b];
        });


    cout << "After sorting :" << endl;
    for (int i = 0; i < POP_SIZE; i++) {
        cout << "Chromosome :" << ranks[i] << endl;
    }

    //declare the probab array to store the probab value using formula
    double probabilities[POP_SIZE];

    for (int i = 0; i < POP_SIZE; i++) {
        probabilities[i] = pmin + (pmax - pmin) * (i - 1) / (POP_SIZE - 1);    // the lower ranking chromosome wil get the lower prob
    }


    cout << "\n\nProbability for each ranking " << endl;
    for (int i = 0; i < POP_SIZE; i++) {
        cout << probabilities[i] << endl;
    }
    cout << endl;

    // normalize the probability

    //  accumulate( first element of array,  last element in array   , initialize the value 0.0
    // to get the sum of the probability
    double psum = std::accumulate(probabilities, probabilities + POP_SIZE, 0.0);
    // normalize the probability
    for (int i = 0; i < POP_SIZE; i++) {
        probabilities[i] /= psum;
    }

    cout << "\n\nProbablity for each ranking with normalize , total = 1 " << endl;
    for (int i = 0; i < POP_SIZE; i++) {
        cout << probabilities[i] << endl;
    }

    // Build a roulette wheel selection pool   or  like linear 
    double wheel[POP_SIZE];                           // accumulate like cumulative frequency
    wheel[0] = probabilities[0];
    for (int i = 1; i < POP_SIZE; i++) {
        wheel[i] = wheel[i - 1] + probabilities[i];
    }
    cout << endl;

    cout << "\nWheel " << endl;
    for (int i = 0; i < POP_SIZE; i++) {
        cout << wheel[i] << endl;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    int indexParent[2];
    int testValue = -1;
    // select the two  parent by looping two time
    for (int i = 0; i < 2; i++) {
        double random_value;
        if (i == 0)
        {
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            random_value = dist(gen);
        }
        else {
            std::uniform_real_distribution<double> dist(0.0, 0.7);
            random_value = dist(gen);
        }

        cout << "\n\nRandom value: " << random_value << endl;

        int selectedIndex = std::distance(wheel, std::upper_bound(wheel, wheel + POP_SIZE, random_value));
        cout << "Seleected Index " << selectedIndex << endl;
        if (testValue == ranks[selectedIndex ])
        {
            cout << "Repeated" << endl;
            i -= 1;
            continue;
        }
        
        cout << "\nRank : " << selectedIndex << "\n\n";
        indexParent[i] = ranks[selectedIndex ];
        testValue = ranks[selectedIndex ];
        cout << "Parent " << i + 1 << ":  Chromosome " << indexParent[i] << "\tFitness :" << fitness_fx[indexParent[i]] << endl;


    }

    //copy selected chromosome into parent array
    for (int i = 0; i < 2; i++) {
        cout << "\n\tParent :" << i + 1 << "\t";
        for (int j = 0; j < GENE; j++) {
            parent[i][j] = chromosome[indexParent[i]][j];
            cout << parent[i][j] << " ";
        }
        cout << endl;
    }


}

//declare CROSSOVER_PROBABILITY as a constant
const double CO_PROBABILITY = 0.9;
//declare child data structure
char children[2][GENE];

void CrossOver() {
    double rNumber;
    //Copy both parent’s chromosome to children chromosomes
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < GENE; j++) {
            children[i][j] = parent[i][j];
        }
    }

    //Generate a random number from 0-1. Make sure it is real value data type
    rNumber = (rand() % 11) / 10.0;

    if (rNumber <= CO_PROBABILITY) {

        //generate a random crossover point
        int C_point = rand() % GENE;

        cout << "\n\tProbablility : " << rNumber;
        cout << "\n\n\t\t Crossover point: " << C_point;
        //Crossover parent 1 and parent 2 to produce the children
        int temp;
        for (int i = 0; i < 2; i++)
        {
            for (int j = C_point; j < GENE; j++) {

                if (i == 0) {
                    children[i][j] = parent[i + 1][j];
                }
                else {
                    children[i][j] = parent[i - 1][j];
                }

            }

        }

        //display children 1 & 2
        for (int i = 0; i < 2; i++) {
            cout << "\n\tChildren" << i + 1 << ":   ";
            for (int j = 0; j < GENE; j++)
            {
                cout << children[i][j] << " ";
            }
            cout << "\n";
        }


    }
    else {
        cout << "\n\n\t\tCrossOver not happened";
    }


}

const double MU_PROBABILITY = 0.1;

void Mutation() {
    float rNumber;
    int mutBit;
    char replace = '\0';   // used for store data
    for (int i = 0; i < 2; i++) {
        //Generate number from 0-1 (real values)
        rNumber = (rand() % 11) / 10.0;
        cout << "\n\tProbablility  " << i + 1 << " : " << rNumber;

        if (rNumber <= MU_PROBABILITY) {
            //generate a mutation bit
            mutBit = rand() % GENE;
            //Print the mutation bit
            cout << "\n\n\tMutation Bit : " << mutBit << endl;

            int arrayChoice = std::rand() % 8;

            switch (arrayChoice) {
            case 0:
                replace = englishDigits[std::rand() % 10];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 1:
                replace = uppercaseCyrillic[std::rand() % 33];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 2:
                replace = uppercaseGreek[std::rand() % 24];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 3:
                replace = lowercaseGreek[std::rand() % 24];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 4:
                replace = uppercaseEnglish[std::rand() % 26];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 5:
                replace = lowercaseEnglish[std::rand() % 26];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 6:
                replace = symbols[std::rand() % 30];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            case 7:
                replace = lowercaseCyrillic[std::rand() % 33];
                if (replace == children[i][mutBit])
                    i -= 1;                         // used for repeat
                else
                    children[i][mutBit] = replace;
                break;
            }
            cout << "\tReplace with " << replace << endl;
        }
        else {
            cout << "\n\n\t\t Mutation not happened\n\n";
        }

    }

    for (int i = 0; i < 2; i++) {
        cout << "\n\t\tChildren Mutated:   ";
        for (int j = 0; j < GENE; j++) {
            cout << children[i][j] << " ";
        }
        cout << "\n\n";
    }

}



char newChromosome[POP_SIZE][GENE];

int counter = 0;
void survivalSelection() {

  
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < GENE; j++) {
          newChromosome[counter][j] = children[i][j];
            
        }
        counter++;
    }

    //Display
    for (int i = 0; i < POP_SIZE; i++) {
        cout << endl;
        for (int j = 0; j < GENE; j++) {
            
            cout << newChromosome[i][j] << " ";
        }

    }

}

void copyChromosome() {

    
    counter = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 0; j < GENE; j++)
        {
            chromosome[i][j] = newChromosome[i][j];
        }


    }

    for (int i = 0; i < POP_SIZE; i++) {
        cout << endl;
        for (int j = 0; j < GENE; j++)
        {

            cout << chromosome[i][j] << " ";
        }
    }

    cout << endl;
}



void calculateAverageFitness() {
    double totalFitness = 0.0;
    double avgFitness ;

    for (int i = 0; i < POP_SIZE; i++)
    {
        //2.1 Accumulate the fitness into totalFitness
        totalFitness += fitness_fx[i];
    }

    avgFitness = totalFitness / POP_SIZE;

    cout << "\n\tAverage Fitness : " << avgFitness << endl;


    AvgFitness.push_back(avgFitness);
}


void recordBestFitness() {
    //1. Declare the bestChromosome data structure
    static char bestChromosome[1][GENE];
    static double bestFitness = 0;
    //2. For each chromosome
    for (int i = 0; i < POP_SIZE; i++)
    {
        //2.1. if (fitness current chromosome better than bestFitness){
        if (fitness_fx[i] > bestFitness) {
            //bestFitness = fitness for the current chromosome
            bestFitness = fitness_fx[i];
            //copy the chromosome to bestChromosome
            for (int j = 0; j < GENE; j++)
            {
                bestChromosome[0][j] = chromosome[i][j];
            }
        }
        else
            continue;
    }

    //3. Print the bestFitness and bestChromosome to the screen
    cout << "\n\tBest Fitness : " << bestFitness << "\t\tBest Chromosome : ";
    for (int j = 0; j < GENE; j++)
    {
        cout << bestChromosome[0][j];
    }

    cout << endl << endl;

    //Print the bestFitness and bestChromosome to two separate files

    BestFitness.push_back(bestFitness);

    for (int i = 0; i < GENE; i++)
    {

        bestChromosomeFile << " " << bestChromosome[0][i];
    }
    bestChromosomeFile << endl;

}



void ExportToCSVFile()
{
    averageNbestFitnessFile.open("Average_Best_Fitness.csv");

    averageNbestFitnessFile << "Average_Fitness, Best_Fitness" << endl;
    for (int i = 0; i < Max_Generation; i++)
    {
        averageNbestFitnessFile << AvgFitness[i] <<", " << BestFitness[i] << endl;
    }

    averageNbestFitnessFile.close();
}




