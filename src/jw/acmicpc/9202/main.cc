#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <string.h>

using namespace std;
constexpr unsigned int MAX_LEN = 8;
constexpr unsigned int BOGGLE_W = 4;
static const unsigned int word_to_point[MAX_LEN + 1] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

unsigned int n_words{}, n_boggles{};
map<string, bool> vocab;

char boggle[BOGGLE_W][BOGGLE_W];

class BoggleProcessor {
  public:
    BoggleProcessor() : len(0), point(0) {}
    ~BoggleProcessor() {}
    unsigned int len, point;
    string longest_word;
    map<string, bool> cur_vocab;
};

void init() {
  vocab.clear();
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
}

bool dfs(int y, int x, string w_in) { 
  if (y < 0 || x < 0 || x >= BOGGLE_W || y >= BOGGLE_W) return false;
  if (w_in.size() == 0) return true;
  if (boggle[y][x] != w_in[0]) return false;
  
  bool ret;
  string w = w_in.erase(0, 1);
  
  ret = dfs(y - 1, x - 1, w); if (ret) return true;
  ret = dfs(y - 1, x, w); if (ret) return true;
  ret = dfs(y - 1, x + 1, w); if (ret) return true;
  ret = dfs(y, x - 1, w); if (ret) return true;
  ret = dfs(y, x + 1, w); if (ret) return true;
  ret = dfs(y + 1, x - 1, w); if (ret) return true;
  ret = dfs(y + 1, x, w); if (ret) return true;
  ret = dfs(y + 1, x + 1, w); if (ret) return true;
  
  return false;
}

void process_boggle() {
  string buf;
  for (int i = 0 ; i < BOGGLE_W ; i++) {
    cin >> buf;
    strncpy((char*)&boggle[i], buf.c_str(), BOGGLE_W);
    /* dunno how to directly cin --> iostream damnit.. */
  }

  BoggleProcessor bp;

  for (auto w = vocab.begin() ; w != vocab.end() ; w++) {
    for (int i = 0 ; i < BOGGLE_W ; i++) {
      for (int j = 0 ;j < BOGGLE_W ; j++) {
        bool ret = dfs(i, j, w->first);
        if (ret && bp.cur_vocab.find(w->first) == bp.cur_vocab.end()) {
          bp.point += word_to_point[w->first.size()];
          bp.len++;
          bp.cur_vocab[w->first] = true;
          if (bp.longest_word.size() < w->first.size()) bp.longest_word = w->first;
          if (bp.longest_word.size() == w->first.size()) {
            if (bp.longest_word > w->first)
              bp.longest_word = w->first;
          }
        }
      }
    }
  }
  cout << bp.point << " " << bp.longest_word << " " << bp.len << endl;
}

void perform() {
  get_input();
  for (int i = 0 ; i < n_boggles ; i++)
    process_boggle();
}

int main() {
  init();
  perform();

  return 0;
}