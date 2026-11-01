/* 
Write a class that models a song.
The song should have properties such as title, artist, and duration in seconds.
Write a function that prints the details of the song.
*/
#include <string>
#include <iostream>

class Song {
    private:
        std::string title {};
        std::string artist {};
        int duration {};

    public:
        // default constructor
        Song() {
            title = "Unknown";
            artist = "Unknown";
            duration = 0;
        }

        // Parameterized constructor
        Song(std::string t, std::string a, int d) {
            title = t;
            artist = a;
            duration = d;
        }

        void Print() {
            std::cout << "Title: " << title << "\n";
            std::cout << "Artist: " << artist << "\n";
            std::cout << "Duration: " << duration << " seconds\n";
        }
};

int main() {
    Song song1;
    song1.Print();

    Song song2("Thriller", "Michael Jackson", 450);
    song2.Print();

    return 0;
}