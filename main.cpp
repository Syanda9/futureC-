/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Syanda
 *
 * Created on 12 March 2023, 8:38 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"
#include "agent.cpp"
#include "cell.cpp"
#include "board.cpp"

using namespace std;

int main(int argc, char** argv) {
        time_t now = time(NULL);
        srand(now);
        cout<<"Seed: "<<now<<endl;
        board abalone;
        string lastState="";
        string state(abalone);
        cout<<"Initial State:"<<endl<<state;
        agent* w = new randAgent('O');
        agent* b = new distAgent('@');
        movement* pom=nullptr;//previous opponent's move
        movement* mym=nullptr;//player's chosen move
        char c='O';
        ofstream moves ("Moves.txt");
        ofstream winner ("Results.txt");
        while(abalone.inPlay()==true){
            
            try{
                if(c=='O'){
                    movement mm = w->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
                else{
                    movement mm = b->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
            }
            catch(const string& s){
                cout<<s;
                return 1;
            }        
            bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
            cout<<"Move "<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
            if(valid){
                string state(abalone);      
                moves<< "Move "<<": "<<" "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;  
                cout<<"Next State:"<<endl<<state;
                lastState= state;
                
            }
            else{
                cout<<"Invalid move!!"<<endl;
            }
            if(c=='O') 
                c='@';
            else
                c='O'; 
            delete mym;
            SLP(1);
            //system(CL);
        }
        if (abalone.winner()=='O'){
            winner<<" Whites marbles won"<<endl;
            winner<<lastState<<endl;
        }else{
            winner<<" black marbles won"<<endl;
        }
        moves.close();
        if(pom)
            delete pom;
        delete w;
        delete b; 
        
        return 0;
}

