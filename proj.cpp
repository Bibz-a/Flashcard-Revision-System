#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
using namespace std;
void scoreanalysis( string question,string answer)
{
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
		cout<<"Question: "<<questions[j]<<endl<<
		"Correct answer: "<<answers[j]<<endl
		<< "\033[31m"
		<<"Number of times wrongly answered : "<<counts[j]
		<<"\033[0m"<<endl;
		
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

    string allQuestions = "", allAnswers = "";
    string question, answer;
    string lastQuestion, lastAnswer;

    // Read all lines and store the last question and answer separately
    while (getline(questionFile, question) && getline(answerFile, answer)) {
        lastQuestion = question;
        lastAnswer = answer;

        // Append the current lines to the strings
        allQuestions += question + "\n";
        allAnswers += answer + "\n";
    }

    questionFile.close();
    answerFile.close();

    // Remove the last question and answer from the strings
    if (!allQuestions.empty()) {
        size_t lastPos = allQuestions.rfind(lastQuestion);
        allQuestions = allQuestions.substr(0, lastPos);
    }
    if (!allAnswers.empty()) {
        size_t lastPos = allAnswers.rfind(lastAnswer);
        allAnswers = allAnswers.substr(0, lastPos);
    }

    // Overwrite the files with updated content
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
	int usedindex[numques] = {0};
	int score = 0;
	if(!(question.is_open()) || !(answer.is_open()) || !(scorefile.is_open()))
	{
		cout<<"Error opening files!"<<endl;
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
	}
	
	else{
		cout<<"PRESS ENTER TO MOVE TO NEXT QUESION!"<<endl;
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
        if (toLowerCase(actualans) == toLowerCase(matchans)) {
            cout << "\033[32mYOU GOT IT RIGHT!\033[0m" <<endl;  // Green
            score++;
        } else {
            cout<< "\033[31mOH NO, YOU GOT IT WRONG!\033[0m" <<endl;  // Red
            scoreanalysis(randomquestion,actualans);
            
        }

        count++;
    }
	}
	cout<<"The score of this session was: "<<score<< " out of : "<<numques<<endl;
	if(score == numques){
		cout<<"\033[35mGREAT JOB! YOU GOT A PERFECT SCORE!!\033[0m\n"<<endl;
	}
	scorefile << score << "\n";
	
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
	if (!questionfile.is_open() || !answerFile.is_open()) 
	{
        cout << "Unable to open files!" << endl;
        return;
		}
	
	while(getline(questionfile,line1)&&getline(answerFile,line2))
	{
		if(line1.find(keyword)!=string::npos || line2.find(keyword)!=string::npos)
		{
			cout<<"Keyword found!"<<endl;
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
    cout << "\033[33mIMPORTANT: FLASHCARDS ANSWERS ARE OF ONE WORD ONLY!!\033[0m\n"; // Yellow
    cout << "Which action do you want to perform?" << endl;
    cout << "1 - ADD A FLASHCARD" << endl;
    cout << "2 - DELETE A FLASHCARD" << endl;
    cout << "3 - RANDOM QUIZ" << endl;
    cout << "4 - SEARCH BY KEYWORD" << endl;
    cout << "5 - VIEW SCORES AND ANALYSIS" << endl;
    cout << "6 - VIEW ALL CARDS" << endl;
    cout << "7 - ADMIN VIEW" << endl;
    cout << "8 - EDIT A QUESTION" << endl;
    cout << "9 - EXIT" <<endl;
   do {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addflashcard();
                break;
            case 2:
            	deleteflashcard();
                break;
            case 3:
                randomquiz();
                break;
            case 4:
                searchbykeyword();
                break;
            case 5:
                ViewScoreAnalysis();
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
            case 8:{
            	editquestion();
				break;
			}
            case 9:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "ERROR: INVALID INPUT. Please try again." << endl;
                break;
        }
    } while (choice != 9);
    
    return 0;
}
