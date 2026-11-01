/* 
Write a class that models a song.
The song should have properties such as title, artist, and duration in seconds.
Write a function that prints the details of the song.
*/
#include <string>
#include <iostream>

class Song {
    public:
        std::string title {};
        std::string artist {};
        int duration {};

        void Print() {
            std::cout << "Title: " << title << "\n";
            std::cout << "Artist: " << artist << "\n";
            std::cout << "Duration: " << duration << " seconds\n";
        }
};

int main() {
    Song currentSong;
    currentSong.title = "Thriller";
    currentSong.artist = "Michael Jackson";
    currentSong.duration = 450;
    currentSong.Print();


    return 0;
}