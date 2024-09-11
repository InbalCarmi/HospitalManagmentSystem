#include "Article.h"
#include "Researcher.h"
#include <cstring>
#include <iostream>

// Constructor
Article::Article(const std::string& nameOfArticle, const Date& publishDate)
    : nameOfArticle(nameOfArticle), publishDate(publishDate) {}

// Setters and Getters
void Article::setNameOfArticle(const std::string& nameOfArticle) {
    this->nameOfArticle = nameOfArticle;
}

std::string Article::getNameOfArticle() const {
    return this->nameOfArticle;
}

Date Article::getPublishDate() const {
    return this->publishDate;
}

int Article::getNumOfResearchersOfArticle() const {
    return (int)researchersOfArticle.size();
}

// Function to add a researcher to the article
void Article::addResearcher(Researcher& researcher) {
    researchersOfArticle.push_back(&researcher);
}

// Getter for the list of researchers
std::list<Researcher*> Article::getResearchersOfArticle() const {
    return researchersOfArticle;
}

// Operators
bool Article::operator==(const Article& other) const {
    if (nameOfArticle != other.nameOfArticle)
        return false;
    if (publishDate != other.publishDate)
        return false;
    if (researchersOfArticle.size() != other.researchersOfArticle.size())
        return false;

    auto it1 = researchersOfArticle.begin();
    auto it2 = other.researchersOfArticle.begin();
    while (it1 != researchersOfArticle.end() && it2 != other.researchersOfArticle.end()) {
        if (**it1 != **it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

bool Article::operator!=(const Article& other) const {
    return !(*this == other);
}

// Output Stream Operator
std::ostream& operator<<(std::ostream& os, const Article& article) {
    os << "Article Name: " << article.getNameOfArticle();
    os << ", Publish Date: " << article.getPublishDate() << "\n";

    int numResearchers = article.getNumOfResearchersOfArticle();
    os << "Number of Author Researchers: " << numResearchers;

    if (numResearchers != 0) {
        os << "\nResearchers: ";
        bool first = true;
        for (const Researcher* researcher : article.getResearchersOfArticle()) {
            if (!first) {
                os << ", ";
            }
            os << researcher->getFirstName() << " " << researcher->getLastName();
            first = false;
        }
    }
    os << std::endl;
    return os;
}
