#pragma once
#pragma once

#include "Builder.h"
#include "Date.h"
#include "Researcher.h"
#include <string>

class Report : public Builder
{
public:
    void buildTitle(const std::string& theTitle) override
    {
        theDocument->add("Report Title: " + theTitle + "\n");
    }

    void buildAuthor(const std::string& theAuthor) override
    {
        theDocument->add("Author: " + theAuthor + "\n");
    }

    void buildDate(const Date& date) override
    {
        theDocument->setDate(date);
    }

    void addResearcher(Researcher& researcher) override
    {
        theDocument->addResearcher(researcher);
    }
};
