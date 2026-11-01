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

        void modifySongTitle(std::string new_title) {
            title = new_title;
        }

        void durationToMinutes() {
            duration = static_cast<double>(duration) / 60.0;
        }

        double getMinutes() {
            return (static_cast<double>(duration) / 60.0);
        }
};

int main() {
    Song song("Thriller", "Michael Jackson", 450);
    song.Print();
    
    song.modifySongTitle("Thriller Remix");
    song.Print();

    return 0;
}