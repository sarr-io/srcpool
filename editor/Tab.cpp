#include <loader.h>

class Tab {
    public:
        std::string loadedFile;
        int selectedLine;

        int tabFocus(int i) {
            // search through tabList vector for the file path, then load the file.
        }

        int loadFile(std::string filePath) {
            // do some io stuff and iterate through lines (clear, then add to textbox vector)
        }

        std::string getLoadedFile() {
            return (loadedFile);
        }
};