#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void addflashcard() {
    string question, answer;
    fstream questionfile;
    
    questionfile.open("Questions.txt", ios::app);
    if (questionfile.is_open()) {
        cout << "Enter your question: " << endl;
        getline(cin, question);
        questionfile << question << endl; 
        questionfile.close();
    } else {
        cout << "Error: Unable to open Questions.txt" << endl;
    }

    
    fstream answerFile;
    answerFile.open("Answers.txt", ios::app);
    if (answerFile.is_open()) {
        cout << "Enter the answer: " << endl;
        getline(cin, answer);
        answerFile << answer << endl; 
        answerFile.close();
    } else {
        cout << "Error: Unable to open Answers.txt" << endl;
    }

}
int main(){
    int choice;
    cout<<"FLASHCARD QUIZ PROGRAM"<<endl;
     cout << "FLASHCARD QUIZ PROGRAM" << endl;
    cout << "Which action do you want to perform?" << endl;
    cout << "1 - ADD A FLASHCARD" << endl;
    cout << "2 - DELETE A FLASHCARD" << endl;
    cout << "3 - RANDOM QUIZ" << endl;
    cout << "4 - SEARCH BY KEYWORD" << endl;
    cout << "5 - VIEW SCORES" << endl;
    cout << "6 - VIEW ALL CARDS" << endl;
    cout << "7 - ADMIN VIEW" << endl;
    cout << "8 - EXIT" << endl;
   do {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addflashcard();
                break;
            case 2:
                cout << "Delete flashcard functionality is not implemented yet." << endl;
                break;
            case 3:
                cout << "Random quiz functionality is not implemented yet." << endl;
                break;
            case 4:
                cout << "Search by keyword functionality is not implemented yet." << endl;
                break;
            case 5:
                cout << "View scores functionality is not implemented yet." << endl;
                break;
            case 6:
                cout << "View all cards functionality is not implemented yet." << endl;
                break;
            case 7:
                cout << "Admin view functionality is not implemented yet." << endl;
                break;
            case 8:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "ERROR: INVALID INPUT. Please try again." << endl;
                break;
        }
    } while (choice != 8);
    
    return 0;
}
