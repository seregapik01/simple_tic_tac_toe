/*********************************************
    Настраиваемые правила игры:
    1) размерность поля от 3*3 до 5*5
    2) количество клеток в ряд необходимых для выигрыша зависит от размерности поля (3*3 - 3 в ряд; 5*5 - 5 в ряд)
    3) режимы игры:
        А) игрок против компьютера
        Б) игрок против игрока
        В) компьютер против компьютера ( демо режим )

    если компьютер ходит первым - должен либо побеждать либо играть в ничью,
    если компьютер ходит вторым - максимально усложнять жизнь игроку

**********************************************/

#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;


vector<string> v {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25"};

int lose_choice(vector<string> v);
int win_choice(vector<string> v);

void free_slot_5x5(short int& result,vector<string> v);
void free_slot(short int& result,vector<string> v);
void last_move_and_lost(short int& result,vector<string> v);
void last_move_and_win(short int &result,vector<string> v);
void last_move_and_win_5x5(short int& result,vector<string> v);

int bot_3x3(int first_or_not,vector<string> & v);
int bot_5x5(int first_or_not,vector<string> & v);

int checkwin(int mod);

void board_3(int mod);
void board_5(int mod);

void start_game_3(int mod,int pole);
void start_game_5(int mod,int pole);

int game_mode(std::istream& stream);
                  
int main()                      
{
    cout<<"Выберите размерность поля \n1)3*3\n2)5*5\n";
    int pole =  game_mode(std::cin);
    system("clear");
    cout<<"Выберите режимы игры \n1)игрок против компьютера\n2)игрок против игрока\n3)компьютер против компьютера ( демо режим )\n";
    int mod =  game_mode(std::cin);
    system("clear");
    //start_game_5
    if(pole==1)
        start_game_3(mod,pole);
    if(pole==2)
        start_game_5(mod,pole);
}                                                      

/*******************************************************************
    ФУНКЦИИ ОТРИСОВКИ ПОЛЯ
********************************************************************/

void board_3(int mod)
{      
    system ("clear");
    cout << "\n\n\tКрестики нолики 3*3\n\n";
    if(mod==1){cout << "Игрок 1 (X)  -  bot 2 (O)" << endl << endl;}
    if(mod==2){cout << "Игрок 1 (X)  -  Игрок 2 (O)" << endl << endl;}
    if(mod==3){cout << "bot 1 (X)  -  bot 2 (O)" << endl << endl;}
    //cout << "Игрок 1 (X)  -  Игрок 2 (O)" << endl << endl;
    cout << endl;

    cout << "     |     |     " << endl;
    cout << "  " << v[1] << "  |  " << v[2] << "  |  " << v[3] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << v[4] << "  |  " << v[5] << "  |  " << v[6] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << v[7] << "  |  " << v[8] << "  |  " << v[9] << endl;

    cout << "     |     |     " << endl << endl;
}

void board_5(int mod)
{
    system ("clear");
    cout << "\n\n\tКрестики нолики 5*5\n\n";
    if(mod==1){cout << "Игрок 1 (X)  -  bot 2 (O)" << endl << endl;}
    if(mod==2){cout << "Игрок 1 (X)  -  Игрок 2 (O)" << endl << endl;}
    if(mod==3){cout << "bot 1 (X)  -  bot 2 (O)" << endl << endl;}
    //cout << "Игрок 1 (X)  -  Игрок 2 (O)" << endl << endl;
    
    cout << endl;

    cout << "                |               |               |               |               " << endl;
    cout << "\t" << v[1] << "\t|\t" << v[2] << "\t|\t" << v[3] <<"\t|\t" << v[4] << "\t|\t" << v[5] << endl;

    cout << "________________|_______________|_______________|_______________|_______________" << endl;
    cout << "                |               |               |               |               " << endl;

    cout << "\t" << v[6] << "\t|\t" << v[7] << "\t|\t" << v[8] <<"\t|\t" << v[9] << "\t|\t" << v[10] << endl;

    cout << "________________|_______________|_______________|_______________|_______________"  << endl;
    cout << "                |               |               |               |               " << endl;

    cout << "\t" << v[11] << "\t|\t" << v[12] << "\t|\t" << v[13] <<"\t|\t" << v[14] << "\t|\t" << v[15] << endl;

    cout << "________________|_______________|_______________|_______________|_______________"  << endl;
    cout << "                |               |               |               |               " << endl;

    cout << "\t" << v[16] << "\t|\t" << v[17] << "\t|\t" << v[18] <<"\t|\t" << v[19] << "\t|\t" << v[20] << endl;

    cout << "________________|_______________|_______________|_______________|_______________"  << endl;
    cout << "                |               |               |               |               " << endl;

    cout << "\t" << v[21] << "\t|\t" << v[22] << "\t|\t" << v[23] <<"\t|\t" << v[24] << "\t|\t" << v[25] << endl;
    cout << "                |               |               |               |               " << endl;
}

/************************************************************************
    ФУНКЦИИ ЗАПУСКА ИГРОВОЙ СЕССИИ В ЗАВИСИМОСТИ ОТ ВЫБОРА РЕЖИМА И ПОЛЯ
*************************************************************************/

/************************************************************************
      __1__|__2__|__3__
      __4__|__5__|__6__
        7  |  8  |  9     


        3x3 ПОЛЕ
*************************************************************************/

void start_game_3(int mod,int pole)
{
    srand(time(0));
    int player = rand() % 2 + 1,i,choice;
    short int first_player_or_bot = player;
    
    //char mark;
    string mark;
            

    if(mod==1) /*  ИГРОК ПРОТИВ КОМПЬЮТЕРА  */
    {   
        /* 1 - player  2 - bot */
        //string Gamer = "X", bot = "O"; 

        do
        {
            board_3(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            if(player==2)
                choice = bot_3x3(first_player_or_bot,v);
            else
            {
               cin >> choice;
            }
            
            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(1);

            player++;
        }while(i==-1);

    board_3(mod);
    if(i==1)

        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }

    if(mod==2)  /*  ИГРОК ПРОТИВ ИГРОКА  */
    {
        do
        {
            board_3(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            cin >> choice;

            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(1);

            player++;
        }while(i==-1);

    board_3(mod);
    if(i==1)

        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }
    
    if(mod==3) /*  КОМПЬЮТЕР ПРОТИВ КОМПЬЮТЕРА ( ДЕМО РЕЖИМ )  */
    {
        do
        {
            board_3(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            if(player==2)
                choice = bot_3x3(first_player_or_bot,v);
            else
            {
               choice = bot_3x3(first_player_or_bot,v);
            }
            
            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(1);

            player++;
        }while(i==-1);

    board_3(mod);
    if(i==1)

        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }
}

/************************************************************************
      ___1__|___2__|__3___|__4___|___5__
      ___6__|___7__|__8___|__9___|__10__
      __11__|__12__|__13__|__14__|__15__
      __16__|__17__|__18__|__19__|__20__
        21  |  22  |  23  |  24  |  25  

        5x5 ПОЛЕ
*************************************************************************/
void start_game_5(int mod,int pole)
{
    srand(time(0));
    int player = rand() % 2 + 1,i,choice;
    short int first_player_or_bot = player;
    
    //char mark;
    string mark;
    //int player = 1,i,choice;
    //char mark;

    if(mod==1) /*  ИГРОК ПРОТИВ КОМПЬЮТЕРА  */
    {
        do
        {
            board_5(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            if(player==2)
                choice = bot_5x5(first_player_or_bot,v);
            else
            {
               cin >> choice;
            }
            
            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else if (choice == 10 && v[10] == "10") {v[10] = mark;}
            else if (choice == 11 && v[11] == "11") {v[11] = mark;}
            else if (choice == 12 && v[12] == "12") {v[12] = mark;}
            else if (choice == 13 && v[13] == "13") {v[13] = mark;}
            else if (choice == 14 && v[14] == "14") {v[14] = mark;}
            else if (choice == 15 && v[15] == "15") {v[15] = mark;}
            else if (choice == 16 && v[16] == "16") {v[16] = mark;}
            else if (choice == 17 && v[17] == "17") {v[17] = mark;}
            else if (choice == 18 && v[18] == "18") {v[18] = mark;}
            else if (choice == 19 && v[19] == "19") {v[19] = mark;}
            else if (choice == 20 && v[20] == "20") {v[20] = mark;}
            else if (choice == 21 && v[21] == "21") {v[21] = mark;}
            else if (choice == 22 && v[22] == "22") {v[22] = mark;}
            else if (choice == 23 && v[23] == "23") {v[23] = mark;}
            else if (choice == 24 && v[24] == "24") {v[24] = mark;}
            else if (choice == 25 && v[25] == "25") {v[25] = mark;}
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(2);

            player++;
        }while(i==-1);

    board_5(mod);
    if(i==1)
        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }

    if(mod==2)  /*  ИГРОК ПРОТИВ ИГРОКА  */
    {
        do
        {
            board_5(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            cin >> choice;

            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else if (choice == 10 && v[10] == "10") {v[10] = mark;}
            else if (choice == 11 && v[11] == "11") {v[11] = mark;}
            else if (choice == 12 && v[12] == "12") {v[12] = mark;}
            else if (choice == 13 && v[13] == "13") {v[13] = mark;}
            else if (choice == 14 && v[14] == "14") {v[14] = mark;}
            else if (choice == 15 && v[15] == "15") {v[15] = mark;}
            else if (choice == 16 && v[16] == "16") {v[16] = mark;}
            else if (choice == 17 && v[17] == "17") {v[17] = mark;}
            else if (choice == 18 && v[18] == "18") {v[18] = mark;}
            else if (choice == 19 && v[19] == "19") {v[19] = mark;}
            else if (choice == 20 && v[20] == "20") {v[20] = mark;}
            else if (choice == 21 && v[21] == "21") {v[21] = mark;}
            else if (choice == 22 && v[22] == "22") {v[22] = mark;}
            else if (choice == 23 && v[23] == "23") {v[23] = mark;}
            else if (choice == 24 && v[24] == "24") {v[24] = mark;}
            else if (choice == 25 && v[25] == "25") {v[25] = mark;}
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(2);

            player++;
        }while(i==-1);

    board_5(mod);
    if(i==1)

        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }
    
    if(mod==3) /*  КОМПЬЮТЕР ПРОТИВ КОМПЬЮТЕРА ( ДЕМО РЕЖИМ )  */
    {
        do
        {
            board_5(mod);
            player=(player%2)?1:2;

            cout << "Игрок " << player << ", enter a number:  ";
            if(player==2)
                choice = bot_5x5(first_player_or_bot,v);
            else
            {
               choice = bot_5x5(first_player_or_bot,v);
            }
            
            mark=(player == 1) ? 'X' : 'O';

            if (choice == 1 && v[1] == "1")         {v[1] = mark;}
            else if (choice == 2 && v[2] == "2")    {v[2] = mark;}
            else if (choice == 3 && v[3] == "3")    {v[3] = mark;}
            else if (choice == 4 && v[4] == "4")    {v[4] = mark;}
            else if (choice == 5 && v[5] == "5")    {v[5] = mark;}
            else if (choice == 6 && v[6] == "6")    {v[6] = mark;}
            else if (choice == 7 && v[7] == "7")    {v[7] = mark;}
            else if (choice == 8 && v[8] == "8")    {v[8] = mark;}
            else if (choice == 9 && v[9] == "9")    {v[9] = mark;}
            else if (choice == 10 && v[10] == "10") {v[10] = mark;}
            else if (choice == 11 && v[11] == "11") {v[11] = mark;}
            else if (choice == 12 && v[12] == "12") {v[12] = mark;}
            else if (choice == 13 && v[13] == "13") {v[13] = mark;}
            else if (choice == 14 && v[14] == "14") {v[14] = mark;}
            else if (choice == 15 && v[15] == "15") {v[15] = mark;}
            else if (choice == 16 && v[16] == "16") {v[16] = mark;}
            else if (choice == 17 && v[17] == "17") {v[17] = mark;}
            else if (choice == 18 && v[18] == "18") {v[18] = mark;}
            else if (choice == 19 && v[19] == "19") {v[19] = mark;}
            else if (choice == 20 && v[20] == "20") {v[20] = mark;}
            else if (choice == 21 && v[21] == "21") {v[21] = mark;}
            else if (choice == 22 && v[22] == "22") {v[22] = mark;}
            else if (choice == 23 && v[23] == "23") {v[23] = mark;}
            else if (choice == 24 && v[24] == "24") {v[24] = mark;}
            else if (choice == 25 && v[25] == "25") {v[25] = mark;}

                
            else
            {
                cout<<"Invalid move ";

                player--;
                cin.ignore();
                cin.get();
            }
            i=checkwin(2);

            player++;
        }while(i==-1);

    board_5(mod);
    if(i==1)
        cout<<"==>\aИгрок "<<--player<<" Выиграл ";
    else
        cout<<"==>\aНичья";

    cin.ignore();
    cin.get();
    }
    }



/************************************************************************
    ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ  game_mode,checkwin
*************************************************************************/

bool random_bool()
{
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

int game_mode(std::istream& stream)
{
    int mode;
    stream >> mode;
    if(mode == 1)
        return 1;

    if(mode == 2)
        return 2;

    if(mode == 3)
        return 3;
    else
        return -1;
}

int checkwin(int pole)
{
    int result = -3;
    
    if(pole==1)
    {
        if (v[1] == v[2] && v[2] == v[3])

            result = 1;
        else if (v[4] == v[5] && v[5] == v[6])

            result = 1;
        else if (v[7] == v[8] && v[8] == v[9])

            result = 1;
        else if (v[1] == v[4] && v[4] == v[7])

            result = 1;
        else if (v[2] == v[5] && v[5] == v[8])

            result = 1;
        else if (v[3] == v[6] && v[6] == v[9])

            result = 1;
        else if (v[1] == v[5] && v[5] == v[9])

            result = 1;
        else if (v[3] == v[5] && v[5] == v[7])

            result = 1;
        else if (v[1] != "1" && v[2] != "2" && v[3] != "3" 
              && v[4] != "4" && v[5] != "5" && v[6] != "6" 
              && v[7] != "7" && v[8] != "8" && v[9] != "9")
            result = 0;
        else
            result = -1;
    }
    
    if(pole==2)
    {
        if(v[1]==v[2]&&v[2]==v[3]&&v[3]==v[4]&&v[4]==v[5]        || v[6]==v[7]&&v[7]==v[8]&&v[8]==v[9]&&v[9]==v[10]       ||
        v[11]==v[12]&&v[12]==v[13]&&v[13]==v[14]&&v[14]==v[15]   || v[16]==v[17]&&v[17]==v[18]&&v[18]==v[19]&&v[19]==v[20]||
        v[21]==v[22]&&v[22]==v[23]&&v[23]==v[24]&&v[24]==v[25]   || v[5]==v[9]&&v[9]==v[13]&&v[13]==v[17]&&v[17]==v[21]   ||
           v[1]==v[6]&&v[6]==v[11]&&v[11]==v[16]&&v[16]==v[21]   || v[2]==v[7]&&v[7]==v[12]&&v[12]==v[17]&&v[17]==v[22]   ||
           v[3]==v[8]&&v[8]==v[13]&&v[13]==v[18]&&v[18]==v[23]   || v[4]==v[9]&&v[9]==v[14]&&v[14]==v[19]&&v[19]==v[24]   ||
           v[5]==v[10]&&v[10]==v[15]&&v[15]==v[20]&&v[20]==v[25] || v[1]==v[7]&&v[7]==v[13]&&v[13]==v[19]&&v[19]==v[25] )  
            result = 1;

        else if (v[1] != "1" && v[2] != "2" && v[3] != "3" && v[4] != "4" &&v[5] != "5" && v[6] != "6" && v[7] != "7" && 
                v[8] != "8" && v[9] != "9" && v[10] != "10" && v[11] != "11" && v[12] != "12" && v[13] != "13" && v[14] != "14" &&
                v[15] != "15" && v[16] != "16" && v[17] != "17" && v[18] != "18" && v[19] != "19" && v[20] != "20" && v[21] != "21" &&
                v[22] != "22" && v[23] != "23" && v[24] != "24" && v[25] != "25")
                result = 0;
        else
            result = -1;
    }
    return result;
}


int bot_3x3(int first_or_not,vector<string> & v) 
{
    short int result = 1;
    short int count_move = 0;
    if(first_or_not==2)
    {
        
        if(v[9]=="9")
        {
           
            result = 9;
        }
        else if(v[5]!="X")
        {
            if(v[8]!="X")
            {
                if(v[7]!="X")
                {
                    if(v[7]!="O")
                        result = 7;
                }
                else if(v[3]!="X")
                {
                    if(v[3]!="O")
                        result = 3;
                }
                else if(v[1]!="O")
                {
                    if(v[1]!="X")
                        result = 1;
                }   
            }  
        }
        else if(v[5]=="X")
        {
            if(v[8]!="X")
            {
                if(v[7]!="X")
                {
                    if(v[7]!="O")
                        result = 7;
                }
                else if(v[3]!="X")
                {
                    if(v[3]!="O")
                        result = 3;
                }
                else if(v[1]!="O")
                {
                    if(v[1]!="X")
                        result = 1;
                }   
            }  
        }
    }
    last_move_and_lost(result,v);     //  если компьютер ходит первым - должен либо побеждать либо играть в ничью,
    if(first_or_not==2)    //  если компьютер ходит вторым - максимально усложнять жизнь игроку  (выключаем приоритет выйграть раунд и делаем ничью)
        last_move_and_win(result,v);
    if (v[result]!="O"&&v[result]!="X")
        return result;
    else
    {
        free_slot(result,v);
        return result;
    }
    
}

int bot_5x5(int first_or_not,vector<string> & v) 
{
    short int result = 1;
    last_move_and_win_5x5(result,v);
    int last = win_choice(v);
    if (v[last]==to_string(last))
    {
        if(first_or_not == 1)
            result = last;
    }
    int lose = lose_choice(v);
    
    if (first_or_not==2) //если компьютер ходит вторым - максимально усложнять жизнь игроку
    {
        if (v[lose]==to_string(lose))
        {
            result =lose;
        }
    }
    
        
    return result;
} 

void last_move_and_win(short int& result,vector<string> v)
{
    if(v[1]=="O"&&v[2]=="O"){result = 3;}
    else if(v[3]=="O"&&v[2]=="O"){result = 1;}
    else if(v[3]=="O"&&v[6]=="O"){result = 9;}
    else if(v[9]=="O"&&v[6]=="O"){result = 3;}
    else if(v[9]=="O"&&v[8]=="O"){result = 7;}
    else if(v[7]=="O"&&v[8]=="O"){result = 9;}
    else if(v[7]=="O"&&v[4]=="O"){result = 1;}
    else if(v[1]=="O"&&v[4]=="O"){result = 7;}
    else if(v[2]=="O"&&v[5]=="O"){result = 8;}
    else if(v[8]=="O"&&v[5]=="O"){result = 2;}
    else if(v[3]=="O"&&v[5]=="O"){result = 7;}
    else if(v[7]=="O"&&v[5]=="O"){result = 3;}
    else if(v[1]=="O"&&v[5]=="O"){result = 9;}
    else if(v[9]=="O"&&v[5]=="O"){result = 1;}
    else if(v[4]=="O"&&v[5]=="O"){result = 6;}
    else if(v[6]=="O"&&v[5]=="O"){result = 4;}
    else if(v[1]=="O"&&v[3]=="O"){result = 2;}
    else if(v[1]=="O"&&v[9]=="O"){result = 5;}
    else if(v[1]=="O"&&v[7]=="O"){result = 4;}
    else if(v[2]=="O"&&v[8]=="O"){result = 5;}
    else if(v[4]=="O"&&v[6]=="O"){result = 5;}
    else if(v[3]=="O"&&v[9]=="O"){result = 6;}
    else if(v[7]=="O"&&v[9]=="O"){result = 8;}
    else if(v[3]=="O"&&v[7]=="O"){result = 5;}
        
}

void last_move_and_win_5x5(short int& result,vector<string> v)
{
    free_slot_5x5(result,v);
}

void last_move_and_lost(short int& result,vector<string> v)
{
    string val = "X";
    if(v[1]==val&&v[2]==val)     {result = 3;}
    else if(v[3]==val&&v[2]==val){result = 1;}
    else if(v[3]==val&&v[6]==val){result = 9;}
    else if(v[9]==val&&v[6]==val){result = 3;}
    else if(v[9]==val&&v[8]==val){result = 7;}
    else if(v[7]==val&&v[8]==val){result = 9;}
    else if(v[7]==val&&v[4]==val){result = 1;}
    else if(v[1]==val&&v[4]==val){result = 7;}
    else if(v[2]==val&&v[5]==val){result = 8;}
    else if(v[8]==val&&v[5]==val){result = 2;}
    else if(v[3]==val&&v[5]==val){result = 7;}
    else if(v[7]==val&&v[5]==val){result = 3;}
    else if(v[1]==val&&v[5]==val){result = 9;}
    else if(v[9]==val&&v[5]==val){result = 1;}
    else if(v[4]==val&&v[5]==val){result = 6;}
    else if(v[6]==val&&v[5]==val){result = 4;}
    else if(v[1]==val&&v[3]==val){result = 2;}
    else if(v[1]==val&&v[9]==val){result = 5;}
    else if(v[1]==val&&v[7]==val){result = 4;}
    else if(v[2]==val&&v[8]==val){result = 5;}
    else if(v[4]==val&&v[6]==val){result = 5;}
    else if(v[3]==val&&v[9]==val){result = 6;}
    else if(v[7]==val&&v[9]==val){result = 8;}
    else if(v[3]==val&&v[7]==val){result = 5;}
}
void free_slot(short int& result,vector<string> v)  // находит свободный слот и меняет result
{
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        if (v[i] == "1")    {result = 1;}
        else if(v[i] == "2"){result = 2;}
        else if(v[i] == "3"){result = 3;}
        else if(v[i] == "4"){result = 4;}
        else if(v[i] == "5"){result = 5;}
        else if(v[i] == "6"){result = 6;}
        else if(v[i] == "7"){result = 7;}
        else if(v[i] == "8"){result = 8;}
        else if(v[i] == "9"){result = 9;}
    }
}

void free_slot_5x5(short int& result,vector<string> v)  // находит свободный слот и меняет result
{
    bool stop = true;
    while (stop == true)
    {
        srand(time(0) + 1);
        short int i = rand() % 25 +1;

        if (v[i] == "1")    {stop = false;result = 1;}          

        else if(v[i] == "2") {stop = false;result = 2;}
        else if(v[i] == "3") {stop = false;result = 3;}
        else if(v[i] == "4") {stop = false;result = 4;}
        else if(v[i] == "5") {stop = false;result = 5;}
        else if(v[i] == "6") {stop = false;result = 6;}
        else if(v[i] == "7") {stop = false;result = 7;}
        else if(v[i] == "8") {stop = false;result = 8;}
        else if(v[i] == "9") {stop = false;result = 9;}
        else if(v[i] == "10"){stop = false;result = 10;}
        else if(v[i] == "11"){stop = false;result = 11;}
        else if(v[i] == "12"){stop = false;result = 12;}
        else if(v[i] == "13"){stop = false;result = 13;}
        else if(v[i] == "14"){stop = false;result = 14;}
        else if(v[i] == "15"){stop = false;result = 15;}
        else if(v[i] == "16"){stop = false;result = 16;}
        else if(v[i] == "17"){stop = false;result = 17;}
        else if(v[i] == "18"){stop = false;result = 18;}    
        else if(v[i] == "19"){stop = false;result = 19;}  
        else if(v[i] == "20"){stop = false;result = 20;}
        else if(v[i] == "21"){stop = false;result = 21;}
        else if(v[i] == "22"){stop = false;result = 22;}
        else if(v[i] == "23"){stop = false;result = 23;}                 
        else if(v[i] == "24"){stop = false;result = 24;}
        else if(v[i] == "25"){stop = false;result = 25;}

        else {result -1;}

    }
    
    
    
}

/************************************************************************
    поле 5x5 - 12 функций для того что бы сделать последний победный ход
    или прервать победную серию игрока
*************************************************************************/

int win_choice(vector<string> v)
{
    string bot = "O";
    string player = "X";
    int arr[12][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25},{1,7,13,19,15},
                       {1,6,11,16,21},{2,7,12,17,22},{3,8,13,18,23},{4,9,14,19,24},{5,10,15,20,25},{5,9,13,17,21}};
    int count = 0;
    int result = -1;
    for (size_t i = 0; i < 5; i++)
    {
        if(v[arr[i][1]] =="X")
            result == 0;
    }
    if(result == -1)
    {
    for (size_t i = 0; i < 12; i++)
        for(size_t c = 0; c < 5; c++)
            {
                if(v[arr[i][c]]==to_string(arr[i][c]))
                    {
                        result = arr[i][c];
                    }
                }
                count = 0;
            }
    return result;
}

int lose_choice(vector<string> v)
{
    string bot = "X";
    string player = "O";
    int arr[12][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25},{1,7,13,19,15},
                       {1,6,11,16,21},{2,7,12,17,22},{3,8,13,18,23},{4,9,14,19,24},{5,10,15,20,25},{5,9,13,17,21}};
    int count = 0;
    int result = -1;
    for (size_t i = 0; i < 5; i++)
    {
        if(v[arr[i][1]] =="O")
            result == 0;
    }
    if(result == -1)
    {
    for (size_t i = 0; i < 12; i++)
        for(size_t c = 0; c < 5; c++)
            {
                if(v[arr[i][c]]==to_string(arr[i][c]))
                    {
                        result = arr[i][c];
                    }
                }
                count = 0;
            }
    return result;
}

