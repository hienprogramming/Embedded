#include <stdio.h>

void recursive_function(int depth) {
  int local_array[1024]; // Khai báo mảng lớn trong hàm đệ quy

  printf("Depth: %d\n", depth);

  if (depth < 10) {
    recursive_function(depth + 1);
  }
}

int main() {
  recursive_function(0);
  return 0;
}