/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include <stack>
#include <deque>

void Finding_word_ladder(string start,string end,const Lexicon& english);
static string getWord(const Lexicon& english, const string& prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

static void generateLadder(const Lexicon& english, const string& start, const string& end) {
    cout << "Here's where you'll search for a word ladder connecting \"" << start << "\" to \"" << end << "\"." << endl;
}

static const string kEnglishLanguageDatafile = "./res/dictionary.txt";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        generateLadder(english, start, end);
        Finding_word_ladder(start,end,english);
    }
}

bool norepeat(stack<string>group,string word)
{
    while (!group.empty())
    {
        if(group.top()==word)
        {
            return false;
        }
        else
        {
            group.pop();
        }
    }
    return true;
}

stack<string>change_stack(stack<string>group1)
{
    stack<string>group2;
    while (!group1.empty())
    {
        group2.push(group1.top());
        group1.pop();
    }
    return group2;
}
stack<string>copy_stack(stack<string>group1)
{
    stack<string>group2;
    while (!group1.empty())
    {
        group2.push(group1.top());
        group1.pop();
    }
    while (!group2.empty())
    {
        group1.push(group2.top());
        group2.pop();
    }
    return group1;
}

void Finding_word_ladder(string start,string end,const Lexicon& english)
{
    stack<string>group;
    group.push(start);
    deque< stack<string> >WordLad,result;
    WordLad.push_back(group);
    while(!WordLad.empty())
    {
        for(int i=0;i<WordLad.front().top().length();i++)
        {
            char a = 'a';
            string word =WordLad.front().top();
            for(;a<'z';a++)
            {
                if(word[i]!=a)
                {
                    word[i]=a;
                    if(english.contains(word))
                    {
                        if(norepeat(WordLad.front(),word))
                        {
                            if(word==end)
                            {
                                stack<string>copystack=copy_stack(WordLad.front());
                                copystack.push(word);
                                cout<<"Hooray! we have found a solution"
                                        "and it is the stack you are working on in the queue)."<<endl;
                                stack<string> finally_result=change_stack(copystack);
                                while (!finally_result.empty())
                                {
                                    cout<<finally_result.pop()<<" ";
                                }
                                return;
                            }
                            else
                            {
                                stack<string>copystack=copy_stack(WordLad.front());
                                copystack.push(word);
                                WordLad.push_back(copystack);
                            }
                        }
                    }
                }

            }
        }
        WordLad.pop_front();
    }
}

int main() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    string start,end;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}
