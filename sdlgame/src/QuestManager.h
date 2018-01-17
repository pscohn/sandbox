#ifndef QUESTMANAGER_H_
#define QUESTMANAGER_H_

#include "datareader.h"

class QuestManager {
public:
    std::vector<int> activeQuests;

    void begin(int newQuestId) {
        activeQuests.push_back(newQuestId);
        printf("started quest %i\n", newQuestId);
    }

    bool isQuestActive(int questId) {
        for (int i = 0; i < activeQuests.size(); i++) {
            if (questId == activeQuests[i]) {
                return true;
            }
        }
        return false;
    }

    int checkForAvailableQuest(std::vector<int> possibleQuestIds) {
        for (int i = 0; i < possibleQuestIds.size(); i++) {
            if (!isQuestActive(possibleQuestIds[i])) {
                return possibleQuestIds[i];
            }
        }

        return -1;
    }

    std::vector<std::string> getDialogStart(int newQuestId) {
        return reader::getQuestStartDialog(newQuestId);
    }

};

#endif
