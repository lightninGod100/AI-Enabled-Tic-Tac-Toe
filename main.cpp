// Main Code File //

#include<bits/stdc++.h>
using namespace std;

#define P1 'X'
#define P2 'O'

class game{
    private:
        // Game Variables
        vector<vector<char>> board;    // Game Board
        int side;                      // Side of Board
        char curr_turn;                // Current Turn
        int move_no;                   // Move Number
        bool is_pvp;                   // Game Mode: true for PvP, false for PvC
        bool player_first;             // In PvC mode: true if player goes first, false if computer goes first
        char player_symbol;            // Symbol used by the player in PvC mode
        char computer_symbol;          // Symbol used by the computer in PvC mode

        // Game Methods
        void showboard(bool game_started);   // Display Game Board
        bool is_victory();                  // Does Victory Achieved?
        void victory_message();             // Victory Message
        pair<int,int> bestMove();           // Best Move for Computer
        int minimax(bool isCompTurn, int depth, int alpha, int beta); // Best Score for a Move
        void input();                       // to get player input
        void computer_move();               // to get computer input
        void start_screen();                 // to select game mode (PvP or PvC)
        void select_first_player();         // to select who goes first in PvC mode
        void play_pvp();                    // Player vs Player game flow
        void play_pvc();                    // Player vs Computer game flow
        int end_game_menu();                // End game menu for options after game over
        void handle_end_game();             // Handle user choice from end game menu

    public:
        // Constructor Initialises Game Data
        game(){
            side = 3;
            board = vector<vector<char>>(side, vector<char>(side, '*'));
            curr_turn = P1;
            move_no = 0; // Start from move 0
            is_pvp = false; // Default to PvC mode
            player_first = true; // Default to player going first
            player_symbol = P1; // Default player symbol
            computer_symbol = P2; // Default computer symbol
        }

        void game_master(); // Will control the whole game flow
};

///////////////////////////////////////////////////////////////////////////////////

void game::start_screen() {
    int choice = 0;
    bool valid_choice = false;
    
    cout << "\n===== TIC TAC TOE =====\n\n";
    cout << "Select Game Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Computer\n";
    cout << "3. Exit\n\n";

    while (!valid_choice) {
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        
        if (cin.fail() || (choice < 1 || choice > 3)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
             cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        } else {
            valid_choice = true;
        }
    }
    
    if (choice == 3) {
        cout << "Thanks for visiting! Goodbye." << endl;
        exit(0);  // Exit the program
    }

    is_pvp = (choice == 1);
    
    // Display the selected mode
    cout << "\nSelected mode: " << (is_pvp ? "Player vs Player" : "Player vs Computer") << "\n";
    cout << "Get ready to play!\n\n";
}

void game::select_first_player() {
    int choice = 0;
    bool valid_choice = false;
    
    cout << "\nWho should go first?\n";
    cout << "1. You (Player)\n";
    cout << "2. Computer\n\n";
    
    while (!valid_choice) {
        cout << "Enter your choice (1-2): ";
        cin >> choice;
        
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice. Please enter 1 or 2.\n";
        } else {
            valid_choice = true;
        }
    }
    
    player_first = (choice == 1);
    
    // Set symbols based on who goes first
    if (player_first) {
        player_symbol = P1;    // Player is X
        computer_symbol = P2;  // Computer is O
    } else {
        player_symbol = P2;    // Player is O
        computer_symbol = P1;  // Computer is X
    }
    
    // Display the selection
    cout << "\n" << (player_first ? "You" : "Computer") << " will go first.\n";
    cout << "Your symbol: " << player_symbol << "\n";
    cout << "Computer's symbol: " << computer_symbol << "\n\n";
}

int game::end_game_menu() {
    int choice = 0;
    bool valid_choice = false;
    
    cout << "\n===== GAME OVER =====\n\n";
    cout << "What would you like to do?\n";
    cout << "1. Restart Game\n";
    cout << "2. Return to Main Menu\n";
    cout << "3. Exit\n\n";
    
    while (!valid_choice) {
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        
        if (cin.fail() || (choice < 1 || choice > 3)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        } else {
            valid_choice = true;
        }
    }
    
    return choice;
}

void game::handle_end_game() {
    int choice = end_game_menu();
    
    switch(choice) {
        case 1: // Restart
            cout << "\nThe game is restarting...\n" << endl;
            // Reset the board and game state
            board = vector<vector<char>>(side, vector<char>(side, '*'));
            move_no = 0;
            
            // Restart the current game mode
            if(is_pvp) {
                curr_turn = P1;  // In PvP, always start with P1
                play_pvp();
            } else {
                // For PvC, ask again who goes first
                select_first_player();
                play_pvc();
            }
            break;
            
        case 2: // Return to main menu
            // Reset game state
            board = vector<vector<char>>(side, vector<char>(side, '*'));
            move_no = 0;
            curr_turn = P1;
            
            // Return to game_master to select mode again
            game_master();
            break;
            
        case 3: // Exit
            cout << "Thanks for playing! Goodbye." << endl;
            exit(0);  // Exit the program
            break;
    }
}

void game::showboard(bool game_started){
    cout<<"\n";

    // Before Start of Game
    if(!game_started){
        cout<<"Press Corresponding Number to enter your input"<<endl<<endl;
        for(int i=1; i<10; i=i+3){
            cout<<i<<" | "<<i+1<<" | "<<i+2<<endl;
            if(i<6) cout<<"---------"<<endl;
        }
    }

    // After Game has started
    if(game_started){
        for(int i=0; i<3; i++){
            cout<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2]<<endl;
            if(i<2) cout<<"---------"<<endl;
        }
    }

    cout<<endl;
}

