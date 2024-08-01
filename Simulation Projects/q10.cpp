#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> find_gaps(const vector<int>& sequence, int target);
unordered_map<int, int> count_gaps(const vector<int>& gaps);
void print_gap_counts(const unordered_map<int, int>& gap_counts);

int main() {
    // Example sequence
    vector<int> sequence = {1, 2, 3, 4, 1, 5, 1, 6, 7, 1, 8, 9, 1};
    int target = 1;

    vector<int> gaps = find_gaps(sequence, target);
    unordered_map<int, int> gap_counts = count_gaps(gaps);
    print_gap_counts(gap_counts);

    return 0;
}

vector<int> find_gaps(const vector<int>& sequence, int target) {
    vector<int> gaps;
    int last_position = -1;

    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == target) {
            if (last_position != -1) {
                gaps.push_back(i - last_position - 1);
            }
            last_position = i;
        }
    }

    return gaps;
}

unordered_map<int, int> count_gaps(const vector<int>& gaps) {
    unordered_map<int, int> gap_counts;

    for (int gap : gaps) {
        gap_counts[gap]++;
    }

    return gap_counts;
}

void print_gap_counts(const unordered_map<int, int>& gap_counts) {
    for (const auto& pair : gap_counts) {
        cout << "Gap length " << pair.first << ": " << pair.second << " occurrence(s)" << endl;
    }
}
