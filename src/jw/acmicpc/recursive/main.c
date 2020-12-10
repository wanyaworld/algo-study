int n;
void func() {
  n++;
  if (n >= 100000) return;
  return func();
}

int main() {
  n = 0;
  func();
  return 0;
}
