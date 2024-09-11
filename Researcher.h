#pragma once

#include <list>
#include "Worker.h"
#include "Article.h"

class Researcher : public virtual Worker
{
protected:
    std::list<Article*> articlesOfResearcher; // List of pointers to articles

public:
    // Constructors
    Researcher(const Worker& base);
    Researcher(const Worker& base, const std::list<Article*>& articlesOfResearcher);

    // Member functions
    bool addArticle(Article* article);
    std::list<Article*> getArticles() const;
    int getNumOfArticles() const;
    void toOs(std::ostream& os) const;
    bool operator==(const Researcher& other) const;
};
