/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
using namespace std;
#include<cstring>
#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include <random>

/**
 * dance.g,rejection.g,excuse.g存在问题(已解决)
 * 主要是空格影响替代词获取
 *
 *
 *
 *
 *
 */

static const string kGrammarsDirectory = "res/grammars/";
static const string kGrammarFileExtension = ".g";
static string getNormalizedFilename(string filename) {
    string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}

static bool isValidGrammarFilename(string filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}

static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        filename=kGrammarsDirectory + filename;
        if (!filename.empty() || isValidGrammarFilename(filename)) return filename;
        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}
string replace_word(string replace,string filename);

string ReadFile(string &filename)
{
    string sentence;
    vector<string> word;
    ifstream input;
    input.open(filename);
    std::string line;
    getline(input,line);
    int number;
    if (line=="<start>")
    {
        getline(input,line);
        number = stoi(line);
        for (int i = 0; i < number; ++i)
        {
            getline(input,line);
            if (i == 0)
            {
                sentence=line;
            }
            else
            {
                sentence=sentence+'\n'+line;
            }
        }
    }
    cout<<sentence<<endl;
    return sentence;
}
string deal_word(string &sentence,string filename)
{
    int start,end;
    while(true)
    {
        for (int i = 0; i < sentence.length(); i++)
        {
            if (sentence[i]=='<')
            {
                start = i;
                cout<<i<<endl;
            }
            else if(sentence[i]=='>')
            {
                end = i;
                cout<<i<<endl;
                break;
            }
            else if(sentence[i] != '<' && i==sentence.length() -1)
                return sentence;
        }
        string replaceWord =sentence.substr(start,end - start+1);
        cout<<replaceWord<<endl;
        sentence.erase(start,end - start+1);
        sentence.insert(start,replace_word(replaceWord,filename));
        cout<<sentence<<endl;
        cout<<"***********"<<endl;
    }
    return sentence;
}
string replace_word(string replace,string filename)
{
    vector<string> sentence;
    string line;
    ifstream input;
    input.open(filename);
    while(getline(input,line))
    {
        int number;
        if(line==replace)
        {
            getline(input,line);
            cout<<"数字"<<line<<endl;
            if (line.length() <3 && line.length() >0)//增加判断，当<>后为数字时进行读取文件
            {
                number = stoi(line);
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dist(0, number-1);
                int randomIndex = dist(gen);
                for (int i = 0; i < number; ++i)
                {
                    getline(input,line);
                    if(line.empty())//部分文件后面为空格，排除空格影响
                    {
                        number++;
                    }
                    else
                    sentence.push_back(line);
                }
                replace=sentence[randomIndex];
                return replace;
            }
        }
    }
    return replace;
}



int main() {
    while (true) {
        string filename = getFileName();
        if (filename.empty()) break;
        cout << "Here's where you read in the \"" << filename << "\" grammar "
             << "and generate three random sentences." << endl;
        string sentence =ReadFile(filename);
        sentence=deal_word(sentence,filename);
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
