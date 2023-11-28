class Cell;

class Observer {
 public:
  virtual void notify(Cell &c) = 0;  // c is the Cell that called the notify method
  virtual ~Observer() = default;
};
