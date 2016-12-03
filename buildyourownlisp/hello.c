#include <stdio.h>
#include <unistd.h>

struct person {
  int age;
};

int return_bool() {
  return 4 == 4;
}

void access_struct(struct person p) {
  printf("%d\n", p.age);
}

int main(int argc, char** argv) {
  struct person p;
  p.age = 4;
  access_struct(p);

  puts("Begin");
  if (0) {
    puts("b");
  }
  // while (1) {
  //   puts("hi");
  //   sleep(1);
  // }
  puts("done");
  printf("%d\n", return_bool());
  return 0;
}
