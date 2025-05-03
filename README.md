# Tic-Tac-Toe Game

## Overview
A classic Tic-Tac-Toe console game offering both human vs. human gameplay and challenging AI opponent modes. The game features a traditional 3x3 grid where players take turns placing X and O marks, with victory achieved by forming a line horizontally, vertically, or diagonally. Future versions will include graphical interface enhancements thorugh SFML.

## Key Features
- Game mode selection: PvP or PvC
- In PvC mode, player can choose to go first or second
- Input validation to prevent invalid moves
- End-game menu with options to restart, return to main menu, or exit
- Intelligent computer opponent (unbeatable)

## Technical Implementation
- Object-oriented design with a 'game' class encapsulating all functionality
- Minimax algorithm with alpha-beta pruning for optimal AI moves
- Game state tracking with move counter and current player turn
- Comprehensive input validation for all user interactions

## Game Flow
1. Player selects game mode (PvP/PvC)
2. In PvC mode, player chooses who goes first
3. Game board is displayed with position numbers
4. Players take turns making moves
5. Victory or draw is determined
6. End-game menu provides options to continue playing
