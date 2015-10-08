#include <fstream>

using namespace std;

#ifdef N
static int n = N;
#else
static int n = 2;
#endif

#ifdef M
static int m = M;
#else
static int m = 2;
#endif

int main(int argv, char** args) {
  ofstream out("1.matrix");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      out << j << ' ';
    }
    out << endl;
  }
  out.close();
  return 0;
}
