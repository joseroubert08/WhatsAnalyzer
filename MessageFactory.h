//
// Created by Christoph on 27.09.2015.
//

#ifndef WHATSANALYZER_MESSAGEFACTORY_H
#define WHATSANALYZER_MESSAGEFACTORY_H


#include <vector>
#include <unordered_map>
#include "Message.h"
#include <regex>

class MessageFactory {
public:
    std::pair<std::vector<Message>, std::unordered_map<std::string, int>> processFile(std::string filename);
private:
    std::vector<Message> _messages;
    std::unordered_map<std::string, int> _participants;
};

class MessageProcessor {
public:
    virtual ~MessageProcessor() { };

    static const std::regex &get_regex() {
        std::regex regex;
        return regex;
    }

    virtual Message::processedMsg process(const std::string &line) {
        if (std::regex_match(line, get_regex())) {
            std::cmatch res;
            std::regex_search(line.c_str(), res, get_regex());
            struct tm tm1 = {0};
            Message::processedMsg msg;
            tm1.tm_mday = std::atoi(res[1].str().c_str());
            tm1.tm_mon = std::atoi(res[2].str().c_str());
            tm1.tm_year = 2000 + (std::atoi(res[3].str().c_str()));
            tm1.tm_hour = std::atoi(res[4].str().c_str());
            tm1.tm_min = std::atoi(res[5].str().c_str());
            msg._time = tm1;
            msg._sender = res[6].str();
            msg._content = res[7].str();
            return msg;
        }
        else {
            Message::processedMsg msg;
            msg._content = line;
            return msg;
        }
    };

};


#endif //WHATSANALYZER_MESSAGEFACTORY_H
