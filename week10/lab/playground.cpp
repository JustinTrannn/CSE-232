// playground.cpp
// Lab 09: Pointers and References. PROVIDED. Do not edit.
//
// A memory playground. Type simplified C++ lines and watch what happens to
// memory: every variable is a numbered box, a reference is a second name on
// the same box, and a pointer is an arrow to a box.
//
// Build:  g++ -std=c++20 -Wall playground.cpp -o playground
// Run:    ./playground          (Windows: .\playground.exe)
//
// Lines you can type:
//   int x = 5          a new box holding 5          int x       (holds 0)
//   int& r = x         r is another name for x's box
//   int* p = &x        p points to x's box           int* p      (points to nothing)
//   x = 7              put 7 in x's box (also through a reference)
//   *p = 7             put 7 in the box p points to
//   p = &y             point p at y's box            p = nullptr
//   print x            print *p      print &x      print p
//   show               draw memory          help          quit
//
// You do not need to understand how this file works. It uses a few tools
// (std::map) that come later in the course.

#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<int> boxes{};                   // the values, one per box
std::map<std::string, int> variableBox{};   // name of a variable or reference -> box index
std::map<std::string, int> pointerTarget{}; // name of a pointer -> box index, or -1 for nullptr
std::vector<std::string> declared{};        // names in the order they were declared

bool isVariable(std::string name) { return variableBox.count(name) > 0; }
bool isPointer(std::string name) { return pointerTarget.count(name) > 0; }
bool isNumber(std::string text)
{
    if (text.empty())
    {
        return false;
    }
    size_t start{text.at(0) == '-' ? size_t{1} : size_t{0}};
    if (start >= text.size())
    {
        return false;
    }
    for (size_t i{start}; i < text.size(); ++i)
    {
        if (text.at(i) < '0' || text.at(i) > '9')
        {
            return false;
        }
    }
    return true;
}

std::vector<std::string> tokenize(std::string line)
{
    std::vector<std::string> tokens{};
    std::string current{};
    for (char c : line)
    {
        if (c == ' ' || c == '\t' || c == ';')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current = "";
            }
        }
        else if (c == '&' || c == '*' || c == '=')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current = "";
            }
            tokens.push_back(std::string(1, c));
        }
        else
        {
            current += c;
        }
    }
    if (!current.empty())
    {
        tokens.push_back(current);
    }
    return tokens;
}

void show()
{
    std::cout << "\n  memory\n";
    for (size_t i{0}; i < boxes.size(); ++i)
    {
        std::cout << "  box #" << (i + 1) << " [ " << boxes.at(i) << " ]   ";
        std::string names{};
        for (std::string name : declared)
        {
            if (isVariable(name) && variableBox.at(name) == static_cast<int>(i))
            {
                names += (names.empty() ? "" : ", ") + name;
            }
        }
        std::cout << names << "\n";
    }
    for (std::string name : declared)
    {
        if (isPointer(name))
        {
            int target{pointerTarget.at(name)};
            std::cout << "  " << name << "  --->  ";
            if (target < 0)
            {
                std::cout << "nullptr\n";
            }
            else
            {
                std::cout << "box #" << (target + 1) << "\n";
            }
        }
    }
    std::cout << "\n";
}

void help()
{
    std::cout << "  int x = 5      int& r = x      int* p = &x      int* p\n"
              << "  x = 7          *p = 7          p = &y           p = nullptr\n"
              << "  print x        print *p        print &x         print p\n"
              << "  show           help            quit\n";
}

bool declareName(std::string name)
{
    if (isVariable(name) || isPointer(name))
    {
        std::cout << "  " << name << " already exists.\n";
        return false;
    }
    if (name.empty() || isNumber(name) || name == "nullptr")
    {
        std::cout << "  '" << name << "' is not a valid name.\n";
        return false;
    }
    declared.push_back(name);
    return true;
}

// Sets which box a pointer points to, from the tokens after '='.
void pointAt(std::string pointer, std::vector<std::string> rhs)
{
    if (rhs.size() == 2 && rhs.at(0) == "&" && isVariable(rhs.at(1)))
    {
        pointerTarget[pointer] = variableBox.at(rhs.at(1));
    }
    else if (rhs.size() == 1 && rhs.at(0) == "nullptr")
    {
        pointerTarget[pointer] = -1;
    }
    else if (rhs.size() == 1 && isPointer(rhs.at(0)))
    {
        pointerTarget[pointer] = pointerTarget.at(rhs.at(0));
    }
    else if (rhs.size() == 1 && isVariable(rhs.at(0)))
    {
        std::cout << "  " << rhs.at(0) << " is an int, not an address. Did you mean &" << rhs.at(0) << "?\n";
    }
    else
    {
        std::cout << "  A pointer needs an address (&name), another pointer, or nullptr.\n";
    }
}

