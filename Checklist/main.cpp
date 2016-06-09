#include <iostream>
#include <limits>
#include <string>
#include <list>
#include <fstream>

/* Class for handling terminal I/O */
class Terminal
{
    public:
        static void clearScreen() { std::cout<<ERASE<<HOME<<std::flush; }
        static void invertDisplay() { std::cout<<INVERT<<std::flush; }
        static void boldDisplay() { std::cout<<BOLD<<std::flush; }
        static void normalDisplay() { std::cout<<NORMAL<<std::flush; }
        static void waitForEnter() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); }
        static void overwriteLine() { std::cout<<ROWUP1<<std::flush; }
        Terminal() = delete;
        Terminal(const Terminal& other) = delete;
        Terminal& operator= (const Terminal& rhs) = delete;
    private:
        static constexpr const char* INVERT="\033[7m";
        static constexpr const char* NORMAL="\033[0m";
        static constexpr const char* BOLD="\033[1m";
        static constexpr const char* ROWUP1="\033[A";
        static constexpr const char* ERASE="\033[2J";
        static constexpr const char* HOME="\033[H";
};

/* Class with all program messages and misc strings */
class Messages
{
    public:
        static constexpr const char* EMPTY_BOX="[ ]";
        static constexpr const char* CHECK_BOX="[X]";
        static constexpr const char* START_MSG=" : START";
        static constexpr const char* DONE_MSG=" : DONE";
        static constexpr const char COMMENT_CHAR='#';
        static void showHelp()
        {
            std::cout<<Messages::VERSION<<std::endl<<Messages::DESCRIPTION<<std::endl<<std::endl<<Messages::USAGE<<std::endl<<std::endl;
            std::cout<<Messages::COPYRIGHT<<std::endl<<Messages::AUTHOR<<std::endl;
        }
        Messages() = delete;
        Messages(const Messages& other) = delete;
        Messages& operator= (const Messages& rhs) = delete;
 
    private:
        static constexpr const char* VERSION="Checklist 0.1";
        static constexpr const char* DESCRIPTION="Simple, interactive checklist for the command-line";
        static constexpr const char* COPYRIGHT="(c) whatever";
        static constexpr const char* USAGE="usage: checklist file1 [...]";
        static constexpr const char* AUTHOR="Written by abc";
};

/* Main class, contains all the monkey business */
class Checklist
{
    public:
        // each checklist must be instantiated with the
        // name of the file that it corresponds to
        explicit Checklist(const std::string& fileName)
        : _fileName(fileName){ }

        // Main method, gets stuff rolling
        void run()
        {
            auto theList = populateItems(_fileName);
            if(!theList.empty())
            { 
                std::string listName = theList.front();
                theList.pop_front();
                startChecklist(listName);
                for(auto item : theList)
                {
                    displayItem(item);
                    Terminal::waitForEnter();
                    checkItem(item);
                }
                completeChecklist(listName);
            }
        }
        Checklist() = delete;
        Checklist(const Checklist& other) = delete;
        Checklist& operator= (const Checklist& rhs) = delete;
 
    private:
        void startChecklist(const std::string& name)
        {
            Terminal::boldDisplay();
            std::cout<<name<<std::flush;
            Terminal::normalDisplay();
            std::cout<<Messages::START_MSG<<std::flush;
            std::cout<<std::endl<<std::endl;
        }
        void completeChecklist(const std::string& name)
        {
            Terminal::boldDisplay();
            std::cout<<std::endl<<name<<std::flush;
            Terminal::normalDisplay();
            std::cout<<Messages::DONE_MSG<<std::flush;
            std::cout<<std::endl<<std::endl;
        }
        void displayItem(const std::string& item)
        {
            Terminal::invertDisplay();
            std::cout<<Messages::EMPTY_BOX<<item<<std::flush;
            Terminal::normalDisplay();
        }
        void checkItem(const std::string& item)
        {
            Terminal::overwriteLine();
            std::cout<<Messages::CHECK_BOX<<item<<std::flush;
            std::cout<<std::endl;
        }
        std::list<std::string> populateItems(const std::string fileName)
        {
            std::list<std::string> retVal;
            std::fstream fIn(fileName);
            if(fIn.is_open())
            {
                std::string line;
                while (std::getline(fIn,line))
                {
                    if((line.front() == Messages::COMMENT_CHAR)
                        || (line.length() < 2))
                    {
                        //ignore comments and blank lines
                        continue;
                    }
                    else
                    {
                        retVal.push_back(line);
                    }
                }
            }
            return retVal;
        }
        std::string _fileName;
};

int main(int argc, char** argv)
{
    Terminal::clearScreen();
    if(argc < 2)
    {
        Messages::showHelp();
        return 0;
    }

    // prepare list of checklists
    // assume one checklist per file
    std::list<std::string> fileNames;    
    for(auto i = 1; i < argc; ++i)
        fileNames.push_back(argv[i]);

    // run through each checklist in order specified
    for(auto file : fileNames)
    {    
        Checklist checkList(file);
        checkList.run();
    }
    return 0;
}
