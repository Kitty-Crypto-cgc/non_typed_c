#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
    bool test[5] = {true, false, 0, NULL};

    for(int i = 0; i < 5; i++)
    {
        std::string output = (!test[i]) ? "match" : "no match";;
        cout << output << endl;
    } 
    /*
    string word_1 = "create list";
    int vowels = 0;
    int word_length;        // better to set .length() into variable to eliminate warnings
    int words_to_print = 0; // this will count how many words to print to use in for loop later

    
    vector <variable type> name_of_vector[size of vector];

    creating vectors
    leaving them empty for now
    
    vector<string> words_saved;
    vector<int> number_of_syllables_saved;

    cout << "Enter 4 words from the English dictionary, to determine the amount of syllables each word has." << endl;
    cout << "Please enter [#] when finished, to create a list." << endl;
    cin >> word_1;

    while (word_1 != "#") // as long as user doesnt enter # you can enter a word and
    {                     // have it run thru the syllable logic
        word_length = word_1.length();
        words_to_print++;
        words_saved.push_back(word_1);
        // ^ this saves the word into the next availabe index of vector for strings.

        for (int i = 0; i < word_length; i++) // length is a variable now instead of function syntax this
        {                                     // eliminates the <: signed/usnsigned mismatch warning below
            if ((word_1[i] == 'a') || (word_1[i] == 'e') || (word_1[i] == 'i') || (word_1[i] == 'o') || (word_1[i] == 'u') || (word_1[i] == 'y'))
            {
                vowels = vowels + 1;

                if ((word_1[i + 1] == 'a') || (word_1[i + 1] == 'e') || (word_1[i + 1] == 'i') || (word_1[i + 1] == 'o') || (word_1[i + 1] == 'u') || (word_1[i + 1] == 'y'))
                {
                    vowels = vowels - 1;

                    if (word_1[word_length - 1] == 'e')
                    {
                        vowels = vowels - 1;
                        if (vowels == 0)
                        {
                            vowels = vowels + 1;
                        }
                    }
                }
            }
        }
        number_of_syllables_saved.push_back(vowels);
        //^ this puts number of syllables into vector of ints
        vowels = 0; // this resets the amounts so it can count vowels of next word and not stack from previous word

        cin >> word_1; // this will reset the word and controls loop to print out chart if # is entered
    }

    // use a for loop to print out all the words

    cout << endl
         << endl
         << endl;
    cout << "Word: " << setw(30) << "Syllables: " << endl;

    for (int x = 0; x < words_to_print; x++)
    {
        cout << words_saved[x] << setw(20) << number_of_syllables_saved[x] << endl;
    }

    // system("pause");
    */
    return 0;
}
