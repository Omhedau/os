#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>


using namespace std;

int FCFS(int pages[], int p, int slots[], int s) {
    int pageFaults = 0;
    int nextFreeSlot = 0;

    for (int i = 0; i < p; i++) {
        bool pageFaultOccurred = true;

        for (int j = 0; j < s; j++) {
            if (slots[j] == pages[i]) {
                pageFaultOccurred = false;
                break;
            }
        }

        if (pageFaultOccurred) {
            slots[nextFreeSlot] = pages[i];
            pageFaults++;
            nextFreeSlot = (nextFreeSlot + 1) % s;
        }
    }

    return pageFaults;
}

int LRU(int pages[], int p, int slots[], int s) {
    unordered_set<int> sSet; // To represent set of current pages
    unordered_map<int, int> indexes; // To store least recently used indexes of pages

    int pageFaults = 0;

    for (int i = 0; i < p; i++) {
        if (sSet.size() < s) {
            if (sSet.find(pages[i]) == sSet.end()) {
                sSet.insert(pages[i]);
                pageFaults++;
            }
            indexes[pages[i]] = i;
        } else {
            if (sSet.find(pages[i]) == sSet.end()) {
                int lru = INT_MAX, val;
                for (auto it = sSet.begin(); it != sSet.end(); it++) {
                    if (indexes[*it] < lru) {
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                sSet.erase(val);
                sSet.insert(pages[i]);
                pageFaults++;
            }
            indexes[pages[i]] = i;
        }
    }

    return pageFaults;
}

int optimal(int pages[], int p, int slots[], int s) {
    vector<int> fr(s, -1); // Frames initialized to -1

    int page_faults = 0;
    for (int i = 0; i < p; i++) {
        if (find(fr.begin(), fr.end(), pages[i]) == fr.end()) {
            int j = 0, farthest = i;
            for (int k = 0; k < s; k++) {
                int l;
                for (l = i; l < p; l++) {
                    if (fr[k] == pages[l]) {
                        if (l > farthest) {
                            farthest = l;
                            j = k;
                        }
                        break;
                    }
                }
                if (l == p) {
                    j = k;
                    break;
                }
            }
            fr[j] = pages[i];
            page_faults++;
        }
    }
    return page_faults;
}

int main() {
    int p, s;
    cout << "Enter no of elements in Reference String: ";
    cin >> p;

    vector<int> pages(p);

    cout << "Enter Reference String elements: ";
    for (int i = 0; i < p; i++) {
        cin >> pages[i];
    }

    cout << "Enter No of slots: ";
    cin >> s;

    vector<int> slots(s);

    char choice;
    cout << "Choose a paging replacement algorithm: " << endl;
    cout << "a) FCFS" << endl;
    cout << "b) Least Recently Used (LRU)" << endl;
    cout << "c) Optimal algorithm" << endl;
    cin >> choice;

    int pageFaults = 0;
    switch (choice) {
        case 'a':
            cout << "By using FCFS Algorithm: " << endl;
            pageFaults = FCFS(&pages[0], p, &slots[0], s);
            break;
        case 'b':
            cout << "By using LRU Algorithm: " << endl;
            pageFaults = LRU(&pages[0], p, &slots[0], s);
            break;
        case 'c':
            cout << "By using Optimal Algorithm: " << endl;
            pageFaults = optimal(&pages[0], p, &slots[0], s);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    cout << "Total page Faults: " << pageFaults << endl;

    return 0;
}

