#ifndef DATAREADER_H_
#define DATAREADER_H_

#include <tinyxml2.h>
// TODO add error handling

std::vector<std::string> randomElementSetText(std::string dialogPath, std::string name, std::string xmlPathStr) {
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
        std::string text = name + ": " + pRoot->GetText();
        message.push_back(text);
    }

    return message;
};

std::vector<std::string> getRandomDialog(std::string dialogPath, std::string name) {
    return randomElementSetText(dialogPath, name, "dialog");
};

std::vector<std::string> getRandomSongBeginDialog(std::string dialogPath, std::string name) {
    return randomElementSetText(dialogPath, name, "songbegin");
}

std::vector<std::string> getRandomSongEndDialog(std::string dialogPath, std::string name) {
    return randomElementSetText(dialogPath, name, "songend");
}

#endif