bool game::is_victory(){
    // Check rows
    for(int i=0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }

    // Check columns
    for(int i=0; i<3; i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }

    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != '*')
        return true;

    return false;
}

void game::victory_message(){
    if(is_pvp) {
        // PvP mode victory message
        if(curr_turn == P1) {
            cout << "***---***--- Player P1 (" << P1 << ") Won ---***---***";
        } else {
            cout << "***---***--- Player P2 (" << P2 << ") Won ---***---***";
        }
    } else {
        // PvC mode victory message
        if(curr_turn == player_symbol) {
            cout << "***---***--- Player (" << player_symbol << ") Won ---***---***";
        } else {
            cout << "***---***--- Computer (" << computer_symbol << ") Won ---***---***";
        }
    }
    cout << endl;
    cin.ignore();
    return;
}

void game::input(){
    bool valid_move = false;
    int input_index;
    
    while(!valid_move){
        cout<<"Enter Index No (1-9): ";
        cin>>input_index;
        
        if(input_index < 1 || input_index > 9){
            cout<<"Invalid input. Please enter a number between 1 and 9."<<endl;
            continue;
        }
        
        int row = (input_index-1)/3;
        int col = (input_index-1)%3;
        
        if(board[row][col] != '*'){
            cout<<"That position is already taken. Try again."<<endl;
            continue;
        }
        
        board[row][col] = curr_turn;
        move_no++; // Increment move counter
        valid_move = true;
    }
}

pair<int,int> game::bestMove(){
    int best_row = -1;
    int best_col = -1;
    int bestScore = -1000;
    
    for(int i=0; i<side; i++){
        for(int j=0; j<side; j++){
            if(board[i][j] == '*'){
                board[i][j] = computer_symbol;
                int score = minimax(false, move_no+1, -1000, 1000);
                board[i][j] = '*';
                
                if(score > bestScore){
                    bestScore = score;
                    best_row = i;
                    best_col = j;
                }
            }
        }
    }
    
    return {best_row, best_col};
}

int game::minimax(bool isCompTurn, int depth, int alpha, int beta){
    // Check terminal states
    if(is_victory()){
        if(isCompTurn)
            return -10 + depth; // Human won
        else
            return 10 - depth;  // Computer won
    }
    
    if(depth >= 9) // Board is full (draw) - using depth instead of move_no
        return 0;
    
    if(isCompTurn){
        int bestScore = -1000;
        for(int i=0; i<side; i++){
            for(int j=0; j<side; j++){
                if(board[i][j] == '*'){
                    board[i][j] = computer_symbol;
                    int score = minimax(false, depth+1, alpha, beta);
                    board[i][j] = '*';
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                    if(beta <= alpha)
                        break; // Alpha-beta pruning
                }
            }
        }
        return bestScore;
    }
    else{
        int bestScore = 1000;
        for(int i=0; i<side; i++){
            for(int j=0; j<side; j++){
                if(board[i][j] == '*'){
                    board[i][j] = player_symbol;
                    int score = minimax(true, depth+1, alpha, beta);
                    board[i][j] = '*';
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                    if(beta <= alpha)
                        break; // Alpha-beta pruning
                }
            }
        }
        return bestScore;
    }
}

void game::computer_move(){
    cout<<"Computer is making a move..."<<endl;
    pair<int,int> comp_move = bestMove();
    board[comp_move.first][comp_move.second] = computer_symbol;
    move_no++; // Increment move counter for computer's move
}

void game::play_pvp() {
    // Player vs Player game loop
    showboard(false);
    cout<<endl;
    
    while(move_no < 9){
        // Player 1's turn
        curr_turn = P1;
        cout << "Player " << curr_turn << "'s turn:" << endl;
        input();
        showboard(true);
        
        if(is_victory()){
            victory_message();
            handle_end_game();
            return;
        }
        
        if(move_no >= 9) { // Check for draw
            cout<<"Match Was a Draw";
            handle_end_game();
            return;
        }
        
        // Player 2's turn
        curr_turn = P2;
        cout << "Player " << curr_turn << "'s turn:" << endl;
        input();
        showboard(true);
        
        if(is_victory()){
            victory_message();
            handle_end_game();
            return;
        }
    }
    
    cout<<"Match Was a Draw";
    handle_end_game();
    return;
}

void game::play_pvc() {
    // Player vs Computer game loop
    showboard(false);
    cout<<endl;
    
    // Initialize who plays first
    curr_turn = player_first ? player_symbol : computer_symbol;
    
    // Main game loop - one move per iteration
    while(move_no < 9) {
        if(curr_turn == player_symbol) {
            // Player's turn
            cout << "Your turn (Player " << curr_turn << "):" << endl;
            input();
        } else {
            // Computer's turn
            cout << "Computer's turn:" << endl;
            computer_move();
        }
        
        showboard(true);
        
        if(is_victory()) {
            victory_message();
            handle_end_game();
            return;
        }
        
        // Switch turns
        curr_turn = (curr_turn == player_symbol) ? computer_symbol : player_symbol;
    }
    
    cout<<"Match Was a Draw";
    handle_end_game();
    return;
}

void game::game_master(){
    // Select game mode
    start_screen();
    
    // Play the appropriate game mode
    if(is_pvp) {
        play_pvp();
    } else {
        // For PvC mode, ask who goes first
        select_first_player();
        play_pvc();
    }
}

int main(){
    game start;
    start.game_master();
    return 0;
}
