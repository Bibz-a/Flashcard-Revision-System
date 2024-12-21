#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
using namespace std;
void sortFlashcardsAlphabetically() {
    string questions[100];
    string answers[100];
    int size = 0;

    ifstream questionFile("Questions.txt");
    ifstream answerFile("Answers.txt");

    if (!questionFile.is_open() || !answerFile.is_open()) {
        cout << "Error: Unable to open Questions.txt or Answers.txt" << endl;
        return;
    }

    while (getline(questionFile, questions[size]) && getline(answerFile, answers[size])) {
        size++;
    }

    questionFile.close();
    answerFile.close();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*(answers+j) > *(answers+j+1)) {
                swap(answers[j], answers[j + 1]);
                swap(questions[j], questions[j + 1]);
            }
        }
    }

    ofstream sortedQuestionFile("Questions.txt", ios::trunc);
    ofstream sortedAnswerFile("Answers.txt", ios::trunc);

    if (!sortedQuestionFile.is_open() || !sortedAnswerFile.is_open()) {
        cout << "Error: Unable to open Questions.txt or Answers.txt for writing" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        sortedQuestionFile << questions[i] << endl;
        sortedAnswerFile << answers[i] << endl;
    }

    sortedQuestionFile.close();
    sortedAnswerFile.close();

    cout << "Flashcards sorted alphabetically by answers successfully!" << endl;
}

void scoreanalysis( string question,string answer){
	ofstream wrongquestions("wrongquestions.txt",ios::app);
    ofstream actualanswers("correctanswers.txt",ios::app);
    if(wrongquestions.is_open() && actualanswers.is_open())
    {
	wrongquestions<<question<<endl;
	actualanswers<<answer<<endl;
    }
    else
    cout<<"Error opening files"<<endl;
    wrongquestions.close();
    actualanswers.close();
}

void ViewScoreAnalysis()
{
	ifstream wrongquestions("wrongquestions.txt",ios::in);
	ifstream actualanswers("correctanswers.txt",ios::in);
	
	string question,answer;
	string questions[100];
	string answers[100];
	int size=0;
	int counts[100];
	if(wrongquestions.peek()==EOF||actualanswers.peek()==EOF)
	{
		cout<<"Files are Empty!"<<endl;
	}
	while(getline(wrongquestions,question)&&getline(actualanswers,answer))
	{
        bool found = false;
        for (int i=0; i<size; i++) 
		{
            if (questions[i] == question)
			 {
                counts[i]++;
                found = true;
                break;
            }
        }
        
        
        if (!found) 
		{
            questions[size] = question;
            answers[size] = answer;
            counts[size] = 1;
            size++;
        }
	}
	cout<<"Analysis of your performance"<<endl;
	for(int j=0;j<size;j++)
	{
		cout<<"Question: "<<questions[j]<<endl
		<<"Correct answer: "<<answers[j]<<endl
		<< "\033[31m"
		<<"Number of times wrongly answered : "<<counts[j]
		<<"\033[0m"
		<<endl;
		
	}
	
}
string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void trimInPlace(string &str) {
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
}

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


void deleteflashcard() {
    ifstream questionFile("Questions.txt");
    ifstream answerFile("Answers.txt");

    if (!questionFile.is_open() || !answerFile.is_open()) {
        cout << "Unable to open files!" << endl;
        return;
    }
    else if(questionFile.peek()==EOF||answerFile.peek()==EOF)
	{
		cout<<"Files are Empty!"<<endl;
	}

    string allQuestions = "", allAnswers = "";
    string question, answer;
    string lastQuestion, lastAnswer;

    while (getline(questionFile, question) && getline(answerFile, answer)) {
        lastQuestion = question;
        lastAnswer = answer;

        allQuestions += question + "\n";
        allAnswers += answer + "\n";
    }

    questionFile.close();
    answerFile.close();

    if (!allQuestions.empty()) {
        allQuestions.erase(allQuestions.size() - lastQuestion.size() - 1);
    }
    if (!allAnswers.empty()) {
        allAnswers.erase(allAnswers.size() - lastAnswer.size() - 1);
    }
    
    ofstream questionFileOut("Questions.txt", ios::trunc);
    ofstream answerFileOut("Answers.txt", ios::trunc);

    if (questionFileOut.is_open() && answerFileOut.is_open()) {
        questionFileOut << allQuestions;
        answerFileOut << allAnswers;
        cout << "Last flashcard deleted successfully." << endl;
    } else {
        cout << "Error: Unable to write to files!" << endl;
    }

    questionFileOut.close();
    answerFileOut.close();
}

