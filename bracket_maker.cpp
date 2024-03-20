// #include <iostream>
// #include <chrono>

// using namespace std;

// char *bracketGenerator(char *bracket, char *preBracket, int size)
// {

//     int outerIndexer = 0;
//     for (int i = 1; i <= size; i++)
//     {
//         outerIndexer += 2;
//         bracket[i - 1] = preBracket[outerIndexer - 1];
//         cout << outerIndexer - 1 << " : " << preBracket[outerIndexer - 1] << ":" << bracket[i - 1] << endl;
//     }
//     bracket[size] = '\0';

//     return bracket;
// }

// int main()
// {
//     auto start = std::chrono::high_resolution_clock::now();

//     char *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//     char Bracket1[33];
//     char Bracket2[17];
//     char Bracket3[9];
//     char Bracket4[5];
//     char Bracket5[3];
//     char Winner[2];
//     // char *finalBracket;

//     bracketGenerator(Bracket1, chars, 32);
//     cout << "Bracket1"
//          << ":" << Bracket1 << endl;
//     bracketGenerator(Bracket2, Bracket1, 16);
//     cout << "Bracket2"
//          << ":" << Bracket2 << endl;
//     bracketGenerator(Bracket3, Bracket2, 8);
//     cout << "Bracket3"
//          << ":" << Bracket3 << endl;
//     bracketGenerator(Bracket4, Bracket3, 4);
//     cout << "Bracket4"
//          << ":" << Bracket4 << endl;
//     bracketGenerator(Bracket5, Bracket4, 2);
//     cout << "Bracket5"
//          << ":" << Bracket5 << endl;
//     bracketGenerator(Winner, Bracket5, 1);
//     cout << "Winner"
//          << ":" << Winner << endl;

//     // Allocate enough space for all the characters plus the null terminator
//     char finalBracket[33 + 17 + 9 + 5 + 3 + 2 + 1];
//     strcpy(finalBracket, Bracket1); // Copy the first bracket into finalBracket
//     strcat(finalBracket, Bracket2); // Concatenate the rest of the brackets
//     strcat(finalBracket, Bracket3);
//     strcat(finalBracket, Bracket4);
//     strcat(finalBracket, Bracket5);
//     strcat(finalBracket, Winner);

//     cout << "Final Bracket: " << finalBracket << endl;
//     auto stop = std::chrono::high_resolution_clock::now();

 
//     // Calculate duration
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

//     // Output the duration in nanoseconds
//     std::cout << "Time taken by program: " << duration.count() << " nanoseconds" << std::endl;
// }


#include <iostream>
#include <chrono>
#include <cstring> // For strcpy and strcat
#include <string> // For std::string

std::string bracketGenerator(const std::string& preBracket, int size)
{
    std::string bracket;
    bracket.reserve(size + 1); // Reserve enough space for the entire bracket
    int outerIndexer = 0;
    for (int i = 1; i <= size; ++i)
    {
        outerIndexer += 2;
        bracket += preBracket[outerIndexer - 1];
    }

    return bracket;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string Bracket1 = bracketGenerator(chars, 32);
    std::string Bracket2 = bracketGenerator(Bracket1, 16);
    std::string Bracket3 = bracketGenerator(Bracket2, 8);
    std::string Bracket4 = bracketGenerator(Bracket3, 4);
    std::string Bracket5 = bracketGenerator(Bracket4, 2);
    std::string Winner = bracketGenerator(Bracket5, 1);

    // Output brackets for verification
    std::cout << "Bracket1: " << Bracket1 << "\n"
              << "Bracket2: " << Bracket2 << "\n"
              << "Bracket3: " << Bracket3 << "\n"
              << "Bracket4: " << Bracket4 << "\n"
              << "Bracket5: " << Bracket5 << "\n"
              << "Winner: " << Winner << "\n";

    std::string finalBracket = Bracket1 + Bracket2 + Bracket3 + Bracket4 + Bracket5 + Winner;

    std::cout << "Final Bracket: " << finalBracket << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    // Output the duration in nanoseconds
    std::cout << "Time taken by program: " << duration.count() << " nanoseconds" << std::endl;

    return 0;
}
