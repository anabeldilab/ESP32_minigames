template <class T>
class Vector {
 public:
  Vector(void);
  Vector(const unsigned&);
  Vector(const Vector<T>&);

  ~Vector();

  T* get_vector(void) const;
  unsigned size(void) const;

  void set_sz(const unsigned&);
  void swap(const unsigned&, const unsigned&);

  const T& back(void) const;

  void push_back(const T&);

  Vector<T>& operator=(const Vector<T>&);
  bool operator==(const Vector<T>&);
  T& operator[](const unsigned&);
  T operator[](const unsigned&) const;

 private:
  T* vector_;
  unsigned sz_;
};



template <class T>
Vector<T>::Vector(void): sz_(0) { 
  vector_ = 0;
}


template <class T>
Vector<T>::Vector(const unsigned& sz): sz_(sz) {
  vector_ = new T[sz_];
}


template <class T> 
Vector<T>::Vector(const Vector<T>& kNewVector) {
  sz_ = kNewVector.size();
  vector_ = new T[sz_];
  for (unsigned i = 0; i < sz_; i++) {
    (*this)[i] = kNewVector[i];
  }  
}


template <class T> 
Vector<T>::~Vector() {
  delete[] vector_;
}


template <class T>
const T& Vector<T>::back(void) const {
  return vector_[sz_ - 1];
}


template <class T>
void Vector<T>::push_back(const T& kNewElement) {
  T* aux = new T[sz_ + 1];
  for (unsigned i = 0; i < sz_; i++) {
    aux[i] = vector_[i];
  }
  aux[sz_] = kNewElement;
  delete[] vector_;
  vector_ = aux;
  sz_++;
}


template <class T> 
Vector<T>& Vector<T>::operator=(const Vector<T>& kNewVector) {
  delete[] vector_;
  sz_ = kNewVector.size();
  vector_ = new T[sz_];
  for (unsigned i = 0; i < sz_; i++) {
    (*this)[i] = kNewVector[i];
  }  
  return *this;
}


template <class T> 
bool Vector<T>::operator==(const Vector<T>& kNewVector) {
  if (kNewVector.size() != sz_) return false;
  for (unsigned i = 0; i < sz_; i++)
    if (vector_[i] != kNewVector.get_vector()[i])
      return false;
  return true;
}


template <class T> 
T& Vector<T>::operator[](const unsigned& i) {
  if (i < 0 || i >= sz_) {
    std::cout << "Vector fuera de rango.\n";
    exit(1);
  } else {
    return vector_[i];
  }
}


template <class T> 
T Vector<T>::operator[](const unsigned& i) const {
  if (i < 0 || i >= sz_) {
    std::cout << "Vector fuera de rango.\n";
    exit(1);
  } else {
    return vector_[i];
  }
}


template <class T>
T* Vector<T>::get_vector(void) const {
  return vector_;
}


template <class T>
unsigned Vector<T>::size(void) const {
  return sz_;
}


template <class T>
void Vector<T>::set_sz(const unsigned& kNewsz)  {
  sz_ = kNewsz;
}


template <class T>
void Vector<T>::swap(const unsigned& x, const unsigned& y) {
  T aux = (*this)[x];
  (*this)[x] = (*this)[y];
  (*this)[y] = aux; 
}