#include "AI.h"
#include "Chessboard.h"

int AI::getBestMove(ChessBoard &board) {
    int bestMove = 0, value = 0;
    findCompMove(board, bestMove, value, CompLoss, CompWin);
    return bestMove;
}

void AI::findCompMove(ChessBoard &board, int &bestMove,
    int &value, int alpha, int beta) {
    if (board.isFull()) {
        value = Draw;
    } else if (board.compCanWinImmediately(bestMove)) {
        value = CompWin;
    } else {
        value = alpha;
        for (int i = 0; i < 9 && value < beta; ++i) {
            if (board.isEmpty(i)) {
                board.placeComp(i);

                int tmp = -1, response = -1;  // Tmp is useless
                findHumanMove(board, tmp, response, value, beta);

                board.unPlace(i);

                if (response > value) {
                    value = response;
                    bestMove = i;
                }
            }
        }
    }
}

void AI::findHumanMove(ChessBoard &board, int &bestMove,
    int &value, int alpha, int beta) {
    if (board.isFull()) {
        value = Draw;
    } else if (board.humanCanWinImmediately(bestMove)) {
        value = CompLoss;
    } else {
        value = beta;
        for (int i = 0; i < 9 && value > alpha; ++i) {
            if (board.isEmpty(i)) {
                board.placeHuman(i);

                int tmp = -1, response = -1;  // Tmp is useless
                findCompMove(board, tmp, response, alpha, value);

                board.unPlace(i);

                if (response < value) {
                    value = response;
                    bestMove = i;
                }
            }
        }
    }
}
