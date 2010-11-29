
template <typename TYPE>
struct link {
  link* forward, *back;
  mutable TYPE data;
};

template <typename TYPE>
class buffer {
  private:
    link<TYPE> *_start, *_middle, *_end;
    int _size;

    int mod(int a, int b) { return a%b < 0 ? a%b+b : a%b; }

  public:
    buffer() : _size(0) {}
    ~buffer() {
      for (int i=0;i<_size;i++) {
        link<TYPE>* ptr = (*_start).forward;
        delete _start;
        _start = ptr;
      }
    }

    int size() const { return _size; }

    void push_front(const TYPE& new_data) {
      _size++;

      link<TYPE>* new_link = new link<TYPE>;
      (*new_link).data = new_data;

      if (_size > 1) {
        (*new_link).back = 0; // void first-link's back pointer

        (*new_link).forward = _start; // set first-link's forward pointer
        (*_start).back = new_link; // set old first-link's back pointer

        if (_size == 3) _middle = (*_start).forward; // at size 3, set the initial middle-pointer
        else if (mod(_size, 2) == 0) _middle = (*_middle).back; // every even insert, update the middle pointer :. _middle = _size/2

      }
      else { // if inserting the first item:
        (*new_link).back = 0; // void first-link's back pointer
        (*new_link).forward = 0; // void first-link's forward pointer

        _middle = new_link; // set middle pointer
        _end = new_link; // set end pointer
      }

      _start = new_link; // set start pointer
    }

    void pop_front() {
      _size--;

      if (_size == 0) {
        delete _start;
        return;
      }

      _start = (*_start).forward; // update start pointer
      delete (*_start).back; // deallocate memory for the removed item
      (*_start).back = 0; // void new start-link's back pointer

      if (_size > 0) {
        if (_size == 3) _middle = (*_start).forward; // at size 3, set the initial middle-pointer
        else if (mod(_size, 2) == 1) _middle = (*_middle).forward; // every odd delete, update the middle pointer :. _middle = _size/2
      }
    }

    void push_back(const TYPE& new_data) {
      _size++;

      link<TYPE>* new_link = new link<TYPE>;
      (*new_link).data = new_data;

      if (_size > 1) {
        (*new_link).back = _end; // set end-link's back pointer

        (*new_link).forward = 0; // void end-link's forward pointer
        (*_end).forward = new_link; // set old end-link's forward pointer

        if (_size == 3) _middle = (*_start).forward; // at size 3, set the initial middle-pointer
        else if (mod(_size, 2) == 1) _middle = (*_middle).forward; // every odd insert, update the middle pointer :. _middle = _size/2

      }
      else { // if inserting the first item:
        (*new_link).back = 0; // void first-link's back pointer
        (*new_link).forward = 0; // void first-link's forward pointer

        _start = new_link; // set start pointer
        _middle = new_link; // set middle pointer
      }

      _end = new_link; // set end pointer
    }

    void pop_back() {
      _size--;

      if (_size == 0) {
        delete _start;
        return;
      }

      _end = (*_end).back; // update end pointer
      delete (*_end).forward; // deallocate memory for the removed item
      (*_end).forward = 0; // void new end-link's forward pointer

      if (_size == 3) _middle = (*_start).forward; // at size 3, set the initial middle-pointer
      else if (mod(_size, 2) == 0) _middle = (*_middle).back; // every even delete, update the middle pointer :. _middle = _size/2
    }

    // complexity: worst = 1/4 * linear, best = constant
    TYPE& operator[](int index) const {
        if (index == 0) { return (*_start).data; } // start
        if (index == _size-1) { return (*_end).data; } // end
        if (_size%2 != 0 && index == _size/2) { return (*_middle).data; } // middle

        // index is not at a critical point:
        link<TYPE>* requested_link;
        if (index < _size/2) { // if index is in the first half
          if (index < _size/4) { // if index is in the first quarter
            requested_link = _start;
            for (int i=0;i<index;i++) requested_link = (*requested_link).forward; // advance pointer forward
          }
          else { // index is in the second quarter
            requested_link = _middle;
            for (int i=0;i<(_size-1)/2-index;i++) requested_link = (*requested_link).back; // advance pointer backward
          }
        }
        else { // index is in the second half
          if (index < _size*3/4) { // if index is in the third quarter
            requested_link = _middle;
            for (int i=0;i<index-(_size-1)/2;i++) requested_link = (*requested_link).forward; // advance pointer forward
          }
          else { // index is in the fourth quarter
            requested_link = _end;
            for (int i=0;i<_size-1-index;i++) requested_link = (*requested_link).back; // advance pointer backward
          }
        }
        return (*requested_link).data;

      }

      TYPE& front() const { return (*_start).data; }
      TYPE& mid() const { return (*_middle).data; }
      TYPE& back() const { return (*_end).data; }

      void print() const {
        cout << "m = ";
        if (_middle != 0) cout << (*_middle).data;
        cout << endl;

        link<TYPE>* ptr = _start;
        while (ptr != 0) {
          cout << (*ptr).data << " ";
          ptr = (*ptr).forward;
        }
        cout << endl;
      }
};
