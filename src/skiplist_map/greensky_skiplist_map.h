#pragma once

#include "include/sl_map.h"

#include "skiplist_map.h"

namespace metable {

template <typename KeyType, typename ValueType>
class GreenSkySkiplistMap : public SkiplistMap<KeyType, ValueType> {
public:
  virtual bool Put(const KeyType &key, const ValueType &value) override;

  virtual bool Get(const KeyType &key, ValueType *value) override;

  virtual bool Remove(const KeyType &key) override;

  virtual bool Contains(const KeyType &key) override;

  /// The desctuctor of this class.
  ~GreenSkySkiplistMap() = default;

private:
  sl_map_gc<KeyType, ValueType> data_;
};

//////////////////////////////////////////////////////////
//// TODO(qwang): Move these implementations to .cc file.
//////////////////////////////////////////////////////////
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

} // namespace metable
