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
void randomquiz(){
	
}
void viewflashcards()
{
	string questions,answers;
	int flashcardnum=1;
	fstream question,answer;
	question.open("Questions.txt",ios::in);
	answer.open("Answers.txt",ios::in);
	if(!(question.is_open()) || !(answer.is_open()))
	{
		cout<<"Error opening files!"<<endl;
	}
	else
	{
	cout<<"All flashcards:"<<endl;
   while(getline(question,questions) && getline(answer,answers))
   {
   	cout<<"Flash Card number: "<<flashcardnum<<endl;
   	cout<<questions<<endl;
   	cout<<answers<<endl;
   	flashcardnum++;
   	cout<<"---------------"<<endl;
   }
}
}


bool admintry = 0;
void adminview(){
	string adminpass,temp;
	adminpass = "admin123@";
	cout<<"Confirm you are admin by entering the password."<<endl;
	cin>>temp;
	if(temp == adminpass){
		cout<<"Welcome Admin!"<<endl;
		int choice;
        do {
            cout << "\nAdmin Menu:" << endl;
            cout << "1 - List all files" << endl;
            cout << "2 - Refresh all files" << endl;
            cout << "3 - Exit Program" << endl;
            cout << "4 - Exit admin view" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  
            switch (choice) {
                case 1:
                    cout<<"The files currently in this program are:"<<endl;
                    cout<<"Answers.txt, Questions.txt, Scores.txt"<<endl;
                    break;
                case 2: {
                	// QUESTION FILE
                    ofstream question;
                    question.open("Questions.txt",ios::trunc);
                    if(!question){
                    	cout<<"Failed to open Questions.txt"<<endl; 	
					}
					else{
						cout<<"Contents of Question.txt deleted."<<endl;
					}
					// ANSWER FILE
					ofstream answers;
                    answers.open("Answers.txt",ios::trunc);
                    if(!answers){
                    	cout<<"Failed to open Answers.txt"<<endl; 	
					}
					else{
						cout<<"Contents of Answers.txt deleted."<<endl;
					}
					// SCORE FILE
					ofstream Score;
                    Score.open("Scores.txt",ios::trunc);
                    if(!Score){
                    	cout<<"Failed to open Scores.txt"<<endl; 	
					}
					else{
						cout<<"Contents of Scores.txt deleted."<<endl;
					}
                    break;
                }
                case 3:{
                	cout<<"Exiting the program."<<endl;
                	exit(0);
					break;
				}
                case 4:
                    cout << "Exiting admin view." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);

	}
	else{
		cout<<"Password incorrect, admin access blocked."<<endl;
		admintry = 1;
	}
}

int main(){
    int choice;
    cout << "FLASHCARD QUIZ PROGRAM" << endl;
    cout << "Which action do you want to perform?" << endl;
    cout << "1 - ADD A FLASHCARD" << endl;
    cout << "2 - DELETE A FLASHCARD" << endl;
    cout << "3 - RANDOM QUIZ" << endl;
    cout << "4 - SEARCH BY KEYWORD" << endl;
    cout << "5 - VIEW SCORES AND ANALYSIS" << endl;
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
            	
                viewflashcards();
                break;
            case 7:
            	if(admintry==0){
            		adminview();
				}
                else{
                	cout<<"Admin access has been blocked, as you entered the wrong password once."<<endl;
				}
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
