// header file for the generator class
#include "lrc-generator.h"
// std lib headers
#include <iostream>

int main(int argc, char** argv) {
    if(argc != 1) { // check if arguments have been given to the program
        
        // the filename of the lrc file is the same as the lyrics file
        std::string lyrics_fname = std::string(argv[1]);
        std::string lrc_fname = lyrics_fname;
        lrc_fname.replace(lrc_fname.size() - 3, 3, "lrc");
        
        // a simple class implements a menu for setting up the lrc file
        Lrc_generator generator(lyrics_fname, lrc_fname);
        generator.run(); // main program loop (menu)
    }
    else {
        std::cerr << "No lyrics provided\nUsage: lrc-generator [LYRICS.txt]\n";
    }
    return 0;
}