void execute(std::vector<std::string> t)
{
    if (t.empty())
    {
        return;
    }
    if (t.at(0) == "show")
    {
        return; // the diagram is drawn after every line anyway
    }
    if (t.at(0) == "help")
    {
        help();
        return;
    }
    if (t.at(0) == "print" && t.size() >= 2)
    {
        if (t.size() == 2 && isVariable(t.at(1)))
        {
            std::cout << "  " << t.at(1) << " = " << boxes.at(variableBox.at(t.at(1))) << "\n";
        }
        else if (t.size() == 2 && isPointer(t.at(1)))
        {
            int target{pointerTarget.at(t.at(1))};
            std::cout << "  " << t.at(1) << " holds the address of " << (target < 0 ? "nothing (nullptr)" : "box #" + std::to_string(target + 1)) << "\n";
        }
        else if (t.size() == 3 && t.at(1) == "&" && isVariable(t.at(2)))
        {
            std::cout << "  &" << t.at(2) << " is the address of box #" << (variableBox.at(t.at(2)) + 1) << "\n";
        }
        else if (t.size() == 3 && t.at(1) == "*" && isPointer(t.at(2)))
        {
            int target{pointerTarget.at(t.at(2))};
            if (target < 0)
            {
                std::cout << "  " << t.at(2) << " is nullptr. Dereferencing it would crash a real program.\n";
            }
            else
            {
                std::cout << "  *" << t.at(2) << " = " << boxes.at(target) << "  (the value in box #" << (target + 1) << ")\n";
            }
        }
        else
        {
            std::cout << "  I do not know that name.\n";
        }
        return;
    }
    if (t.at(0) == "int")
    {
        if (t.size() >= 3 && t.at(1) == "&")
        {
            // int& r = x
            if (t.size() == 5 && t.at(3) == "=" && isVariable(t.at(4)))
            {
                if (declareName(t.at(2)))
                {
                    variableBox[t.at(2)] = variableBox.at(t.at(4));
                }
            }
            else if (t.size() == 5 && t.at(3) == "=" && isPointer(t.at(4)))
            {
                std::cout << "  " << t.at(4) << " is a pointer. A reference to an int needs an int.\n";
            }
            else
            {
                std::cout << "  A reference must be given a variable right away: int& r = x\n";
            }
            return;
        }
        if (t.size() >= 3 && t.at(1) == "*")
        {
            // int* p        int* p = &x        int* p = nullptr        int* p = q
            if (!declareName(t.at(2)))
            {
                return;
            }
            pointerTarget[t.at(2)] = -1;
            if (t.size() > 3)
            {
                if (t.at(3) == "=")
                {
                    pointAt(t.at(2), std::vector<std::string>(t.begin() + 4, t.end()));
                }
                else
                {
                    std::cout << "  I did not understand that. Try: int* p = &x\n";
                }
            }
            return;
        }
        // int x        int x = 5        int c = y
        if (t.size() == 2 || (t.size() == 4 && t.at(2) == "="))
        {
            int value{0};
            if (t.size() == 4)
            {
                if (isNumber(t.at(3)))
                {
                    value = std::stoi(t.at(3));
                }
                else if (isVariable(t.at(3)))
                {
                    value = boxes.at(variableBox.at(t.at(3))); // a copy: a new box with the same value
                }
                else
                {
                    std::cout << "  An int needs a number or another int.\n";
                    return;
                }
            }
            if (declareName(t.at(1)))
            {
                boxes.push_back(value);
                variableBox[t.at(1)] = static_cast<int>(boxes.size()) - 1;
            }
            return;
        }
        std::cout << "  I did not understand that. Try: int x = 5\n";
        return;
    }
    if (t.at(0) == "*" && t.size() == 4 && t.at(2) == "=" && isPointer(t.at(1)))
    {
        // *p = 7
        int target{pointerTarget.at(t.at(1))};
        if (target < 0)
        {
            std::cout << "  " << t.at(1) << " is nullptr. Dereferencing it would crash a real program.\n";
        }
        else if (isNumber(t.at(3)))
        {
            boxes.at(target) = std::stoi(t.at(3));
        }
        else if (isVariable(t.at(3)))
        {
            boxes.at(target) = boxes.at(variableBox.at(t.at(3)));
        }
        else
        {
            std::cout << "  *" << t.at(1) << " needs a number or an int.\n";
        }
        return;
    }
    if (t.size() >= 3 && t.at(1) == "=")
    {
        std::string name{t.at(0)};
        std::vector<std::string> rhs(t.begin() + 2, t.end());
        if (isVariable(name))
        {
            if (rhs.size() == 1 && isNumber(rhs.at(0)))
            {
                boxes.at(variableBox.at(name)) = std::stoi(rhs.at(0));
            }
            else if (rhs.size() == 1 && isVariable(rhs.at(0)))
            {
                boxes.at(variableBox.at(name)) = boxes.at(variableBox.at(rhs.at(0)));
            }
            else if (rhs.size() == 2 && rhs.at(0) == "&")
            {
                std::cout << "  " << name << " is an int. It cannot hold an address; only a pointer can.\n";
            }
            else
            {
                std::cout << "  " << name << " needs a number or another int.\n";
            }
        }
        else if (isPointer(name))
        {
            pointAt(name, rhs);
        }
        else
        {
            std::cout << "  I do not know " << name << ". Declare it first: int " << name << " = 0\n";
        }
        return;
    }
    std::cout << "  I did not understand that. Type help for the list of lines.\n";
}

int main()
{
    std::cout << "Memory playground. Type help for the lines you can use, quit to leave.\n";
    show();
    std::string line{};
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
        {
            break;
        }
        std::vector<std::string> tokens{tokenize(line)};
        if (!tokens.empty() && tokens.at(0) == "quit")
        {
            break;
        }
        execute(tokens);
        show();
    }
    std::cout << "Bye.\n";
    return 0;
}
