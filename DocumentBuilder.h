#pragma once
#pragma once

#include "Builder.h"
#include "Date.h"
#include "Researcher.h"
#include <string>

class DocumentBuilder
{
public:
    // Method to construct a document with title, author, date, and researchers
    void construct(Builder* builder, const std::string& theTitle, const std::string& theAuthor, const Date& publishDate, const std::list<Researcher*>& researchers)
    {
        builder->buildTitle(theTitle);
        builder->buildAuthor(theAuthor);
        builder->buildDate(publishDate);

        for (Researcher* researcher : researchers)
        {
            builder->addResearcher(*researcher);
        }
    }
};
