#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <string.h>
#include <unordered_set>

using namespace std;

enum cache_state {NOT_CACHED, CACHED, CACHED_FALSE};
constexpr unsigned int MAX_WORDS = 300000;
constexpr unsigned int MAX_LEN = 8;
constexpr unsigned int BOGGLE_W = 4;
static const unsigned int word_to_point[MAX_LEN + 1] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

unsigned int n_words{}, n_boggles{};
unordered_map<string, bool> vocab;

char boggle[BOGGLE_W][BOGGLE_W];

class BoggleProcessor {
  public:
    BoggleProcessor() : len(0), point(0) {}
    ~BoggleProcessor() {}
    void add_word(string w) {
      if (cur_vocab.find(w) != cur_vocab.end()) return;
      cur_vocab[w] = true;
      len++;
      point += word_to_point[w.size()];
      if (w.size() > longest_word.size()) longest_word = w;
      else if (w.size() == longest_word.size()) {
        if (w < longest_word)
          longest_word = w;
      }
    }
    unsigned int len, point;
    string longest_word;
    unordered_map<string, bool> cur_vocab;
};

void init() {
  vocab.clear();
}

string random_word() {
  string ret= "";
  for (int i = 0 ; i < 5 ; i++)
    ret += rand()%('Z' - 'A') + 'A';

  return ret;
}

void get_input() {
  string buf;
  cin >> n_words;

  for (int i = 0 ; i < n_words ; i++) {
    string w;
    cin >> w;
    vocab[w] = true;
  }
  getline(cin, buf);
  cin >> n_boggles;

#if 0
  for (int i = n_words ; i < MAX_WORDS ; i++) {
    vocab[random_word()] = true;
  }
  n_words = MAX_WORDS;
#endif
}

int y_disp[] = {-1, 0, 1};
int x_disp[] = {-1, 0, 1};

void dfs(BoggleProcessor &bp, map<tuple<int, int>, bool> prv, int y, int x, string w) { 
  if (y < 0 || x < 0 || x >= BOGGLE_W || y >= BOGGLE_W) return;
  if (prv.size() >= MAX_LEN) return;
  w += boggle[y][x];
  prv[tuple<int, int>(y, x)] = true;
  if (vocab.find(w) != vocab.end()) {
    bp.add_word(w); 
  }

  for (int *dy = &y_disp[0] ; dy <= &y_disp[2] ; dy++){
    for (int *dx = &x_disp[0] ; dx <= &x_disp[2] ; dx++){
      if (!(*dy == 0 && *dx == 0) && prv.find(tuple<int, int>(y + *dy, x + *dx)) == prv.end())
      {
        dfs(bp, prv, y + *dy, x + *dx, w);
      }
    }
  }
}

void process_boggle() {
  string buf;
  for (int i = 0 ; i < BOGGLE_W ; i++) {
    cin >> buf;
    strncpy((char*)&boggle[i], buf.c_str(), BOGGLE_W);
    /* dunno how to directly cin --> iostream damnit.. */
  }

  BoggleProcessor bp;

  for (int i = 0 ; i < BOGGLE_W ; i++) {
    for (int j = 0 ; j < BOGGLE_W ; j++) {
      string w = "";
      map<tuple<int, int>, bool> points{};
      dfs(bp, points, i, j, w);
    }
  }
  cout << bp.point << " " << bp.longest_word << " " << bp.len << endl;
}

void perform() {
  get_input();
  for (int i = 0 ; i < n_boggles ; i++) {
    process_boggle();
  }
}

int main() {
  init();
  perform();

  return 0;
}