void printpattern() {
    int size=6; 
    for (int i=size/2; i<=size; i+=2) {
        cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
        for (int j=1; j<size-i; j+=2) {
            cout << " ";
        }
        for (int j=1; j<=i; j++) {
            cout << "\033[31m*\033[0m";
        }
        for (int j=1; j<=size-i; j++) {
            cout << " ";
        }
        for (int j=1; j<=i; j++) {
            cout << "\033[31m*\033[0m";
        }
        cout<<endl;
    }
    for (int i=size; i>=1; i--) {
        cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
        for (int j=1; j<=size-i; j++) {
            cout << " ";
    }
        for (int j=1; j<=(2*i)-1; j++) {
            cout<<"\033[31m*\033[0m";
        }
        cout<<endl;
    }
}

float accuracy(string answer, string correctans){
	float total = answer.length();
	int correct = 0;
	int count = 0;
	while(answer[count]){
		if(answer[count] == correctans[count]){
			correct++;
		}
		count++;
	}
	float accuracy = 0;
	accuracy = (correct/total) * 100;
	return accuracy;
}

void scorehistory() {
    ifstream scoreHistoryFile("scorehistory.txt");
    
    if (!scoreHistoryFile.is_open()) {
        cout << "Unable to open scorehistory.txt" << endl;
        return;
    }

    string line;
    int quizNumber = 1;

    if (!(scoreHistoryFile >> line)) {
        cout << "No quizzes have been attempted yet." << endl;
    } else {
        cout << "Past Quiz Scores:" << endl;
        while (getline(scoreHistoryFile, line)) {
            cout << "Score for Quiz " << quizNumber << ": " << line << endl;
            quizNumber++;
       }
    }
}
    
