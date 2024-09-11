#pragma once

#include <string>
#include "Document.h"

class Builder
{
public:
    // Constructor and Destructor
    Builder() : theDocument(new Document) {}
    virtual ~Builder() { delete theDocument; }

    // Pure Virtual Functions
    virtual void buildTitle(const std::string& title) = 0;
    virtual void buildAuthor(const std::string& author) = 0;
    virtual void buildDate(const Date& date) = 0;
    virtual void addResearcher(Researcher& researcher) = 0;

    // Getter
    Document* getResult() const { return theDocument; }

protected:
    Document* theDocument; // Protected member for derived classes
}; // Builder
