#include "greensky_skiplist_map.h"


namespace metable {


  template<typename KeyType, typename ValueType>
  bool GreenSkySkiplistMap<KeyType, ValueType>::Put(const KeyType &key, const ValueType &value) {
    auto it = data_.find(key);
    if (it == data_.end()) {
      return false;
    }
    data_.insert(std::make_pair(key, value));
    return true;
  }

  template<typename KeyType, typename ValueType>
  bool GreenSkySkiplistMap<KeyType, ValueType>::Get(const KeyType &key, ValueType *value) {
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
  

  template<typename KeyType, typename ValueType>
  bool GreenSkySkiplistMap<KeyType, ValueType>::Remove(const KeyType &key) {
    auto it = data_.find(key);
    if (it == data_.end()) {
      return false;
    }

    data_.erase(key);
    return true;
  }


  template<typename KeyType, typename ValueType>
  bool GreenSkySkiplistMap<KeyType, ValueType>::Contains(const KeyType &key) {
    auto it = data_.find(key);
    return it == data_.end();
  }
  

} // namespace metable
