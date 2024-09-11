#include "Researcher.h"
#include <cstring>

// Constructor that initializes base Worker
Researcher::Researcher(const Worker& base) : Worker(base) {}

// Constructor that initializes base Worker and copies articles
Researcher::Researcher(const Worker& base, const std::list<Article*>& articlesOfResearcher)
    : Worker(base), articlesOfResearcher(articlesOfResearcher) {
    for (list<Article*>::iterator it = this->articlesOfResearcher.begin(); it != this->articlesOfResearcher.end(); ++it) {
        *it = new Article(**it); // Deep copy of articles
    }
}

// Function to add an article
bool Researcher::addArticle(Article* article) {
    if (article == nullptr) {
        return false;
    }
    articlesOfResearcher.push_back(article);
    return true;
}

// Getter for articles
std::list<Article*> Researcher::getArticles() const {
    return articlesOfResearcher;
}

// Getter for the number of articles
int Researcher::getNumOfArticles() const {
    return (int)articlesOfResearcher.size();
}

// Equality operator
bool Researcher::operator==(const Researcher& other) const {
    if (static_cast<const Worker&>(*this) != static_cast<const Worker&>(other))
        return false;
    if (articlesOfResearcher.size() != other.articlesOfResearcher.size())
        return false;

    auto it1 = articlesOfResearcher.begin();
    auto it2 = other.articlesOfResearcher.begin();
    while (it1 != articlesOfResearcher.end() && it2 != other.articlesOfResearcher.end()) {
        if (**it1 != **it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

// Output stream operator to display Researcher details
void Researcher::toOs(std::ostream& os) const {
    Worker::toOs(os);
    os << "Number of Articles: " << getNumOfArticles() << std::endl;

    if (!articlesOfResearcher.empty())
        os << "Articles: ";

    for (auto it = articlesOfResearcher.begin(); it != articlesOfResearcher.end(); ++it) {
        os << (*it)->getNameOfArticle();
        if (std::next(it) != articlesOfResearcher.end()) {
            os << ", ";
        }
    }
    os << std::endl;
}
