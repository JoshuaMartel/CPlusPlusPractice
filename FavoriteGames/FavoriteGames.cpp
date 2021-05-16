// FavoriteGames.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> favGames;
    vector<string>::iterator iter;
    string game;

    cout << "Hello. How can I help you? Type 'help' for options." << endl;
    cin >> game;

    while (game != "quit")
    {
        if (game == "help") 
        {
            cout << "Here are your options:" << endl;
            cout << "'add': add a game to your favorite game list" << endl;
            cout << "'delete': remove a game from your list" << endl;
            cout << "'print': display all of your favorite games" << endl;
            cout << "'quit': exit this program" << endl;
            
        }
        else if(game == "add")
        {
            cout << "What is the name?" << endl;
            cin >> game;
            favGames.push_back(game);
            cout << "Game added" << endl;
        }
        else if (game == "delete")
        {
            if (favGames.size() == 0)
            {
                cout << "There are no games listed!" << endl;
            }
            else
            {
                cout << "What game to you want to delete?" << endl;
                cin >> game;
                iter = find(favGames.begin(), favGames.end(), game);
                if (iter != favGames.end())
                {
                    favGames.erase(iter);
                    cout << "Game deleted;" << endl;
                }
                else
                {
                    cout << "Your game is not in the list" << endl;
                }
            }
        }
        else if (game == "print")
        {
            for (iter = favGames.begin(); iter != favGames.end(); ++iter)
            {
                cout << *iter << endl;
            }
        }
        else
        {
            cout << "sorry, that's not an option" << endl;
        }
        cout << endl;
        cin >> game;
        cout << endl;
    }

    cout << "Until next time.";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
