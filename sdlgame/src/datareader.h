#ifndef DATAREADER_H_
#define DATAREADER_H_

#include <tinyxml2.h>
// TODO add error handling

namespace reader {

std::vector<std::string> randomElementGetText(std::string dialogPath, std::string xmlPathStr) {
    const char* xmlPath = xmlPathStr.c_str();
    std::vector<std::string> message;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* pRoot;
    doc.LoadFile(dialogPath.c_str());

    if (doc.FirstChild()->FirstChildElement(xmlPath) == NULL) {
        return message;
    }

    int possibleMessages = 0;
    tinyxml2::XMLElement* countRoot;
    for (countRoot = doc.FirstChild()->FirstChildElement(xmlPath); countRoot != nullptr;
         countRoot = countRoot->NextSiblingElement(xmlPath)) {
        possibleMessages++;
    }
    int randomConversation = rand() % possibleMessages;

    pRoot = doc.FirstChild()->FirstChildElement(xmlPath);
    for (int i = 0; i < randomConversation; i++) {
        pRoot = pRoot->NextSiblingElement(xmlPath);
    }

    for (pRoot = pRoot->FirstChildElement("element"); pRoot != nullptr;
         pRoot = pRoot->NextSiblingElement("element")) {
        std::string text = pRoot->GetText();
        message.push_back(text);
    }

    return message;
};

std::vector<std::string> getTextAtPath(std::string songPath, std::string element) {
    const char* xmlPath = element.c_str();
    std::vector<std::string> message;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* pRoot;
    doc.LoadFile(songPath.c_str());

    if (doc.FirstChild()->FirstChildElement(xmlPath) == NULL) {
        return message;
    }

    for (pRoot = doc.FirstChild()->FirstChildElement(xmlPath); pRoot != nullptr;
         pRoot = pRoot->NextSiblingElement(xmlPath)) {
        message.push_back(pRoot->GetText());
    }

    return message;
}

std::vector<int> getIntsAtPath(std::string songPath, std::string element) {
    const char* xmlPath = element.c_str();
    std::vector<int> result;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* pRoot;
    doc.LoadFile(songPath.c_str());

    if (doc.FirstChild()->FirstChildElement(xmlPath) == NULL) {
        return result;
    }

    for (pRoot = doc.FirstChild()->FirstChildElement(xmlPath); pRoot != nullptr;
         pRoot = pRoot->NextSiblingElement(xmlPath)) {
        std::string s = pRoot->GetText();
        result.push_back(stoi(s));
    }

    return result;
}


std::vector<std::string> getQuestStartDialog(int questId) {
    return randomElementGetText("data/quests/" + std::to_string(questId) + ".xml", "questStartDialog");
}

std::vector<std::string> getQuestEndDialog(int questId) {
    return randomElementGetText("data/quests/" + std::to_string(questId) + ".xml", "questEndDialog");
}

std::vector<std::string> getRandomDialog(std::string dialogPath) {
    return randomElementGetText(dialogPath, "dialog");
};

std::vector<std::string> getRandomSongBeginDialog(std::string dialogPath) {
    return randomElementGetText(dialogPath, "songbegin");
}

std::vector<std::string> getRandomSongEndDialog(std::string dialogPath) {
    return randomElementGetText(dialogPath, "songend");
}

std::vector<int> getNpcQuests(std::string path) {
    return getIntsAtPath(path, "questStart");
}

std::vector<int> parseIntsByComma(std::string s) {
    std::string delimiter = ",";
    std::vector<int> ints;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        ints.push_back(stoi(s));
        s.erase(0, pos + delimiter.length());
    }
    ints.push_back(stoi(s));
    return ints;
}

std::vector<std::vector<int> > loadSong(std::string songPath) {
    std::vector<std::vector<int> > tracks;
    std::vector<std::string> tracksText = getTextAtPath(songPath, "track");
    for (int i = 0; i < tracksText.size(); i++) {
        std::vector<int> notes = parseIntsByComma(tracksText[i]);
        tracks.push_back(notes);
    }
    return tracks;
}

}

#endif
