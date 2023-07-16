class Base {
};

class Derived : public Base {
};

int main() {
  Derived d;
  Base& b = d;
}