void randomquiz(){
	
	int total= 0;
	cout<<"How many questions do you need in the quiz session?"<<endl;
	int numques;
	cin>>numques;
	fstream question;
	question.open("Questions.txt",ios::in);
	fstream answer;
	answer.open("Answers.txt",ios::in);
	fstream scorefile;
	scorefile.open("Scores.txt",ios::app);
	fstream scoreHistoryFile;
	scoreHistoryFile.open("ScoreHistory.txt", ios::app);
	int usedindex[numques] = {0};
	float score = 0;
	if(!(question.is_open()) || !(answer.is_open()) || !(scorefile.is_open()) || !(scoreHistoryFile.is_open()))
	{
		cout<<"Error opening files!"<<endl;
	}
	if((question.peek()==EOF) || (answer.peek()==EOF) || (scorefile.peek()==EOF) || (scoreHistoryFile.peek()==EOF))
	{
		cout<<"EMPTY FILES!"<<endl;
	}

	else{
		string temp;
		while(getline(question,temp)){
			total++;
		}
		question.clear();          
		question.seekg(0, ios::beg);  //moving the pointers of getline back to beginning of files :)
		answer.clear();
		answer.seekg(0, ios::beg);
		
	if(numques>total){
		int numdiff;
		numdiff = numques - total;
		cout<<"There are not enough questions in the file."<<endl;
		cout<<"Add "<< numdiff<<" more questions or shorten quiz length."<<endl;
		cin.ignore();
	}
	
	else{
		cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
		cout << "\033[33mPRESS ENTER TO MOVE TO THE NEXT QUESTION!\033[0m" << endl;
		int randnum;
		int count = 0;
		srand(time(0));
		
		while (count < numques) {
        
        question.clear();
        answer.clear();
        question.seekg(0, ios::beg);
        answer.seekg(0, ios::beg);

       	bool usedfound = 0 ;
       
        do{
        	usedfound = 0;
        	randnum = rand() % total;
        	for(int i = 0;i<count;i++){
        		if(usedindex[i]==randnum){
        			usedfound = 1;
        			break;
				}
			}
		}while(usedfound);
		
        usedindex[count] = randnum;
        
        string randomquestion, actualans;
        
        
        for (int i = 0; i <= randnum; i++) {
            getline(question, randomquestion);
            getline(answer, actualans);
        }

        cin.ignore(); 
        cout << randomquestion << endl;

       
        string matchans;
        
        getline(cin,matchans);

        
        trimInPlace(matchans);
        trimInPlace(actualans);
		//cout << "Your answer: '" << toLowerCase(matchans) << "'" << endl;
		//cout << "Correct answer: '" << toLowerCase(actualans) << "'" << endl; // these are debug statements ignore!
		float percentacc = 0;
		
		if(matchans.length() == actualans.length()){
			percentacc =accuracy(toLowerCase(matchans),toLowerCase(actualans));
			if(percentacc==100){
			cout << "\033[32mYOU GOT IT RIGHT!\033[0m" <<endl;  // Green
            score++;
			}
			else if(percentacc >= 80){
			cout << "\033[33mYOU MADE SOME MINOR MISTAKES!\033[0m" << endl;
				score = score + 0.7;
			}
			else if(percentacc>=50){
			cout << "\033[33mYOUR ANSWER WAS HALF OR PARTIALLY CORRECT!\033[0m" << endl;
				score = score + 0.5;
			}
			else{
			cout<< "\033[31mOH NO, YOU GOT IT TOO MUCH WRONG!\033[0m" <<endl; 
			}
		}
        else {
        	if(toLowerCase(matchans) == toLowerCase(actualans)){
        		cout << "\033[32mYOU GOT IT RIGHT!\033[0m" <<endl;  // Green
            	score++;
			}
			else{
				 cout<< "\033[31mOH NO, YOU GOT IT WRONG!\033[0m" <<endl;  // Red
            	 scoreanalysis(randomquestion,actualans);
			}
           }

        count++;
    }
    cout<<endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
 	cout << "\033[34mThe score of this session was: " << score << " out of : " << numques << "\033[0m" << endl;
	if(score == numques){
		cout<<"\033[35mGREAT JOB! YOU GOT A PERFECT SCORE!!\033[0m\n"<<endl;
		cout<<"\033[35mHERE'S A HEART FOR YOU!!\033[0m\n"<<endl;
		printpattern();
	}
	scorefile << score << "\n";
	scoreHistoryFile<<score<<"/"<<numques<<endl;
	}
	

}
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
	else if(question.peek()==EOF||answer.peek()==EOF)
	{
		cout<<"Files are Empty!"<<endl;
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
void searchbykeyword()
{
	string keyword;
	cout<<"Enter the keyword you want to search:"<<endl;
	getline(cin,keyword);
	string line1,line2;
	ifstream questionfile("Questions.txt");
	ifstream answerFile("Answers.txt");
	keyword = toLowerCase(keyword);
	if (!questionfile.is_open() || !answerFile.is_open()) 
	{
        cout << "Unable to open files!" << endl;
        return;
		}
	if((questionfile.peek())==EOF||(answerFile.peek())==EOF)
	{
		cout<<"EMPTY FILES"<<endl;
	}
	while(getline(questionfile,line1)&&getline(answerFile,line2))
	{
		string newline1=toLowerCase(line1);
		string newline2=toLowerCase(line2);
		if(newline1.find(keyword)!=string::npos || newline2.find(keyword)!=string::npos)
		{
			cout<<"\033[32mKeyword found!\033[0m"<<endl;
			cout<<"Question: "<<line1<<endl;
			cout<<"Answer:"<<line2<<endl;
		}
		
	}
}

void editquestion() {
    string fquestion;
    cout << "What is the Question you want to edit?" << endl;
    getline(cin, fquestion);  

   
    fquestion = toLowerCase(fquestion);

    fstream question;
    fstream answer;
    question.open("Questions.txt", ios::in);
    answer.open("Answers.txt", ios::in);

    if (!question.is_open() || !answer.is_open()) {
        cout << "One or more files not opening." << endl;
        return;
    }
    if((question.peek()==EOF) || (answer.peek()==EOF))
	{
		cout<<"EMPTY FILES!"<<endl;
	}

    string questionfile, temp, tempans, ansfile;
    string newquestion, newanswer;
    questionfile = "";
    ansfile = "";
    bool quesfound = false;

    while (getline(question, temp) && getline(answer, tempans)) {
        string trimmedTemp = temp;
        string trimmedFquestion = fquestion;

        
        trimInPlace(trimmedTemp);
        trimInPlace(trimmedFquestion);

        
        if (toLowerCase(trimmedTemp) == trimmedFquestion) {
            cout << "What is the new Question you wish to write?" << endl;
            getline(cin, newquestion);
            cout << "What is the new Answer you wish to write?" << endl;
            getline(cin, newanswer);
            temp = newquestion;
            tempans = newanswer;
            quesfound = true;
        }
        ansfile = ansfile + tempans + "\n";
        questionfile = questionfile + temp + "\n";
    }

    question.close();
    answer.close();

    question.open("Questions.txt", ios::out);
    answer.open("Answers.txt", ios::out);

    if (!question.is_open() || !answer.is_open()) {
        cout << "Error reopening files for writing." << endl;
        return;
    }

    question << questionfile;
    answer << ansfile;

    question.close();
    answer.close();

    if (quesfound) {
        cout << "Question and Answer updated successfully!" << endl;
    } else {
        cout << "Question was not found." << endl;
    }
}

bool admintry = 0;
void adminview(){
	string adminpass,temp;
	adminpass = "admin@123";
	cout<<"Confirm you are admin by entering the password."<<endl;
	cin>>temp;
	if(temp == adminpass){
		cout<<"Welcome Admin!"<<endl;
		int choice;
        do {
            cout << "\nAdmin Menu:" << endl;
            cout << "1 - List all files" << endl;
            cout << "2 - Clear all files" << endl;
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
		cin.ignore();
	}
}
void printoption(){
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
	cout << "FLASHCARD QUIZ PROGRAM" << endl;
	cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
    cout << "\033[33mIMPORTANT: FLASHCARDS ANSWERS ARE OF ONE WORD ONLY!!\033[0m\n"; // Yellow
    cout << "Which action do you want to perform?" << endl;
    cout << "01 - ADD A FLASHCARD" << endl;
    cout << "02 - DELETE A FLASHCARD" << endl;
    cout << "03 - RANDOM QUIZ" << endl;
    cout << "04 - SEARCH BY KEYWORD" << endl;
    cout << "05 - VIEW SCORES AND ANALYSIS" << endl;
    cout << "06 - VIEW ALL CARDS" << endl;
    cout << "07 - ADMIN VIEW" << endl;
    cout << "08 - EDIT A QUESTION" << endl;
    cout << "09 - SORT ANSWERS ALPHABETICALLY"<<endl;
    cout << "10 - VIEW SCORE HISTORY" <<endl;
    cout << "11 - EXIT THE PROGRAM"<<endl;
}
int main(){
    int choice;
   do {
   		printoption();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addflashcard();
                 cin.ignore();
                system("cls");
                break;
            case 2:
            	deleteflashcard();
            	cin.ignore();
                system("cls");
                break;
            case 3:
                randomquiz();
                cin.ignore();
                system("cls");
                break;
            case 4:
                searchbykeyword();
                cin.ignore();
                system("cls");
                break;
            case 5:
                ViewScoreAnalysis();
                cin.ignore();
                system("cls");
                break;
            case 6:
                viewflashcards();
                 cin.ignore();
                system("cls");
                break;
            case 7:
            	if(admintry==0){
            		adminview();
            		cin.ignore();
                	system("cls");
				}
                else{
                	 cout<<"Admin access has been blocked, as you entered the wrong password once."<<endl;
                	 cin.ignore();
                	 system("cls");
				}
                break;
            case 8:{
            	editquestion();
            	 cin.ignore();
                system("cls");
				break;
			}
				case 9:{
				sortFlashcardsAlphabetically();
				 cin.ignore();
                system("cls");
				break;
				}
                case 10:{
				scorehistory();
				 cin.ignore();
                system("cls");
				break;
                }
            case 11:
                {
                cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
				cout << "Exiting program. Goodbye!" << endl;
                break;
				}
            default:{
				cout << "ERROR: INVALID INPUT. Please try again." << endl;
				cin.clear();
				cin.ignore();
                break;
            }
        }
    } while (choice != 11);
    
    return 0;
}
