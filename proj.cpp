#include <iostream>
#include <fstream>
using namespace std;
void addflashcard(){
    //just testing
}
int main(){
    int choice;
    cout<<"FLASHCARD QUIZ PROGRAM"<<endl;
    cout<<"Which action do you want to perform: 1 - ADD A FLASHCARD , 2 - DELETE A FLASHCARD , 3-RANDOM QUIZ , 4-EXIT"<<endl;
    do{
        cin>>choice;
        switch(choice){
        case 1:{
        //addflashcard();
        break;
        }
        case 2:{
        //deleteflashcard();
        break;
        }
        case 3:{
            //quiz();
        }
        default:
        cout<<"ERROR INVALID INPUT."<<endl;
    }
    }while(choice!=4);
    
    return 0;
}