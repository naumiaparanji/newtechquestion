#include <algorithm> //added
#include <iostream>
#include <string> //added
#include <vector>

using namespace std;

int counter = 0;
int getLen(int end_len, int start_len) { // added
  int len = 0;
  if (counter % 2 == 0) {
    len = start_len;
    counter++;
  } else {
    len = end_len;
    counter++;
  }
  return len;
}
vector<string> split_string(string str, string range_str) {
  // 1. Declare variables which will be used or returned.
  vector<string> result;
  int start_len, end_len;
  if (range_str.empty() || str.empty()) { 
    // edge case where nothing specified
    cout << "Invalid input" << endl;
    return result;
  }

  // 2. Parse the range_str for the function
  sscanf(range_str.c_str(), "%d-%d", &start_len, &end_len);
  cout << "This is start_len: " << start_len << endl;
  cout << "This is end_len: " << end_len << endl;
  if (start_len <= 0 || end_len <= 0) {
    cout << "Invalid range" << endl;
    return result;
  } // edge case

  // 3. Remove whitespaces from the string
  str.erase(remove(str.begin(), str.end(), ' '), str.end());

  // 4. Loop through the string
  int pos = 0;
  while (pos < str.length()) {

    // 5. Determine the length of the next word
    int len = getLen(end_len, start_len); // added

    // int len = rand() % (end_len - start_len + 1) + start_len; //removed

    // 6. Make sure we don't go past the end of the string
    if (pos + len > str.length()) {
      len = str.length() - pos;
    }

    // 7. Add the word to the result array
    string word = str.substr(pos, len);
    result.push_back(word);
    pos += len;
  }

  // 8. Sort the words using a custom comparison function
  sort(result.begin(), result.end(), [](const string &a, const string &b) {
    string::const_iterator ita = a.begin(), itb = b.begin();
    while (ita != a.end() && itb != b.end()) {
      if (isdigit(*ita) && !isdigit(*itb)) {
        return true;
      } else if (!isdigit(*ita) && isdigit(*itb)) {
        return false;
      } else if (isupper(*ita) && !isupper(*itb)) {
        return true;
      } else if (!isupper(*ita) && isupper(*itb)) {
        return false;
      } else if (*ita < *itb) {
        return true;
      } else if (*ita > *itb) {
        return false;
      } else {
        ++ita;
        ++itb;
      }
    }
    return a.length() < b.length();
  });

  // 9. Return the result computed
  return result;
}

int main() {
  string str = "abcdEfghijklmnoPqrsTuvwxyz";
  string range_str = "4-6";
  vector<string> result = split_string(str, range_str);
  for (const auto &word : result) {
    cout << word << " ";
  }
  cout << endl;
  return 0;
}