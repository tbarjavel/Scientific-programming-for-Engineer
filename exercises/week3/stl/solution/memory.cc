#include <memory>
#include <vector>
#include <iostream>

void question1_stack() {
  int values[10];

  for (int& v : values)
    v = 0;

  for (int i = 0; i < 10; ++i)
    std::cout << values[i] << " ";
  std::cout << std::endl;
}

void question1_heap() {
  int * values = new int[10];

  // We can't use range-for with heap allocated arrays
  // the best solution would use a std::vector
  for (int i = 0; i < 10; ++i)
    values[0] = 0;

  for (int i = 0; i < 10; ++i)
    std::cout << values[i] << " ";
  std::cout << std::endl;

  // The memory should be deallocated, otherwise we
  // have a dangling pointer
  delete[] values;
}

std::vector<int>* stack_allocation(int n) {
  std::vector<int> values(n);
  return &values; // good compilers show a warning here
}

std::vector<int>* heap_allocation(int n) {
  std::vector<int>* values = new std::vector<int>(n);
  return values;
}

void question2() {
  std::vector<int> * stack_values = stack_allocation(10);
  std::vector<int> * heap_values = heap_allocation(10);

  // stack_values->size() should fail because memory was freed
  // at the end of the function stack_allocation
  std::cout << stack_values->size() << ", " << heap_values->size() << std::endl;

  // We still need to delete
  delete heap_values;
}

void question1_bis() {
  std::array<int, 10> stack_values;

  for (int& v : stack_values)
    v = 0;

  std::vector<int> heap_values(10);

  for (int& v : heap_values)
    v = 0;

  // no need to delete, everything is managed
}

std::unique_ptr<std::vector<int>> unique_heap_allocation(int n) {
  return std::make_unique<std::vector<int>>(n);
}

void question2_bis() {
  std::unique_ptr<std::vector<int>> heap_vector = unique_heap_allocation(10);
  std::cout << heap_vector->size() << std::endl;

  // no need to delete: the unique pointer will deallocate everything at
  // the end of the function
}

void question3() {
  auto unique = std::make_unique<std::vector<int>>(10);

  std::unique_ptr<std::vector<int>> other = nullptr;

  // the move operation will make "unique" invalid
  // so that there is ONLY ONE pointer to the resource
  // hence "unique_ptr"
  other = std::move(unique);

  // memory will be deallocated nicely by the pointer "other"
}

void question3_bis() {
  auto shared = std::make_shared<std::vector<int>>(10);
  std::shared_ptr<std::vector<int>> other = nullptr;

  // This works because they are shared pointer
  other = shared;

  // memory will be deallocated nicely
}

int main() {
  question1_stack();
  question1_heap();
  //question2(); <-- this causes an error
  question1_bis();
  question2_bis();
  question3();
  question3_bis();
  return 0;
}
