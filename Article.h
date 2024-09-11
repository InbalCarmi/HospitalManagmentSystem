#pragma once

#include "Date.h"
#include <list>
#include <string>

using namespace std;

class Researcher;

class Article
{
private:
    string nameOfArticle;
    Date publishDate;
    list<Researcher*> researchersOfArticle; // List of pointers to researchers

public:
    // Constructors
    Article(const string& nameOfArticle, const Date& publishDate);

    // Setters and Getters
    void setNameOfArticle(const string& nameOfArticle);
    string getNameOfArticle() const;

    void addResearcher(Researcher& researcher);
    list<Researcher*> getResearchersOfArticle() const;

    Date getPublishDate() const;
    int getNumOfResearchersOfArticle() const;

    // Operators
    bool operator==(const Article& other) const;
    bool operator!=(const Article& other) const;
    friend ostream& operator<<(ostream& os, const Article& article);
};
