#include <iostream>
#include <vector>

using namespace std;

// Function to compute the score for a pair of groups for a given game
size_t computeScore(int a, int b, int point) {
    return (size_t) point * (a + b);
}

// Function to find the pair of groups with the highest score for the next game (not used)
pair<int, int> findNextGame(vector<int> &groups, int *points, int index) {
    size_t maxScore = 0;
    pair<int, int> nextGame = {0, 1};
    for (int i = 0; i < groups.size(); i++) {
        for (int j = i + 1; j < groups.size(); j++) {
            size_t score = computeScore(groups[i], groups[j], points[index]);
            if (score > maxScore) {
                maxScore = score;
                nextGame = {i, j};
            }
        }
    }
    return nextGame;
}

// Function to run the algorithm and compute the maximum sum of points for n-1 games
size_t maxPoints(int n, int *points) {
    vector<int> groups(n, 1);

    size_t totalPoints = 0;
    for (int i = 0; i < n - 1; i++) {
        //pair<int, int> nextGame = findNextGame(groups, points, i);
        pair<int, int> nextGame = make_pair(n - (i + 2), n - (i + 1)); // Greedy
        totalPoints += computeScore(groups[nextGame.first], groups[nextGame.second], points[i]);
        int mergedGroup = groups[nextGame.first] + groups[nextGame.second];
        groups.erase(groups.begin() + nextGame.second);
        groups.erase(groups.begin() + nextGame.first);
        groups.push_back(mergedGroup);
    }
    return totalPoints;
}

int main() {
    int n;
    scanf("%d", &n);

    int *points = new int[n - 1];
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &points[i]);
    }

    size_t maxPointsResult = maxPoints(n, points);
    cout << maxPointsResult;
    return 0;
}
