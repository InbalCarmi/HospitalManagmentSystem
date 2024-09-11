#pragma once
#include <string>
#include <list>
#include <iostream>
#include "Date.h"
#include "Researcher.h" 

using namespace std;

class Document
{
public:
    // Add a part to the document
    void add(const string& part) { parts.push_back(part); }

    // Add a researcher to the document
    void addResearcher(Researcher& researcher) { researchersOfArticle.push_back(&researcher); }

    // Set the publication date of the document
    void setDate(const Date& date) { publishDate = date; }

    // Display the document content and researchers
    void show() const
    {
        cout << "\nThe document -------\n";

        for (const auto& part : parts)
        {
            cout << part;
        }
        cout << endl;

        cout << "Published on: " << publishDate << endl;

        int numResearchers = researchersOfArticle.size();
        cout << "Number of Author Researchers: " << numResearchers;

        if (numResearchers != 0)
        {
            cout << "\nResearchers: ";
            bool first = true;
            for (const Researcher* researcher : researchersOfArticle)
            {
                if (!first)
                {
                    cout << ", ";
                }
                cout << researcher->getFirstName() << " " << researcher->getLastName();
                first = false;
            }
        }
        cout << endl;
    }

private:
    list<string> parts; 
    Date publishDate; 
    list<Researcher*> researchersOfArticle; 
};
