#include "greensky_skiplist_map.h"

namespace metable {

template <typename KeyType, typename ValueType>
bool GreenSkySkiplistMap<KeyType, ValueType>::Put(const KeyType &key,
                                                  const ValueType &value) {
  auto it = data_.find(key);
  if (it != data_.end()) {
    return false;
  }
  data_.insert(std::make_pair(key, value));
  return true;
}

template <typename KeyType, typename ValueType>
bool GreenSkySkiplistMap<KeyType, ValueType>::Get(const KeyType &key,
                                                  ValueType *value) {
  if (value == nullptr) {
    return false;
  }

  auto it = data_.find(key);
  if (it == data_.end()) {
    return false;
  }

  *value = it->second;
  return true;
}

template <typename KeyType, typename ValueType>
bool GreenSkySkiplistMap<KeyType, ValueType>::Remove(const KeyType &key) {
  auto it = data_.find(key);
  if (it == data_.end()) {
    return false;
  }

  data_.erase(key);
  return true;
}

template <typename KeyType, typename ValueType>
bool GreenSkySkiplistMap<KeyType, ValueType>::Contains(const KeyType &key) {
  auto it = data_.find(key);
  return it != data_.end();
}

// The temporary function in "greensky_ skiplist_ map.cc" will resolve the link error. You do not need to call this function because it is global.
// When the compiler encounters a greensky skiplistmap object declaration of a specific type, such as int, int, it must be able to access the template implementation source.
// Otherwise, it will not know how to construct the greensky skiplistmap member function.
// Moreover, if you put the implementation in the source file (greensky_skiplist_map.cc) and make it a separate part of the project, the compiler is trying to compile Mian CPP source file will not be found when
// That is, it is not enough to just #include "greensky_skiplist_map.h", which only tells the compiler how to allocate object data and how to build calls to member functions, not how to build member functions.
// At the same time, the compiler will not complain. It will assume that these functions are provided elsewhere and let the linker find them.
// Therefore, when you need a link, you will get "unresolved references" to any class member function that is not defined as inline in the class definition.
void TemporaryFunction (){
  GreenSkySkiplistMap<int,int> TempObj;
}

} // namespace metable
