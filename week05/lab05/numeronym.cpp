// numeronym.cpp
// Lab 05, Problem 3 (optional): Numeronyms
//
// Build:  g++ -std=c++20 -Wall numeronym.cpp -o numeronym
// Run:    ./numeronym        (Windows: .\numeronym.exe)
//
// Written by:  (your name)

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// =================================================================
// PROVIDED: check utilities. Do not edit.
// =================================================================

// Prints one PASS or FAIL line for a number. Returns 1 or 0.
int check(std::string label, int got, int expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> " << got << '\n';
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got " << got << ", expected " << expected << '\n';
    return 0;
}

// Prints one PASS or FAIL line for a string. Returns 1 or 0.
int check_text(std::string label, std::string got, std::string expected)
{
    if (got == expected)
    {
        std::cout << "[PASS] " << label << " -> \"" << got << "\"\n";
        return 1;
    }
    std::cout << "[FAIL] " << label << ": got \"" << got << "\", expected \"" << expected << "\"\n";
    return 0;
}

// =================================================================
// YOUR CODE. Write your function here, above the CHECKS line.
// =================================================================

std::string numeronym(std::string x) {
    std::string final_x {};
    
    if (static_cast<int>(x.size()) <= 3) {
        return x;
    }

    for (int i {0}; (static_cast<int>(x.size())) > i; ++i) {
        if (i == 0 || i == static_cast<int>(x.size()-1)) {
            final_x.push_back(x[i]);
        }
    }

    final_x.insert(1, std::to_string(static_cast<int>(x.size()) - 2));

    return final_x;
}

std::string numeronym_sentence(std::string x) {
    std::string final_x {};
    std::stringstream ss(x);

    std::vector<std::string> words{};
    std::string tempWord {};

    while (ss >> tempWord) {
        words.push_back(tempWord);
    }

    for (std::string word : words) {
        std::string new_word {numeronym(word)};
        final_x += new_word;
        final_x.push_back(' ');
    }


    if (final_x.size() > 0) {
        final_x.erase(static_cast<int>(final_x.size())-1, 1);
    }
    

    return final_x;
}

// =================================================================
// CHECKS (provided). Once your function exists, delete the
// [CHECKS START] and [CHECKS END] lines. Do not edit the checks.
// =================================================================


void run_checks()
{
    std::cout << "== Numeronym checks ==\n";
    int passed{0};
    passed += check_text("numeronym(\"internationalization\")", numeronym("internationalization"), "i18n");
    passed += check_text("numeronym(\"Kubernetes\")", numeronym("Kubernetes"), "K8s");
    passed += check_text("numeronym(\"accessibility\")", numeronym("accessibility"), "a11y");
    passed += check_text("numeronym(\"code\")", numeronym("code"), "c2e");
    passed += check_text("numeronym(\"cat\")", numeronym("cat"), "cat");
    passed += check_text("numeronym(\"\")", numeronym(""), "");
    passed += check_text("numeronym_sentence(\"internationalization and localization\")", numeronym_sentence("internationalization and localization"), "i18n and l10n");
    passed += check_text("numeronym_sentence(\"I love Kubernetes\")", numeronym_sentence("I love Kubernetes"), "I l2e K8s");
    passed += check_text("numeronym_sentence(\"hi\")", numeronym_sentence("hi"), "hi");
    passed += check_text("numeronym_sentence(\"\")", numeronym_sentence(""), "");
    std::cout << "Numeronym: " << passed << " / 10 checks passed\n";
}


int main()
{
    // Un-comment the next line together with the check block above.
    run_checks();
    // std::cout << numeronym("i love carrots");
    return 0;
}
