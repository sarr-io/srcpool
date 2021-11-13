
// srcpool renderer

#include <glad/glad.h>
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>

std::vector<std::string> renderQueue {  ""  };

int lastID;
GLuint windowVAO;
GLuint tablistVAO;
GLuint textboxVAO; // Positions of how many lines are in the file itself, then use EBO to specify which lines to show in the textbox's viewport.

std::vector<int> bufferCount;

std::string writeBuffer(std::string compData[]) {
    std::string id = compData[0];

    std::string rawPos = compData[1];
    std::vector<std::string> posTable;
    std::string tempPos;
    for (int i = 0; i < rawPos.length(); i++) {
        if (rawPos[i] != ',' && rawPos[i] != ' ') {
            tempPos += rawPos[i];
        }
        else if (rawPos[i] == ',') {
            posTable.push_back(tempPos);
            tempPos = "";
        }
    }
    posTable.push_back(tempPos);

    std::string rawInd = compData[2];
    std::vector<std::string> indTable;
    for (int i = 0; i < rawInd.length(); i++) {
        if (rawInd[i] != ',' && rawInd[i] != ' ') {
            indTable.push_back(rawInd.substr(i, 1));
        }
    }

    std::string returnString;

    returnString += id + "|";

    for (int i = 0; i < posTable.size(); i++) {
        returnString += (posTable[i] + ",");
    }

    returnString += "|";

    for (int i = 0; i < indTable.size(); i++) {
        returnString += (indTable[i] + ",");
    }

    renderQueue.push_back(returnString);

    // Adding 1 to the buffer count for specified vertex array.
    bufferCount[std::stoi(id)]++;

    return(returnString);
}

void readBuffer(GLuint index, int& id, std::vector<float>& pos, std::vector<int>& ind) {
    std::string data = renderQueue[index];

    int stage = 1;
    std::string tempId;
    std::string tempPos;
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '|') {   stage++;    }
        else {
            switch (stage) {
                case 1:
                    tempId += data[i];
                    break;
                case 2:
                    if (data[i] != ',') {
                        tempPos += data[i];
                    }
                    else if (data[i] == '|') {
                        pos.push_back(std::stof(tempPos));
                        tempPos = "";
                    }
                    else {
                        std::cout << "Pushing back " << std::stof(tempPos) << std::endl;
                        pos.push_back(std::stof(tempPos));
                        tempPos = "";
                    }
                    break;
                case 3:
                    if (data[i] != ',') {
                        ind.push_back(data[i] - '0');
                    }
                    break;
            }
        }
        id = std::stoi(tempId);
    }
    
    return;
}

void Draw() {
    for (int i = 1; i < renderQueue.size(); i++) {
        int vaoID;
        std::vector<float> posTable;
        std::vector<int> indTable;
        readBuffer(i, vaoID, posTable, indTable);

        glBindVertexArray(vaoID);
        glDrawElements(GL_QUADS, indTable.size(), GL_UNSIGNED_INT, 0);
        std::cout << "LETS GOOOOO" << std::endl;
        glBindVertexArray(0);
    }
    
    return;
}

void assignVAO(GLuint& VAO) {
    lastID = VAO + 1;
    glGenVertexArrays(lastID, &VAO);
    bufferCount.push_back(0);

    return;
}

void AddBuffer(std::string compData[]) {
    std::cout << "Buffer added: " << writeBuffer(compData) << std::endl;
    return;
}

void linkBuffer(GLuint index) {
    int vaoID;
    std::vector<float> posTable;
    std::vector<int> indTable;
    readBuffer(index, vaoID, posTable, indTable);

    int length = posTable.size() / 3;
    if (posTable.size() % 3 != 0) {
        std::cout << "Error: Buffer is not complete. (Probably missing a dimension on a vertex)" << std::endl;
        return;
    }

    glBindVertexArray(vaoID);

    std::cout << vaoID << std::endl;
    GLuint VBO, EBO = bufferCount[vaoID];

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, posTable.size() * sizeof(float), &posTable, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indTable.size() * sizeof(int), &indTable, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return;
}

void InitComponents() {
    for (int i = 1; i < renderQueue.size(); i++) {
        linkBuffer(i);
    }
    return;
}